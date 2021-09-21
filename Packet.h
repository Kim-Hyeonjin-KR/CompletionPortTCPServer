#pragma once
#include "global.h"

class PacketBase : public TCPSocket
{
private:
	int Send_PacketID;	//사용중인 아이디라면 true, 비어있다면 false
	int Recv_PacketID;	//사용중인 아이디라면 true, 비어있다면 false

	
	int SetID();	// 사용할 수 있는 아이디를 찾아서 가져옵니다

protected:
	int GetID(char* _recvbuf);
	void GetProtocol(char* _ptr, PROTOCOL& _protocol);
	int PackPacket(char* _sendbuf, PROTOCOL _protocol, const char* _str1);	// 소켓, 패킷ID, 프로토콜, 데이터 순으로 패킹합니다
	int UnPackPacket(char* _recvbuf, char* _str1);
	int Send(char* _sendData, int _inLen);	// 변수 명... Packet_Send, Call_Send, Call_SOC_Send 등으로 좀 길게라도 써야할까?
};

// 여러 인자들을 공통적으로 패킹하기
// 바이트(길이) 내용(바이트)
// 
