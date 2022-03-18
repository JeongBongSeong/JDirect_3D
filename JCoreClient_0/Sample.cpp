#define _CRT_SECURE_NO_WARNINGS
#define MAX_USER 2
#include <stdio.h>
#include <memory.h>
#include <stdlib.h>

struct JUser
{
	int iIndex;
	int iKor;
};

struct JReturn
{
	FILE* fp;
	JUser* list;
};

JUser userlist[MAX_USER];
JUser* userlistRead = 0;


// ��ó��
// 1) ������ �ʱ�ȭ �� �Է�
FILE* Create();
// 2) ������ �߰�
int Insert(FILE* fp);
// 3) �ε� �� ����
void Load(int iCounter);
// 4) ȭ�� ���
void Draw(int iCounter);

void main(int argc, char* argv[]) 
{
	// 1) ������ �ʱ�ȭ �� �Է�
	FILE* fp = Create();
	// 2) ������ �߰�
	int iCounter = Insert(fp);
	// 3) �ε� �� ����
	Load(iCounter);
	// 4) ȭ�� ���
	Draw(iCounter);
}

// 1) ������ �ʱ�ȭ �� �Է�
FILE* Create()
{
	userlist[0].iIndex = 2;
	userlist[0].iKor = 70;
	userlist[1].iIndex = 3;
	userlist[1].iKor = 60;

	FILE* fpWrite = fopen("tester.txt", "r+");
	if (fpWrite == NULL)
	{
		fpWrite = fopen("tester.txt", "w");
		int iCounter = MAX_USER;
		fwrite(&iCounter, sizeof(int), 1, fpWrite);
		fwrite(&userlist, sizeof(JUser), 2, fpWrite);
		fclose(fpWrite);
		fpWrite = fopen("tester.txt", "r+");
	}
	return fpWrite;
}
// 2) ������ �߰�
int Insert(FILE* fp)
{
	int iCounter = 2 + MAX_USER;
	fwrite(&iCounter, sizeof(int), 1, fp);
	fseek(fp, 0, SEEK_END);	//���� �����͸� ������ �̵���Ŵ
	fwrite(&userlist, sizeof(JUser), 2, fp);
	fclose(fp);
	return iCounter;
}
// 3) �ε� �� ����
void Load(int iCounter)
{
	userlistRead = (JUser*)malloc(sizeof(JUser) * iCounter); //���� ���� ����Ʈ�� ũ�� �Ҵ� iCount�� ���� ���Ͽ� ���� ����� �ִ� ũ�� ��ŭ Ȯ��
	FILE* fpRead = fopen("tester.txt", "r");
	int iCountRead = 0;
	if (fpRead != NULL)
	{
		fread(&iCountRead, sizeof(int), 1, fpRead);
		fread(userlistRead, sizeof(JUser), iCountRead, fpRead);
		fclose(fpRead);
	}
}
// 4) ȭ�� ���
void Draw(int iCounter)
{
	for (int iUser = 0;
		iUser < iCounter;
		iUser++)
	{
		printf("%d %d\n", userlistRead[iUser].iIndex, userlistRead[iUser].iKor);
	}
	free(userlistRead);
}
