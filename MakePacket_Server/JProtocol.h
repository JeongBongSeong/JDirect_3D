#pragma once
//#include<iostream>
#include<windows.h>

#pragma pack(push, 1)

typedef struct {
	WORD len;
	WORD type;
}PACKET_HEADER;

typedef struct {
	PACKET_HEADER	ph;
	char			msg[4096];
}UPACKET, *P_UPACKET;

struct JChatMsg
{
	long index;
	char name[20];
	long damage;
	char msg[2048];
};
#pragma pack(pop)

#define PACKET_HEADER_SIZE	4
#define PACKET_CHAT_MSG		1000
/*
* msg = "¾È³ç";
* UPACKET sendPacket;
* sendPacket.ph.len = strlen(msg) + PACKET_HEADER SIZE;
* sendPacket.ph.type = ;
* sendPacket.msg = ;
*/
/*
* JChatting msg;
* msg.name = "È«±æµ¿";
* msg.msg = "¾È³ç";
* UPACKET sendPacket;
* sendPacket.ph.len = strlen(msg) + PACKET_HEADER SIZE;
* sendPacket.ph.type = ;
* sendPacket.msg = ;
*/