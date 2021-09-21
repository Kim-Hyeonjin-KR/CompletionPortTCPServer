#pragma once

#pragma comment(lib, "ws2_32")
#include<winsock2.h>
#include<iostream>

#include<stdlib.h>
#include<memory.h>
#include<list>
#include<queue>

constexpr u_short					SERVERPORT		= 9000;	// constexpr ������ Ÿ�ӿ��� �ʱ�ȭ �Ǿ� ���� ������ ������ ���� ����.
constexpr unsigned __int32			BUFSIZE			= 512;
#define SOCKET_END	0
#define PACKET_NUM	1024	// �ѹ��� ���� �� �� �ִ� ��Ŷ�� �� ����
#define ERROR		-2		// ����� ���� �Լ����� ������ ��� ��ȯ�� ��
#define FAILED		-1		// ����� ���� �Լ����� ������ ��� ��ȯ�� ��

// ����� ���� �Լ� ���� ����
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


// ����� ���� ��� ��������
enum PROTOCOL
{
	E_INTRO = 1,
	E_MAIN,
	E_PLAY
};



// ���� ��� �Լ�
void err_quit(char* msg);
void err_display(char* msg);


#include"SOC.h"
#include"Packet.h"
#include"IOCP.h"

//#include"LoginManager.h"
#include"LoginSession.h"

#include"InitSystem.h"
