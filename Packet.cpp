#include "Packet.h"

int PacketBase::SetID()
{
	for (int id = 0; id < PACKET_NUM; id++)
	{
		if (Send_PacketID[id] == false)
		{
			return id;
		}
	}

	return FAILED;
}


int PacketBase::GetID(char* _recvbuf)
{
	char* _ptr = _recvbuf;
	char* tmpID;

	memcpy(tmpID, _ptr, sizeof(int));

	return atoi(tmpID);
}


void PacketBase::GetProtocol(char* _recvbuf, PROTOCOL& _protocol)
{
	char* _ptr = _recvbuf + sizeof(int);

	memcpy(&_protocol, _ptr, sizeof(PROTOCOL));
}


int PacketBase::PackPacket(PROTOCOL _protocol, const char* _str1, int size)	//_str1 ���� ��ü�� ������ �Ŵ������� ������ ����� ��ŷ�ؼ� ������ ����
{
	char mBuffer[BUFSIZE];

	int size = 0;
	char* ptr = _sendbuf;
	int strsize = strlen(_str1);
	int _packid = SetID();

	if (_packid == FAILED)
	{
		return FAILED;
	}


	ptr = ptr + sizeof(size);

	// ��Ŷ ID �߰�
	memcpy(ptr, &_packid, sizeof(_packid));
	ptr = ptr + sizeof(_packid);
	size = size + sizeof(_packid);

	// �������� �߰�
	memcpy(ptr, &_protocol, sizeof(_protocol));
	ptr = ptr + sizeof(_protocol);
	size = size + sizeof(_protocol);

	// ���� ���� �߰�
	memcpy(ptr, &strsize, sizeof(strsize));
	ptr = ptr + sizeof(strsize);
	size = size + sizeof(strsize);

	// ���� �߰�
	memcpy(ptr, _str1, strsize);
	ptr = ptr + strsize;
	size = size + strsize;


	// ���� �տ� �� �뷮 �߰�
	ptr = _sendbuf;
	memcpy(ptr, &size, sizeof(size));

	size = size + sizeof(size);

	return size;
}

int PacketBase::UnPackPacket(char* _recvbuf, char* _str1)
{
	int data_size;

	char* ptr = _recvbuf + sizeof(int) + sizeof(PROTOCOL);

	memcpy(&data_size, ptr, sizeof(data_size));
	ptr = ptr + sizeof(data_size);

	memcpy(_str1, ptr, data_size);
	ptr = ptr + data_size;
}

int PacketBase::Send(char* _sendData, int _inLen)
{
	return TCPSocket::Send(_sendData, _inLen);
}
