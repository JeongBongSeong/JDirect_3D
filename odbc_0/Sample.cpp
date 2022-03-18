#define _CRT_SECURE_NO_WARNINGS
#include"windows.h"
#include"sql.h"
#include"sqlext.h"
#include"tchar.h"
#include<iostream>
#include<string>
SQLHENV		g_hEnv;
SQLHDBC		g_hDbc;
SQLHSTMT	g_hStmt;

void Check()
{
	SQLTCHAR szSQLState[SQL_SQLSTATE_SIZE + 1];
	SQLTCHAR errorBuffer[SQL_MAX_MESSAGE_LENGTH + 1];
	SQLINTEGER iSQLCode;
	SQLSMALLINT length;
	SQLError(g_hEnv, g_hDbc,
		g_hStmt,
		szSQLState,
		&iSQLCode,
		errorBuffer,
		sizeof(errorBuffer),
		&length);
	MessageBox(NULL, errorBuffer, szSQLState, MB_OK);
}
void main()
{
	setlocale(LC_ALL, "");
	if (SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &g_hEnv)!= SQL_SUCCESS)
	{
		return;
	}

	//환경설정 3.8버전 쓴다는 내용
	if (SQLSetEnvAttr(g_hEnv, SQL_ATTR_ODBC_VERSION, (SQLPOINTER)SQL_OV_ODBC3_80, SQL_IS_INTEGER) != SQL_SUCCESS)
	{
		return;
	}

	if(SQLAllocHandle(SQL_HANDLE_DBC, g_hEnv, &g_hDbc )!=SQL_SUCCESS)
	{
		return;
	}
	SQLWCHAR dir[MAX_PATH] = { 0, };
	GetCurrentDirectory(MAX_PATH, dir);
	std::wstring dbpath = dir;
	dbpath += L"\\cigarette.accdb";
	//유니코드
	TCHAR InCon[256] = { 0, };
	TCHAR OutCon[1024] = { 0, };
	//_stprintf(lnCon, _T("DRIVER={Microsoft Access Driver (*.mdb, *.accdb)};DBQ=%s;"), dbpath.c_str());
	_stprintf(InCon, _T("FileDsn=%s"), _T("cigarette.accdb.dsn"));
	SQLSMALLINT cbOutLen;
	SQLRETURN ret = SQLDriverConnect(g_hDbc, NULL, InCon, _countof(InCon), OutCon, _countof(OutCon), &cbOutLen, SQL_DRIVER_NOPROMPT);
	if (ret != SQL_SUCCESS && ret != SQL_SUCCESS_WITH_INFO)
	{
		Check();
		return;
	}





	if(SQLAllocHandle(SQL_HANDLE_STMT, g_hDbc, &g_hStmt) != SQL_SUCCESS)
	{
		return;
	}
	
	SQLLEN lName, lPrice, lKorean;
	TCHAR Name[50];
	int Price;
	BOOL Korean;

	ret = SQLBindCol(g_hStmt, 1, SQL_UNICODE, Name, sizeof(Name), &lName);
	ret = SQLBindCol(g_hStmt, 2, SQL_C_ULONG, &Price, 0, &lPrice);
	ret = SQLBindCol(g_hStmt, 3, SQL_C_ULONG, &Korean, 0, &lKorean);

	TCHAR sql[MAX_PATH] = L"select * from tblCigar";
	ret = SQLExecDirect(g_hStmt, (SQLTCHAR*)&sql, SQL_NTS);

	while (SQLFetch(g_hStmt) != SQL_NO_DATA)
	{
		std::wcout << Name << Price << Korean;
	}
	SQLCloseCursor(g_hStmt);

	SQLFreeHandle(SQL_HANDLE_STMT, g_hStmt);
	SQLDisconnect(g_hDbc);
	SQLFreeHandle(SQL_HANDLE_DBC, g_hDbc);
	SQLFreeHandle(SQL_HANDLE_ENV, g_hEnv);
}