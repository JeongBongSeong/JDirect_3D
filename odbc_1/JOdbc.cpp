#include "JOdbc.h"


void JOdbc::Check()
{
	SQLTCHAR szSQLState[SQL_SQLSTATE_SIZE + 1];
	SQLTCHAR errorBuffer[SQL_MAX_MESSAGE_LENGTH + 1];
	SQLINTEGER iSQLCode;
	SQLSMALLINT length;
	SQLError(m_hEnv, m_hDbc,
		m_hStmt,
		szSQLState,
		&iSQLCode,
		errorBuffer,
		sizeof(errorBuffer),
		&length);
	MessageBox(NULL, errorBuffer, szSQLState, MB_OK);
}

JOdbc::JOdbc()
{
}
JOdbc::~JOdbc()
{
}
bool JOdbc::Init()
{

	if (SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &m_hEnv) != SQL_SUCCESS)
	{
		return FALSE;
	}

	//환경설정 3.8버전 쓴다는 내용
	if (SQLSetEnvAttr(m_hEnv, SQL_ATTR_ODBC_VERSION, (SQLPOINTER)SQL_OV_ODBC3_80, SQL_IS_INTEGER) != SQL_SUCCESS)
	{
		return FALSE;
	}

	if (SQLAllocHandle(SQL_HANDLE_DBC, m_hEnv, &m_hDbc) != SQL_SUCCESS)
	{
		return FALSE;
	}
	
	return TRUE;
}

bool JOdbc::Connect(int iType, const TCHAR* dsn)
{
	//유니코드
	TCHAR InCon[256] = { 0, };
	SQLRETURN ret;


	switch (iType)
	{
	case 0:
	{
		ret = SQLDriverConnect(m_hDbc, NULL,
			(SQLWCHAR*)L"Driver={SQL Server};SERVER=localhost, 1433; DATABASE=jbsgame; UID=sa; PWD=wjdqhtnwjd1!;", SQL_NTS,
			NULL, 1024, NULL, SQL_DRIVER_NOPROMPT);
	}break;

	case 1:
	{
		HWND hWnd = GetDesktopWindow();
		SQLSMALLINT len;
		ret = SQLDriverConnect(m_hDbc, hWnd,
			(SQLWCHAR*)L"Driver={SQL Server}", SQL_NTS,
			(SQLWCHAR*)InCon, _countof(InCon),
			&len, SQL_DRIVER_PROMPT);
	}break;
	}
	
	
	if (ret != SQL_SUCCESS && ret != SQL_SUCCESS_WITH_INFO)
	{
		Check();
		return FALSE;
	}
	if (SQLAllocHandle(SQL_HANDLE_STMT, m_hDbc, &m_hStmt) != SQL_SUCCESS)
	{
		return FALSE;
	}
	return TRUE;
}
bool JOdbc::Release()
{
	SQLFreeHandle(SQL_HANDLE_STMT, m_hStmt);
	SQLDisconnect(m_hDbc);
	SQLFreeHandle(SQL_HANDLE_DBC, m_hDbc);
	SQLFreeHandle(SQL_HANDLE_ENV, m_hEnv);
	return true;
}
bool JOdbc::ExecSelect(const TCHAR* sql)
{
	SQLRETURN ret;

	SQLLEN Iid, lUserid, lUserpw, IAccount, ILogin,ILogout;

	

	ret = SQLBindCol(m_hStmt, 1, SQL_C_ULONG, &m_Iid, 0, &Iid);
	ret = SQLBindCol(m_hStmt, 2, SQL_UNICODE, m_Userid, sizeof(m_Userid), &lUserid);
	ret = SQLBindCol(m_hStmt, 3, SQL_UNICODE, m_Userpw, sizeof(m_Userpw), &lUserpw);
	ret = SQLBindCol(m_hStmt, 4, SQL_UNICODE, m_Account, sizeof(m_Account), &IAccount);
	ret = SQLBindCol(m_hStmt, 5, SQL_UNICODE, m_Login, sizeof(m_Login), &ILogin);
	ret = SQLBindCol(m_hStmt, 6, SQL_UNICODE, m_Logout, sizeof(m_Logout), &ILogout);
	

	TCHAR sql4[MAX_PATH] = { 0, };// L"select name,price,korean from tblCigar='%s'";
	wsprintf(sql4, sql);//select * from gameuser");
	ret = SQLExecDirect(m_hStmt, (SQLTCHAR*)sql, SQL_NTS);
	if (ret != SQL_SUCCESS)
	{
		Check();
		return FALSE;
	}
	while (SQLFetch(m_hStmt) != SQL_NO_DATA)
	{
		std::wcout<< "index : " << m_Iid << "\tUserId : " << m_Userid << "\tAccount : " << m_Account << "\nLogin : " << m_Login << "\tLogout : " << m_Logout << std::endl;
		std::wcout << "------------------------------------------------------------------------------------------------\n";
		memset(m_Userid, 0, sizeof(SQLWCHAR)*256);
		memset(m_Userpw, 0, sizeof(SQLWCHAR) * 256);
		memset(m_Account, 0, sizeof(SQLWCHAR) * 256);
		memset(m_Login, 0, sizeof(SQLWCHAR) * 256);
		memset(m_Logout, 0, sizeof(SQLWCHAR) * 256);
	}


	SQLCloseCursor(m_hStmt);
	return true;
}
bool JOdbc::ExecInsert(const TCHAR* sql, TCHAR* id, TCHAR* pw)
{
	SQLRETURN retcode;
	SWORD sReturn1 = 0;
	TCHAR callsp[256] = { 0, };
	wsprintf(callsp, sql);
	retcode = SQLPrepare(m_hStmt, callsp, SQL_NTS);
	SQLLEN cbRetParam1 = SQL_NTS;
	retcode = SQLBindParameter(m_hStmt, 1, SQL_PARAM_OUTPUT,
		SQL_C_SSHORT, SQL_INTEGER, 0, 0, &sReturn1, 0, &cbRetParam1);

	SQLBindParameter(m_hStmt, 2, SQL_PARAM_INPUT, SQL_C_WCHAR, SQL_VARCHAR, 20, 0, (SQLWCHAR*)id, sizeof((SQLWCHAR*)id), NULL);

	SQLBindParameter(m_hStmt, 3, SQL_PARAM_INPUT, SQL_C_WCHAR, SQL_VARCHAR, 20, 0, (SQLWCHAR*)pw, sizeof((SQLWCHAR*)pw), NULL);
	retcode = SQLExecute(m_hStmt);							//2번
	if (retcode != SQL_SUCCESS && retcode != SQL_SUCCESS_WITH_INFO)
	{
		Check();
		return false;
	}
	while (SQLMoreResults(m_hStmt) != SQL_NO_DATA);
	SQLFreeStmt(m_hStmt, SQL_UNBIND);
	SQLFreeStmt(m_hStmt, SQL_RESET_PARAMS);
	SQLCloseCursor(m_hStmt);
}


bool JOdbc::ExecQuery(const TCHAR* sql)
{
	
	SQLRETURN ret;
	TCHAR sql4[MAX_PATH] = { 0, };// L"select name,price,korean from tblCigar='%s'";
	wsprintf(sql4, sql);
	ret = SQLExecDirect(m_hStmt, (SQLTCHAR*)&sql4, SQL_NTS);
	if (ret != SQL_SUCCESS)
	{
		Check();
		return FALSE;
	}


	SQLCloseCursor(m_hStmt);

	return true;
}
