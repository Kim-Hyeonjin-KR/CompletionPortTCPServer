#include "LoginManager.h"
#include "LoginSession.h"

#define ID_ERROR_MSG "���¾��̵�\n"
#define PW_ERROR_MSG "�߸����н�����.\n"
#define LOGIN_SUCCESS_MSG "�α���.\n"
#define ID_EXIST_MSG "���̵��ߺ�.\n"
#define JOIN_SUCCESS_MSG "���ԿϷ�.\n"
#define LOGOUT_MSG "�α׾ƿ�.\n"

void LoginManager::accepted(void* _object, int _bytes)
{


}

//�޼����� ���� �Ϸ��� ���� ó���� �����
//_object�� ���� : 	������, ���� ��������, ��� ��������, ���� ������
void LoginManager::recved(void* _object, int _bytes)
{
	_object		// overlappedex ����ü



	LOGIN_MANAGER_PROTOCOL protocol;
	_User_Info* tmp_User_Info;
	LoginSession loginsession;

	//1. loginsession�� state�� ������.
	//2. ���� loginsession�� state�� �����Ͽ� �Ʒ� ������ ó���ؾ���.
	//3. �׷��� �Ű������� ���� _object�δ� � loginsession���� �� �� ����.
	// 
	//1. �θ�Ŭ����(IOCP)�� �����Ͽ� HANDLE������ �̿��ϴ� ����� ���Ѵ�. HANDLE�� private��.
	loginsession.GetProtocol(ptr, (PROTOCOL&)protocol);

	switch (loginsession->state)
	{
	case E_MENU_SELECT_STATE:

		switch (protocol)
		{
		case E_JOIN_INFO:
			memset(&_ptr->userinfo, 0, sizeof(_User_Info));
			loginsession.UnPackPacket(, tmp_User_Info->id, tmp_User_Info->pw, tmp_User_Info->nickname);
			JoinProcess(_ptr);
			_ptr->state = E_JOIN_RESULT_SEND_STATE;
			break;
		case E_LOGIN_INFO:
			memset(&_ptr->userinfo, 0, sizeof(_User_Info));
			loginsession.UnPackPacket(_ptr->recvbuf, tmp_User_Info->id, tmp_User_Info->pw);
			LoginProcess(_ptr);
			_ptr->state = E_LOGIN_RESULT_SEND_STATE;
			break;
		}
		break;
	case E_LOGIN_STATE:
		switch (protocol)
		{
		case E_LOGOUT:								//�ϴ��� ��Ī�����ٰ�
			loginsession.PackPacket(_ptr->sendbuf, (PROTOCOL)E_LOGOUT_RESULT, (RESULT)E_LOGOUT_SUCCESS, LOGOUT_MSG, _ptr->sendbytes);
			_ptr->state = LOGOUT_RESULT_SEND_STATE;			������Ʈ
			break;

		}

	}



}

//�޼����� ���� �Ϸ��� ���� ó���� �����
void LoginManager::sent(void* object, int bytes)
{

	LoginSession* session = (LoginSession*)object;
	session->


	return false;
}

void LoginManager::distroy()
{



}



BOOL LoginManager::SearchFile(char* filename)
{


	return 0;
}

bool LoginManager::FileDataLoad()
{

	return false;
}

bool LoginManager::FileDataAdd(_User_Info* _info)
{


	return false;
}

void LoginManager::JoinProcess(_User_Info* _info)
{
	LOGIN_MANAGER_RESULT join_result = E_NODATA;
	char msg[BUFSIZE];
	int size;
	std::list<_User_Info*>::iterator iter;



	for (iter = m_Join_List.begin(); iter != m_Join_List.end(); iter++)
	{

		if (!strcmp((*iter)->id, _info->id))
		{
			join_result = E_ID_EXIST;
			strcpy(msg, ID_EXIST_MSG);
			break;
		}
	}

	if (join_result == E_NODATA)
	{
		_User_Info* user = new _User_Info;
		memset(user, 0, sizeof(_User_Info));
		strcpy(user->id, _info->id);
		strcpy(user->pw, _info->pw);
		strcpy(user->nickname, _info->nickname);
		FileDataAdd(user);

		m_Join_List.push_back(user);
		join_result = E_JOIN_SUCCESS;
		strcpy(msg, JOIN_SUCCESS_MSG);
	}

	memset(_info, 0, sizeof(_User_Info));

	LOGIN_MANAGER_PROTOCOL protocol = E_JOIN_RESULT;

	LoginSession loginsession;
	loginsession.PackPacket(m_tmpbuf, (PROTOCOL)protocol, (RESULT)join_result, msg, size);


	STATE state = E_RESULT_SEND_STATE;

	if (!loginsession.SendPack((PROTOCOL)protocol, m_tmpbuf))
	{
		state = E_DISCONNECTED_STATE;
	}
}

void LoginManager::LoginProcess(_User_Info* _info)
{
}

void LoginManager::LogoutProcess(_User_Info* _info)
{
}

void LoginManager::Run()
{
	while (1)
	{
		//SOCKET sock=accept();
		WSAOVERLAPPED_EX* ptr = new WSAOVERLAPPED_EX;
		ZeroMemory(ptr, sizeof(WSAOVERLAPPED_EX));
		ptr->type = E_IO_Accept;
		ptr->_ptr = sock;
		PostQueuedCompletionStatus()


	}
}