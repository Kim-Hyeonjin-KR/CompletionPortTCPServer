#include "IOCP.h"

bool IOCP::Init_IOCPPort()
{
	// 입출력 완료 포트 생성

	// 아래 HANDLE 멤버변수로 클래스로 빼둘것
	m_hcp = CreateIoCompletionPort(INVALID_HANDLE_VALUE, NULL, 0, 0);
	if (m_hcp == NULL) return false;


	// CPU 개수 확인
	SYSTEM_INFO si;
	GetSystemInfo(&si);

	// (CPU 개수 * 2)개의 작업자 스레드 생성
	HANDLE hThread;
	for (int i = 0; i < (int)si.dwNumberOfProcessors * 2; i++) {
		hThread = CreateThread(NULL, 0, WorkerThread, this, 0, NULL);
		if (hThread == NULL) return false;
		//CloseHandle(hThread); // 모든 쓰레드 끝나면 이 작업 해주기
		//핸들 벡터에 넣어주기
		m_hThread_list.push_back(hThread);
	}


	return true;
}

DWORD __stdcall IOCP::WorkerThread(void* _ptr)
{
	static_cast<IOCP*>(_ptr)->Running();
	return 0;
}


//사이즈, 구분 번호, 프로토콜, 패킹된 데이터
// 									= 데이터 : 사이즈, 데이터 프로토콜, 결과, 실제 데이터
//순으로 패킹되어 있는데. 매니저 프로토콜을 어디서 구분하여야 하는가.
//OverlappedEX에 포함되어 있는 void* ptr을 참조하여 구분하는것이 맞는가.
//맞다면 아래 Running()함수에서 해당 프로토콜을 찾아서 구분하는것이 맞는가.

void IOCP::Running()
{
	//dword, long*, 오버레피드ex만들고 오버레피드로캐스팅, 인피니트
	DWORD* data_size;
	unsigned long ptr;
	WSAOVERLAPPED_EX* overlapped_ex;

	while (true)
	{

		// I/O 완료포트에서 패킷을 가져오는 함수
												//완료포트의 헨들
												//입출력 완료 연산의 결과로 전송된 데이터 크기
												//파일 헨들과 관련된 완료 키값의 포인터
												//overlapped 포인터
												//완료 패킷을 기다려주는 시간
		bool retval = GetQueuedCompletionStatus(m_hcp, data_size, &ptr, (LPOVERLAPPED*)&overlapped_ex, INFINITE);



		//오류검사
		if (retval == false)
		{
			distroy();
		}

		//일단 보류
		//accepted();


		//GetQued의 4번째 매개변수에서 IO_TYPE으로 접근하여 알아낸 값으로 함수 호출.
		switch (overlapped_ex->type)
		{
		case E_IO_Recv :
			recved(overlapped_ex->_ptr, (int)data_size);
			break;

		case E_IO_Send :
			sent(overlapped_ex->_ptr, (int)data_size);
			break;

		case E_IO_Accept :
			accepted(overlapped_ex->_ptr, (int)data_size); //loginsseion 객체  생성및 iocp 포트에 소켓핸들 등록
			break;

		default:
			break;
		}
	}
}

void			IOCP::RegisterIocp(SOCKET sock)
{
	CreateIoCompletionPort(m_hcp, (HANDLE)sock, NULL, 0);
}