// https://recipes4dev.tistory.com/153

#pragma once
#include"global.h"

struct WSAOVERLAPPED_EX
{
	WSAOVERLAPPED overlapped;
	void* _ptr;		// 어떤 클라이언트의 요청인가
	IO_TYPE type;	// 샌드인가 리시브인가
};

// 소켓 정보 저장을 위한 구조체
struct Recv_Buffer
{	
	char buf[BUFSIZE + 1];
	int target_bytes;
	int comp_bytes;	
};

struct Send_Buffer
{
	char* buf;	//샌드는 포인터로 동적할당
	int target_bytes;
	int comp_bytes;
};

class TCPSocket
{
private:
	bool			SockInit();
	bool			r_sizeflag;	//recv에서만 사용.
	//SOCKET m_socket;

protected:
	SOCKET			m_sock;
	WSAOVERLAPPED_EX  m_recv_overlapped;
	WSAOVERLAPPED_EX  m_send_overlapped;
	WSAOVERLAPPED_EX  m_accept_overlapped;

	Recv_Buffer		m_Recv_buffer;
	std::queue<Send_Buffer*> m_Send_buffer;

	//샌드용 큐 (동적할당)
	TCPSocket();
	TCPSocket(SOCKET inSocket);
	~TCPSocket();

	bool			Bind(sockaddr_in _portAddr);	//포트마다 사용될 내부 주소(내부 구분용)
	bool			Listen();

	//recv
	bool			Recv();
	int				CompleteRecv(int _completebyte);

	//send
	bool			Send(char* _sendData, int _inLen);
	int				CompleteSend(int _completebyte);


	//accept
	void AcceptSock();
	TCPSocket* Accept();	//서버 소켓의 주소(수신에 사용될 외부 통신용)
};




//bool			Connect(sockaddr_in _serverAddr);	//클라에서 사용할 함수