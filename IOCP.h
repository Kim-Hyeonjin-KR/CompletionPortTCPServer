#pragma once

#include"global.h"

//�ٸ� �ҽ��ڵ��� ���������� ����ϴ� ���. ���� ����� �ƴѰ� ����.
class IOCP;
extern IOCP* m_LoginManager;

class IOCP
{
	//init, end, ��Ʈ�ڵ鸸��
	HANDLE				m_hcp;
	std::list<HANDLE>	m_hThread_list;	//������ ���� ���ͷ� �����ؼ� ��� �����尡 �������Ǹ� ���ξ����� ������ �� �ֵ���
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