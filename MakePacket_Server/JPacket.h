#pragma once
#include"JProtocol.h"
#include<string>

class JPacket
{
public:
	char* m_pOffset;
	UPACKET m_uPacket;

public:
	void PutData(const char* pData, int iSize);
	void GetData(const char* pData, int iSize);
public:
	//Put
	JPacket& operator << (long data);
	JPacket& operator << (int data);
	JPacket& operator << (short data);
	JPacket& operator << (float data);
	JPacket& operator << (byte data);
	JPacket& operator << (DWORD data);
	JPacket& operator << (char* data);
	JPacket& operator << (std::string data);
	
	//Get
	JPacket& operator >> (long& data);
	JPacket& operator >> (int& data);
	JPacket& operator >> (short& data);
	JPacket& operator >> (float& data);
	JPacket& operator >> (byte& data);
	JPacket& operator >> (DWORD& data);
	JPacket& operator >> (char* data);
	JPacket& operator >> (std::string& data);

public:
	JPacket();
	JPacket(WORD iType);
	JPacket(const JPacket& packet);
	~JPacket();
};

