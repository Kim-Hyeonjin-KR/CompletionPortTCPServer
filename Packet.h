#pragma once
#include "global.h"

class PacketBase : public TCPSocket
{
private:
	int Send_PacketID;	//������� ���̵��� true, ����ִٸ� false
	int Recv_PacketID;	//������� ���̵��� true, ����ִٸ� false

	
	int SetID();	// ����� �� �ִ� ���̵� ã�Ƽ� �����ɴϴ�

protected:
	int GetID(char* _recvbuf);
	void GetProtocol(char* _ptr, PROTOCOL& _protocol);
	int PackPacket(char* _sendbuf, PROTOCOL _protocol, const char* _str1);	// ����, ��ŶID, ��������, ������ ������ ��ŷ�մϴ�
	int UnPackPacket(char* _recvbuf, char* _str1);
	int Send(char* _sendData, int _inLen);	// ���� ��... Packet_Send, Call_Send, Call_SOC_Send ������ �� ��Զ� ����ұ�?
};

// ���� ���ڵ��� ���������� ��ŷ�ϱ�
// ����Ʈ(����) ����(����Ʈ)
// 
