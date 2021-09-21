#pragma once

#include"global.h"

//다른 소스코드의 전역변수를 사용하는 방법. 내가 만든건 아닌것 같다.
class IOCP;
extern IOCP* m_LoginManager;

class IOCP
{
	//init, end, 포트핸들만듥
	HANDLE				m_hcp;
	std::list<HANDLE>	m_hThread_list;	//쓰레드 헨들들 백터로 관리해서 모든 쓰레드가 사용종료되면 메인쓰레드 종료할 수 있도록
	void				Running();

public:
	static DWORD __stdcall	WorkerThread(void* _ptr);

	bool			Init_IOCPPort();
	void			RegisterIocp(SOCKET);

	virtual void	accepted()	= 0;
	virtual void	recved(void* object, int bytes)		= 0;
	virtual void	sent(void* object, int bytes)		= 0;
	virtual void	distroy()	= 0;


};