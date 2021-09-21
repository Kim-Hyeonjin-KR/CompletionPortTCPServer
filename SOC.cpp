#include "SOC.h"

bool TCPSocket::SockInit()
{
	// ���� �ʱ�ȭ
	WSADATA wsa;
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0) return false;
	return true;
}

TCPSocket::TCPSocket()
{
	// ������ ȣ�� �� �Ű������� ������ AcceptSocket���� �ʱ�ȭ �մϴ�.
	AcceptSock();
}

TCPSocket::TCPSocket(SOCKET inSocket)
{
	m_sock = inSocket;
}

TCPSocket::~TCPSocket()
{
	closesocket(m_sock);
}

bool TCPSocket::Bind(sockaddr_in _portAddr)
{
	// bind()
	SOCKADDR_IN serveraddr;
	ZeroMemory(&serveraddr, sizeof(serveraddr));
	serveraddr.sin_family = AF_INET;
	serveraddr.sin_addr.s_addr = htonl(INADDR_ANY);
	serveraddr.sin_port = htons(SERVERPORT);
	int retval = bind(m_sock, (SOCKADDR*)&serveraddr, sizeof(serveraddr));
	if (retval == SOCKET_ERROR) err_quit("bind()");
}

bool TCPSocket::Listen()
{
	// listen()
	int retval = listen(m_sock, SOMAXCONN);
	if (retval == SOCKET_ERROR)
	{
		err_quit("listen()");
		return false;
	}
	return true;
}

void TCPSocket::AcceptSock()
{
	m_sock = socket(AF_INET, SOCK_STREAM, 0);
	if (m_sock == INVALID_SOCKET) err_quit("socket()");
}


TCPSocket* TCPSocket::Accept()	//�Ʒ� Connect�Լ��� �Ű����� _serverAddr�� �ٸ���?
{
	int addrlen;
	SOCKET _new_sock;
	SOCKADDR_IN clientaddr;
	// accept()
	addrlen = sizeof(clientaddr);
	_new_sock = accept(m_sock, (SOCKADDR*)&clientaddr, &addrlen);	// accept�� ������ ����� ��
	if (_new_sock == INVALID_SOCKET) {
		err_display("accept()");
		//����ó��
	}

	return new TCPSocket(_new_sock);
}

bool TCPSocket::Recv()
{
	int		retval;
	DWORD	recvbytes;
	DWORD	flags = 0;
	WSABUF	wsabuf;

	ZeroMemory(&m_recv_overlapped.overlapped, sizeof(m_recv_overlapped.overlapped));

	wsabuf.buf = m_Recv_buffer.buf + m_Recv_buffer.comp_bytes;

	if (r_sizeflag)
	{
		wsabuf.len = m_Recv_buffer.target_bytes - m_Recv_buffer.comp_bytes;
	}
	else
	{
		wsabuf.len = sizeof(int) - m_Recv_buffer.comp_bytes;
	}

	retval = WSARecv(m_sock, &wsabuf, 1, &recvbytes,
		&flags, &m_recv_overlapped.overlapped, NULL);
	if (retval == SOCKET_ERROR)
	{
		if (WSAGetLastError() != WSA_IO_PENDING)
		{
			err_display("WSARecv()");
			return false;
		}
	}

	return true;
}

int TCPSocket::CompleteRecv(int _completebyte)
{
	
	if (!r_sizeflag)
	{
		m_Recv_buffer.comp_bytes += _completebyte;

		if (m_Recv_buffer.comp_bytes == sizeof(int))
		{
			memcpy(&m_Recv_buffer.target_bytes, m_Recv_buffer.buf, sizeof(int));
			m_Recv_buffer.comp_bytes = 0;
			r_sizeflag = true;
		}

		if (!Recv())
		{
			return E_SOC_ERROR;
		}

		return E_SOC_FALSE;
	}

	m_Recv_buffer.comp_bytes += _completebyte;

	if (m_Recv_buffer.comp_bytes == m_Recv_buffer.target_bytes)
	{
		m_Recv_buffer.comp_bytes = 0;
		m_Recv_buffer.target_bytes = 0;
		r_sizeflag = false;

		return E_SOC_TRUE;
	}
	else
	{
		if (!Recv())
		{
			return E_SOC_ERROR;
		}

		return E_SOC_FALSE;
	}
}

bool TCPSocket::Send(char* _sendData, int _sendLen)		//send,recv ��ŷ Ŭ������ �ű�� �� ����غ� ��, ��ŷ Ŭ���� �����
{
	int retval;
	DWORD sendbytes;
	DWORD flags;
	WSABUF wsabuf;

	Send_Buffer* tmp_send_buffer;

	//�����۽� �Ʒ� �����Ҵ� �ϴ� �κ� ��ŵ
	//tmp_send_buffer�� ����ִٸ�. ���� �����Ҵ��� ���� �ʾҰ� ó�� ������ �����Ѵٴ� ��
	if (_sendLen != 0)
	{
		if (tmp_send_buffer == nullptr)
		{
			//ť�� ���� ����ü ���� �Ҵ�
			tmp_send_buffer = new Send_Buffer;

			//����ü�� ������ ���ۿ� �ּҸ� �Ѱ��� �ӽ� �޸𸮸� ���� �Ҵ�
			char* tmpbuf = new char[_sendLen];

			//�ӽ� �޸𸮿� ���� ������ ����.				//���۸� ���� �������� ���� �ٷ� �Ű������� _sendData�� �ٷ� tmp_send_buffer->buf�� �ѱ�� �ȵɱ�? 1
			memcpy(tmpbuf, _sendData, _sendLen);

			//�ӽ� �޸��� ���� �ּҸ� ����ü�� ������ ���ۿ� ����
			tmp_send_buffer->buf = tmpbuf;

			//����ü�� ��ǥ �뷮 ����
			tmp_send_buffer->target_bytes = _sendLen;

			//����ü�� �Ϸ� �뷮 ����
			tmp_send_buffer->comp_bytes = *(_sendData + sizeof(char*) + sizeof(int));
		}

	}


	if (m_Send_buffer.size() == 0)
	{
		m_Send_buffer.push(tmp_send_buffer);
		//�׳� �ٷ� ������ �Ʒ� ���ø�Ʈ ���忡�� ť�� Ȯ���ϴ� �������� ������ �� �� ����
	}
	else
	{
		m_Send_buffer.push(tmp_send_buffer);
		//ť�� ���� ����
		return true;
	}

	//����ü ���� �Ҵ� �ޱ�
	//sendData�� ���� �ӽø޸� sendLen��ŭ �����Ҵ�
	//�����Ҵ� ���� �ӽø޸��� ���� �ּ� ����ü�� ���
	//ť Ȯ�� �� �̹� ����� �ִ� ������ ������ �ٷ� ����
	//�̹� ����� �ִ� ���� ������ ���


	ZeroMemory(&m_send_overlapped.overlapped, sizeof(m_send_overlapped.overlapped));
	/*if (tmp_send_buffer->target_bytes == 0)
	{
		tmp_send_buffer->target_bytes = _sendLen;
	}*/

	wsabuf.buf = tmp_send_buffer->buf + tmp_send_buffer->comp_bytes;
	wsabuf.len = tmp_send_buffer->target_bytes - tmp_send_buffer->comp_bytes;

	retval = WSASend(m_sock, &wsabuf, 1, &sendbytes,
		0, &m_send_overlapped.overlapped, NULL);
	if (retval == SOCKET_ERROR)
	{
		if (WSAGetLastError() != WSA_IO_PENDING)
		{
			err_display("WSASend()");
			//RemoveClientInfo(_ptr);
			return false;
		}
	}

	//CompleteSend(retval);


	return true;
}

int TCPSocket::CompleteSend(int _completebyte)
{
	//ť���� ����Ʈ�� �ϳ� �����Ͽ� ��������
	Send_Buffer* tmp_send_buffer = m_Send_buffer.front();

	tmp_send_buffer->comp_bytes += _completebyte;
	if (tmp_send_buffer->comp_bytes == tmp_send_buffer->target_bytes)
	{
		//����Ʈ 2��, ��, �ڿ� ť Ȯ�� �� ������ ����
		delete[] tmp_send_buffer->buf;
		delete tmp_send_buffer;
		m_Send_buffer.pop();
		if (m_Send_buffer.size() != 0)
		{
			//send�� �Ű������� �ֱ� ���� ��� ����Ʈ �ߴ� tmp_send_buffer�� �ٽ� ���� �����. ���� ����Ǵ� �� ���Ƽ� �ƽ���. 2
			Send_Buffer* tmp_send_buffer = m_Send_buffer.front();
			Send(tmp_send_buffer->buf, tmp_send_buffer->target_bytes - tmp_send_buffer->comp_bytes);	// ���� �Ϸ�
		}

		return E_SOC_TRUE;	//ť�� ���� ������ �ִٸ�. �Ϻδ� �����ϰ� �Ϻδ� ���� �� �� �ִµ�. �̷� ��� return���� ��� ��ȯ���ٱ�. 3
	}

	if (!Send(tmp_send_buffer->buf, 0))
	{
		return E_SOC_ERROR;
	}

	return E_SOC_FALSE;
}