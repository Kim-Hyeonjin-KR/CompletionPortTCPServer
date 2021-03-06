#pragma once

#pragma comment(lib, "ws2_32")
#include<winsock2.h>
#include<iostream>

#include<stdlib.h>
#include<memory.h>
#include<list>
#include<queue>

constexpr u_short					SERVERPORT		= 9000;	// constexpr 컴파일 타임에서 초기화 되어 있지 않으면 컴파일 되지 않음.
constexpr unsigned __int32			BUFSIZE			= 512;
#define SOCKET_END	0
#define PACKET_NUM	1024	// 한번에 관리 할 수 있는 패킷의 총 갯수
#define ERROR		-2		// 사용자 정의 함수에서 에러일 경우 반환할 값
#define FAILED		-1		// 사용자 정의 함수에서 오류일 경우 반환할 값

// 사용자 정의 함수 성공 여부
enum RESULT
{
	E_SOC_ERROR = 1,
	E_SOC_TRUE,
	E_SOC_FALSE
};

enum IO_TYPE
{
	E_IO_Recv = 1,
	E_IO_Send = 2,
	E_IO_Accept
};


// 사용자 정의 통신 프로토콜
enum PROTOCOL
{
	E_INTRO = 1,
	E_MAIN,
	E_PLAY
};



// 오류 출력 함수
void err_quit(char* msg);
void err_display(char* msg);


#include"SOC.h"
#include"Packet.h"
#include"IOCP.h"

//#include"LoginManager.h"
#include"LoginSession.h"

#include"InitSystem.h"
