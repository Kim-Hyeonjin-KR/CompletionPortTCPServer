#pragma once

#include "global.h"
//#include "LoginSession.h"
//글로벌 헤더 파일에서는 최대한 중복을 최소화 하도록 변경할 것. 헤더 파일은 include를 최소화 할것. 전방선언으로 해결할 수 있다면 그렇게 처리할것.
//

#define ID "abcd"
#define PW 1234

// 사용자 정의 상태 <로그인>
// 아래 enum들 중 LoginSession.h가 더 적합한 것들은 뺄 수 있도록 할것

// UML만들어서 보기 쉽게 만들기
// 채팅 기록, 내용 등등 이어받기 구현할 수 있도록


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

//전방선언 예시
//class LoginSession;


class LoginManager : IOCP
{
private:
	//지역변수는 지역변수로 쓰는게 좋음
	//싱글톤으로 변경
	std::list<_User_Info*> m_Join_List;
	char m_tmpbuf[BUFSIZE + 1];		// 매니저에서 입력받은 순수한 데이터를 담을 작업대. 로그인시스템에 넘겨준다.

	//전방선언 예시
	//LoginSession* m_Session;

public:
	void Init();
	void Run();//accept() 
	void accepted(void* _object, int _bytes);
	void recved(void* _object, int _bytes);
	void sent(void* _object, int _bytes);
	void distroy();

	//init함수. 노트 참조

	BOOL SearchFile(char* filename);
	bool FileDataLoad();
	bool FileDataAdd(_User_Info* _info);
	void JoinProcess(_User_Info* _info);
	void LoginProcess(_User_Info* _info);
	void LogoutProcess(_User_Info* _info);
};