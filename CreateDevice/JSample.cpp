#include "JSample.h"
// �޼��� ��� ó��
// �������� ���� �޼��� ó�� �Լ�(��ƾ)
// �ü�� -> �޼��� ����(����) -> �޼��� ť ���� -> WinProc ȣ��
// �ü���� ������ �����ȿ� �������� �Ͼ�� ó���ϴ� �� (���콺�� â�ȿ� ������ ��)
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