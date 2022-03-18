#pragma once
#include <windows.h>
#define PACKET_HEADER_SIZE 4

#pragma pack(push, 1)
typedef struct {
	WORD len;
	WORD type;
}PACKET_HEADER;

typedef struct {
	PACKET_HEADER	ph;
	char			msg[4096];
}UPACKET, * P_UPACKET;

struct JChatMsg
{
	long	index;
	char	name[20]; // 全辨悼
	short	damage;
	char	message[256];// 救崇窍技咯.
};
#pragma pack(pop)

#define PACKET_CHAT_MSG      1000
/*
* msg = "救崇";
* UPACKET sendPacket;
* sendPacket.ph.len = strlen(msg) + PACKET_HEADER_SIZE;
* sendPacket.ph.type = PACKET_CHAT_MSG;
* sendPacket.msg = msg;
*/

/*
* TChatMsg msg;
* msg.name = "全辨悼";
* msg.message = "救崇窍技咯.";
* UPACKET sendPacket;
* sendPacket.ph.len = strlen(msg) + PACKET_HEADER_SIZE;
* sendPacket.ph.type = PACKET_CHAT_MSG;
* sendPacket.msg = msg;
*/