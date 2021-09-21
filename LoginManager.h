#pragma once

#include "global.h"
//#include "LoginSession.h"
//�۷ι� ��� ���Ͽ����� �ִ��� �ߺ��� �ּ�ȭ �ϵ��� ������ ��. ��� ������ include�� �ּ�ȭ �Ұ�. ���漱������ �ذ��� �� �ִٸ� �׷��� ó���Ұ�.
//

#define ID "abcd"
#define PW 1234

// ����� ���� ���� <�α���>
// �Ʒ� enum�� �� LoginSession.h�� �� ������ �͵��� �� �� �ֵ��� �Ұ�

// UML���� ���� ���� �����
// ä�� ���, ���� ��� �̾�ޱ� ������ �� �ֵ���


enum LOGIN_MANAGER_RESULT
{
	E_NODATA = -1,
	E_ID_EXIST = 1,
	E_ID_ERROR,
	E_PW_ERROR,
	E_JOIN_SUCCESS,
	E_LOGIN_SUCCESS,
	E_LOGOUT_SUCCESS
};

enum LOGIN_MANAGER_PROTOCOL
{
	E_JOIN_INFO,
	E_LOGIN_INFO,
	E_JOIN_RESULT,
	E_LOGIN_RESULT,
	E_LOGOUT,
	E_LOGOUT_RESULT
};

#define IDSIZE 255
#define PWSIZE 255
#define NICKNAMESIZE 255

struct _User_Info
{
	char id[IDSIZE];
	char pw[PWSIZE];
	char nickname[NICKNAMESIZE];
};

//���漱�� ����
//class LoginSession;


class LoginManager : IOCP
{
private:
	//���������� ���������� ���°� ����
	//�̱������� ����
	std::list<_User_Info*> m_Join_List;
	char m_tmpbuf[BUFSIZE + 1];		// �Ŵ������� �Է¹��� ������ �����͸� ���� �۾���. �α��νý��ۿ� �Ѱ��ش�.

	//���漱�� ����
	//LoginSession* m_Session;

public:
	void Init();
	void Run();//accept() 
	void accepted(void* _object, int _bytes);
	void recved(void* _object, int _bytes);
	void sent(void* _object, int _bytes);
	void distroy();

	//init�Լ�. ��Ʈ ����

	BOOL SearchFile(char* filename);
	bool FileDataLoad();
	bool FileDataAdd(_User_Info* _info);
	void JoinProcess(_User_Info* _info);
	void LoginProcess(_User_Info* _info);
	void LogoutProcess(_User_Info* _info);
};