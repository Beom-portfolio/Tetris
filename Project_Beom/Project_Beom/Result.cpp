#include "pch.h"
#include "Result.h"
#include "InputManager.h"
#include "SceneManager.h"
#include "InfoManager.h"

Result::Result()
{
}

Result::~Result()
{
}

bool Result::Initialize()
{
	Scene::Initialize();

	wstring title;
	wstring score;
	WCHAR scoreArr[10];
	wsprintf(scoreArr, L"%6d", GETMGR(InfoManager)->GetCurrentScore());
	score = scoreArr;
	title += L"\n\n\n\n\n\n";
	title += L"              �ǢǢǢǢǢǢǢǢǢǢǢǢǢǢǢǢ�\n";
	title += L"              ��                              ��\n";
	title += L"              ��  +-----------------------+   ��\n";
	title += L"              ��  |  G A M E  O V E R..   |   ��\n";
	title += L"              ��  +-----------------------+   ��\n";
	title += L"              ��   YOUR SCORE: " + score + L"         ��\n";
	title += L"              ��                              ��\n";
	title += L"              ��  Press any key to restart..  ��\n";
	title += L"              ��                              ��\n";
	title += L"              �ǢǢǢǢǢǢǢǢǢǢǢǢǢǢǢǢ�\n";

	lstrcpy(m_SceneBuffer[INTERVAL_Y], title.c_str());
	GETMGR(InfoManager)->SaveFile();

	return true;
}

int Result::Update(const float& timeDelta)
{
	int key = GETMGR(InputManager)->GetInputKey();
	if (NO_INPUT != key)
		GETMGR(SceneManager)->ChangeScene(SCENE_MENU);

	return 0;
}

void Result::Render(HANDLE& frameBuffer)
{
	Scene::Render(frameBuffer);
}

void Result::Release()
{
}
