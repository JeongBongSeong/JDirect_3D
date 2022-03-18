#include"JClient.h"

void main()
{
	JClient client;
	client.InitClient();
	client.Run();
	client.Release();
}