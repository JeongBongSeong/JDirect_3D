#pragma once
#include "JProtocol.h"
#include <string>

// TPacket data;
// data << header << index << name << damage << mesage;
// data >> header >> index >> name >> damage >> mesage;
class JPacket
{
public:
	char* m_pOffset;
	char* c_str() { return m_pOffset; }
	UPACKET m_uPacket;
	void PutData(const char* pData, int iSize);
	void GetData(const char* pData, int iSize);
public:
	JPacket& operator << (int data);
	JPacket& operator << (long data);
	JPacket& operator << (short data);
	JPacket& operator << (float data);
	JPacket& operator << (byte data);
	JPacket& operator << (char* data);
	JPacket& operator << (DWORD data);
	JPacket& operator << (std::string data);
public:
	JPacket& operator >> (int& data);
	JPacket& operator >> (long& data);
	JPacket& operator >> (short& data);
	JPacket& operator >> (float& data);
	JPacket& operator >> (byte& data);
	JPacket& operator >> (char* data);
	JPacket& operator >> (DWORD& data);
	JPacket& operator >> (std::string& data);
public:
	JPacket();
	JPacket(WORD iType);
	JPacket(const JPacket& packet);
	~JPacket();
};