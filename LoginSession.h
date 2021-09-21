#pragma once

#include "global.h"


enum STATE
{
	E_INIT_STATE = -1,
	E_MENU_SELECT_STATE = 1,	//enum형식 E붙여주도록 변경
	E_JOIN_RESULT_SEND_STATE,
	E_LOGIN_RESULT_SEND_STATE,
	E_LOGIN_STATE,
	E_LOGOUT_RESULT_SEND_STATE,
	E_DISCONNECTED_STATE
};


class LoginSession : PacketBase
{
private:
	//state는 여기서 관리
	STATE m_state;

public:
	STATE GetState();
	void SetState(STATE _state);

	void PackPacket(char* _buf, PROTOCOL _protocol, RESULT _result, char* _str1, int& _size);
	void UnPackPacket(char* _buf, char* _str1, char* _str2, char* _str3);
	void UnPackPacket(char* _buf, char* _str1, char* _str2);
	void GetProtocol(char* _ptr, PROTOCOL& _protocol);

	bool SendPack(PROTOCOL _protocol, const char* _str1);	// 소켓, 패킷ID, 프로토콜, 데이터 순으로 패킹합니다
	bool RecvPack(char* _recvbuf, char* _str1);
};

