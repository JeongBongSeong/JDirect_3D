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


// 전처리
// 1) 데이터 초기화 및 입력
FILE* Create();
// 2) 데이터 추가
int Insert(FILE* fp);
// 3) 로드 후 저장
void Load(int iCounter);
// 4) 화면 출력
void Draw(int iCounter);

void main(int argc, char* argv[]) 
{
	// 1) 데이터 초기화 및 입력
	FILE* fp = Create();
	// 2) 데이터 추가
	int iCounter = Insert(fp);
	// 3) 로드 후 저장
	Load(iCounter);
	// 4) 화면 출력
	Draw(iCounter);
}

// 1) 데이터 초기화 및 입력
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
// 2) 데이터 추가
int Insert(FILE* fp)
{
	int iCounter = 2 + MAX_USER;
	fwrite(&iCounter, sizeof(int), 1, fp);
	fseek(fp, 0, SEEK_END);	//파일 포인터를 끝으로 이동시킴
	fwrite(&userlist, sizeof(JUser), 2, fp);
	fclose(fp);
	return iCounter;
}
// 3) 로드 후 저장
void Load(int iCounter)
{
	userlistRead = (JUser*)malloc(sizeof(JUser) * iCounter); //읽을 유저 리스트의 크기 할당 iCount의 값을 곱하여 현재 저장된 최대 크기 만큼 확대
	FILE* fpRead = fopen("tester.txt", "r");
	int iCountRead = 0;
	if (fpRead != NULL)
	{
		fread(&iCountRead, sizeof(int), 1, fpRead);
		fread(userlistRead, sizeof(JUser), iCountRead, fpRead);
		fclose(fpRead);
	}
}
// 4) 화면 출력
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
