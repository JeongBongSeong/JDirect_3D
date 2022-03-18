#include "JSample.h"
// 메세지 기반 처리
// 윈도우의 각종 메세지 처리 함수(루틴)
// 운영체제 -> 메세지 전달(통지) -> 메세지 큐 저장 -> WinProc 호출
// 운영체제가 윈도우 영역안에 무슨일이 일어나면 처리하는 것 (마우스가 창안에 들어오는 등)
bool JSample::Init()
{
	return true;
}

bool JSample::Frame()
{
	return true;
}

bool JSample::Render()
{
	return true;
}

bool JSample::Release()
{
	return true;
}

GAME_RUN(JBS Title, 1024, 768)