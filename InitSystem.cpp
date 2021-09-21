#include "InitSystem.h"


bool InitSystem::Init(u_short _serverport)
{
	// 윈속 초기화			sockInit 함수를 쓰면. TCPSocket 생성자가 호출될건데 그럼 AcceptSock는 자동으로 생성된다. AcceptSock 소켓 생성보다 윈속 초기화가 먼저 진행되어야 하지 않나?
	TCPSocket::SockInit();
	// iocp 입출력 포트 생성 -iocp
	IOCP::CreateIOCPPort(IOCP::WorkerThread);		//스마트 포인터로 핸들을 가져온다?
	// AcceptSock 생성 -메인
	TCPSocket::AcceptSock();
	// binding -메인
	TCPSocket::Bind();
	// debug
	printf("초기화 시스템 리슨 대기상태 진입 완료. port : %d", _serverport);
	// listening
	TCPSocket::Listen();
	// create accept thread
	HANDLE hThread = CreateThread(NULL, 0, AcceptThread, , 0, NULL);


	return true;
}
