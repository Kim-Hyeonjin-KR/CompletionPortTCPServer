#include "InitSystem.h"


bool InitSystem::Init(u_short _serverport)
{
	// ���� �ʱ�ȭ			sockInit �Լ��� ����. TCPSocket �����ڰ� ȣ��ɰǵ� �׷� AcceptSock�� �ڵ����� �����ȴ�. AcceptSock ���� �������� ���� �ʱ�ȭ�� ���� ����Ǿ�� ���� �ʳ�?
	TCPSocket::SockInit();
	// iocp ����� ��Ʈ ���� -iocp
	IOCP::CreateIOCPPort(IOCP::WorkerThread);		//����Ʈ �����ͷ� �ڵ��� �����´�?
	// AcceptSock ���� -����
	TCPSocket::AcceptSock();
	// binding -����
	TCPSocket::Bind();
	// debug
	printf("�ʱ�ȭ �ý��� ���� ������ ���� �Ϸ�. port : %d", _serverport);
	// listening
	TCPSocket::Listen();
	// create accept thread
	HANDLE hThread = CreateThread(NULL, 0, AcceptThread, , 0, NULL);


	return true;
}
