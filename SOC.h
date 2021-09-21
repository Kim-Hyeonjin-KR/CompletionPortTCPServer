// https://recipes4dev.tistory.com/153

#pragma once
#include"global.h"

struct WSAOVERLAPPED_EX
{
	WSAOVERLAPPED overlapped;
	void* _ptr;		// � Ŭ���̾�Ʈ�� ��û�ΰ�
	IO_TYPE type;	// �����ΰ� ���ú��ΰ�
};

// ���� ���� ������ ���� ����ü
struct Recv_Buffer
{	
	char buf[BUFSIZE + 1];
	int target_bytes;
	int comp_bytes;	
};

struct Send_Buffer
{
	char* buf;	//����� �����ͷ� �����Ҵ�
	int target_bytes;
	int comp_bytes;
};

class TCPSocket
{
private:
	bool			SockInit();
	bool			r_sizeflag;	//recv������ ���.
	//SOCKET m_socket;

protected:
	SOCKET			m_sock;
	WSAOVERLAPPED_EX  m_recv_overlapped;
	WSAOVERLAPPED_EX  m_send_overlapped;
	WSAOVERLAPPED_EX  m_accept_overlapped;

	Recv_Buffer		m_Recv_buffer;
	std::queue<Send_Buffer*> m_Send_buffer;

	//����� ť (�����Ҵ�)
	TCPSocket();
	TCPSocket(SOCKET inSocket);
	~TCPSocket();

	bool			Bind(sockaddr_in _portAddr);	//��Ʈ���� ���� ���� �ּ�(���� ���п�)
	bool			Listen();

	//recv
	bool			Recv();
	int				CompleteRecv(int _completebyte);

	//send
	bool			Send(char* _sendData, int _inLen);
	int				CompleteSend(int _completebyte);


	//accept
	void AcceptSock();
	TCPSocket* Accept();	//���� ������ �ּ�(���ſ� ���� �ܺ� ��ſ�)
};




//bool			Connect(sockaddr_in _serverAddr);	//Ŭ�󿡼� ����� �Լ�