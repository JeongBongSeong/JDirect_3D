#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include"windows.h"
#include"sql.h"
#include"sqlext.h"
#include"tchar.h"
#include<iostream>
#include<istream>
#include<string>


class JOdbc
{
public:
	SQLHENV		m_hEnv;
	SQLHDBC		m_hDbc;
	SQLHSTMT	m_hStmt;
public:
	SQLWCHAR m_Userid[256],m_Userpw[256],m_Account[256], m_Login[256], m_Logout[256];
	SQLINTEGER m_Iid;
	
public:
	JOdbc();
	~JOdbc();
public:
	
	bool Init();
	bool Connect(int iType, const TCHAR* dsn);
	bool Release();
	bool ExecSelect(const TCHAR* sql);
	bool ExecInsert(const TCHAR* sql, TCHAR* id, TCHAR* pw);
	bool ExecQuery(const TCHAR* sql);


	
	void Check();
	

};

