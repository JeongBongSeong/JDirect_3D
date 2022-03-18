#include"JOdbc.h"

/* SQL extended datatypes */
/*
#define SQL_DATE                                9
#define SQL_TIME                                10
#define SQL_TIMESTAMP                           11
#define SQL_LONGVARCHAR                         (-1)
#define SQL_BINARY                              (-2)
#define SQL_VARBINARY                           (-3)
#define SQL_LONGVARBINARY                       (-4)
#define SQL_BIGINT                              (-5)
#define SQL_TINYINT                             (-6)
#define SQL_BIT                                 (-7)
*/
void main()
{
	setlocale(LC_ALL, "");
	JOdbc odbc;
	odbc.Init();

	

	odbc.Connect(0, L"");
	std::cout << "------------------------Select------------------------" << std::endl;
	odbc.ExecSelect(L"AllDataSelect");
	
	std::wstring id, pw;
	std::cout << "------------------------Insert------------------------" << std::endl;
	std::cout << "id : ";
	std::wcin >> id;
	std::cout << "pw : ";
	std::wcin >> pw;
	odbc.ExecInsert(L"{?=call AccountCreate(?,?)}",(TCHAR*)id.c_str(), (TCHAR*)pw.c_str());
	
	std::cout << "------------------------Update------------------------" << std::endl;
	std::cout << "id : ";
	std::wcin >> id;
	std::cout << "pw : ";
	std::wcin >> pw;

	TCHAR sql3[256] = { 0, };
	wsprintf(sql3, L"{call LoginUser('%s','%s')}",
		id.c_str(), pw.c_str());
	odbc.ExecQuery(sql3);
	
	TCHAR sql4[256] = { 0, };
	wsprintf(sql4, L"{call LogoutUser('%s')}",
		id.c_str());
	odbc.ExecQuery(sql4);
	std::cout << "------------------------Select------------------------" << std::endl;
	odbc.ExecSelect(L"AllDataSelect");
	std::cout << "------------------------Delete------------------------" << std::endl;
	std::cout << "id : ";
	std::wcin >> id;
	std::cout << "pw : ";
	std::wcin >> pw;
	TCHAR sql5[256] = { 0, };
	wsprintf(sql5, L"{call UserDelete('%s','%s')}",
		id.c_str(), pw.c_str());
	odbc.ExecQuery(sql5);
	std::cout << "------------------------Select------------------------" << std::endl;
	odbc.ExecSelect(L"AllDataSelect");
	odbc.Release();

	Sleep(10000);
}
