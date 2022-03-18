#include<Windows.h>
#include<sql.h>
#include<sqlext.h>
#include<iostream>
#include<tchar.h>
void Error(SQLHENV env, SQLHDBC dbc, SQLHSTMT stmt)
{
	SQLTCHAR buffer[SQL_MAX_MESSAGE_LENGTH + 1];
	SQLINTEGER sqlcode;
	SQLSMALLINT length;
	SQLSTATE sqlstate;

	while (SQLError(env, dbc, stmt, 
		sqlstate, &sqlcode,
		buffer, SQL_MAX_MESSAGE_LENGTH + 1,
		&length) == SQL_SUCCESS)
	{
		printf("%s", buffer);
	}
}
void main()
{
	SQLHENV henv = SQL_NULL_HENV;
	SQLHDBC hdbc = SQL_NULL_HDBC;
	SQLHSTMT hstmt = SQL_NULL_HSTMT;
	SQLRETURN retcode;

	SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &henv);

	SQLSetEnvAttr(henv, SQL_ATTR_ODBC_VERSION,
		(SQLPOINTER)SQL_OV_ODBC3_80, 0);

	SQLAllocHandle(SQL_HANDLE_DBC, henv, &hdbc);
	TCHAR dsn[] = L"";
	SQLSMALLINT cbCon;
	SQLTCHAR connStrbuffer[1024] = { 0, };
	retcode = SQLDriverConnect(hdbc, GetDesktopWindow(),
		(SQLTCHAR*)L"Driver={SQL Server}", SQL_NTS,
		(SQLTCHAR*)connStrbuffer, _countof(connStrbuffer), 
		&cbCon, SQL_DRIVER_PROMPT);

	retcode = SQLAllocHandle(SQL_HANDLE_STMT, hdbc, &hstmt);
	
	

}