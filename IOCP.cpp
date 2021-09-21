#include "IOCP.h"

bool IOCP::Init_IOCPPort()
{
	// ����� �Ϸ� ��Ʈ ����

	// �Ʒ� HANDLE ��������� Ŭ������ ���Ѱ�
	m_hcp = CreateIoCompletionPort(INVALID_HANDLE_VALUE, NULL, 0, 0);
	if (m_hcp == NULL) return false;


	// CPU ���� Ȯ��
	SYSTEM_INFO si;
	GetSystemInfo(&si);

	// (CPU ���� * 2)���� �۾��� ������ ����
	HANDLE hThread;
	for (int i = 0; i < (int)si.dwNumberOfProcessors * 2; i++) {
		hThread = CreateThread(NULL, 0, WorkerThread, this, 0, NULL);
		if (hThread == NULL) return false;
		//CloseHandle(hThread); // ��� ������ ������ �� �۾� ���ֱ�
		//�ڵ� ���Ϳ� �־��ֱ�
		m_hThread_list.push_back(hThread);
	}


	return true;
}

DWORD __stdcall IOCP::WorkerThread(void* _ptr)
{
	static_cast<IOCP*>(_ptr)->Running();
	return 0;
}


//������, ���� ��ȣ, ��������, ��ŷ�� ������
// 									= ������ : ������, ������ ��������, ���, ���� ������
//������ ��ŷ�Ǿ� �ִµ�. �Ŵ��� ���������� ��� �����Ͽ��� �ϴ°�.
//OverlappedEX�� ���ԵǾ� �ִ� void* ptr�� �����Ͽ� �����ϴ°��� �´°�.
//�´ٸ� �Ʒ� Running()�Լ����� �ش� ���������� ã�Ƽ� �����ϴ°��� �´°�.

void IOCP::Running()
{
	//dword, long*, �������ǵ�ex����� �������ǵ��ĳ����, ���Ǵ�Ʈ
	DWORD* data_size;
	unsigned long ptr;
	WSAOVERLAPPED_EX* overlapped_ex;

	while (true)
	{

		// I/O �Ϸ���Ʈ���� ��Ŷ�� �������� �Լ�
												//�Ϸ���Ʈ�� ���
												//����� �Ϸ� ������ ����� ���۵� ������ ũ��
												//���� ���� ���õ� �Ϸ� Ű���� ������
												//overlapped ������
												//�Ϸ� ��Ŷ�� ��ٷ��ִ� �ð�
		bool retval = GetQueuedCompletionStatus(m_hcp, data_size, &ptr, (LPOVERLAPPED*)&overlapped_ex, INFINITE);



		//�����˻�
		if (retval == false)
		{
			distroy();
		}

		//�ϴ� ����
		//accepted();


		//GetQued�� 4��° �Ű��������� IO_TYPE���� �����Ͽ� �˾Ƴ� ������ �Լ� ȣ��.
		switch (overlapped_ex->type)
		{
		case E_IO_Recv :
			recved(overlapped_ex->_ptr, (int)data_size);
			break;

		case E_IO_Send :
			sent(overlapped_ex->_ptr, (int)data_size);
			break;

		case E_IO_Accept :
			accepted(overlapped_ex->_ptr, (int)data_size); //loginsseion ��ü  ������ iocp ��Ʈ�� �����ڵ� ���
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