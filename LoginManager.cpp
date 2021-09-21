#include "LoginManager.h"
#include "LoginSession.h"

#define ID_ERROR_MSG "없는아이디\n"
#define PW_ERROR_MSG "잘못된패스워드.\n"
#define LOGIN_SUCCESS_MSG "로그인.\n"
#define ID_EXIST_MSG "아이디중복.\n"
#define JOIN_SUCCESS_MSG "가입완료.\n"
#define LOGOUT_MSG "로그아웃.\n"

void LoginManager::accepted(void* _object, int _bytes)
{


}

//메세지를 수신 완료한 이후 처리할 내용들
//_object의 내용 : 	사이즈, 실행 프로토콜, 결과 프로토콜, 실제 데이터
void LoginManager::recved(void* _object, int _bytes)
{
	_object		// overlappedex 구조체



	LOGIN_MANAGER_PROTOCOL protocol;
	_User_Info* tmp_User_Info;
	LoginSession loginsession;

	//1. loginsession이 state를 관리함.
	//2. 따라서 loginsession의 state에 접근하여 아래 내용을 처리해야함.
	//3. 그런데 매개변수로 받은 _object로는 어떤 loginsession인지 알 수 없음.
	// 
	//1. 부모클래스(IOCP)에 접근하여 HANDLE변수를 이용하는 방법도 못한다. HANDLE이 private임.
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
		case E_LOGOUT:								//일대일 매칭시켜줄것
			loginsession.PackPacket(_ptr->sendbuf, (PROTOCOL)E_LOGOUT_RESULT, (RESULT)E_LOGOUT_SUCCESS, LOGOUT_MSG, _ptr->sendbytes);
			_ptr->state = LOGOUT_RESULT_SEND_STATE;			스테이트
			break;

		}

	}



}

//메세지를 전송 완료한 이후 처리할 내용들
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