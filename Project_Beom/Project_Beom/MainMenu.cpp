#include "pch.h"
#include "MainMenu.h"
#include "InputManager.h"
#include "SceneManager.h"
#include "InfoManager.h"

MainMenu::MainMenu()
{
}

MainMenu::~MainMenu()
{
}

bool MainMenu::Initialize()
{
	Scene::Initialize();

	wstring title;
	title += L"\n\n\n\n\n\n\n\n\n\n";
	title += L"                 ����������������\n";
	title += L"                 �����  ����    ������\n";
	title += L"                 �����  T E T R I S ���  ��\n";
	title += L"                 ������  ��  ��  ������\n";
	title += L"                 ���  �������������\n";
	title += L"                  https://lipcoder.tistory.com/ \n\n";
	title += L"                 Please Enter Any Key to Start.. \n";
	title += L"                   ��   : Shift\n";
	title += L"                 ��  �� : Left / Right\n";
	title += L"                   ��   : Soft Drop\n";
	title += L"                  SPACE : Hard Drop\n";

	lstrcpy(m_SceneBuffer[INTERVAL_Y], title.c_str());
	GETMGR(InfoManager)->LoadFile();

	return true;
}

int MainMenu::Update(const float& timeDelta)
{
	int key = GETMGR(InputManager)->GetInputKey();
	if (NO_INPUT != key)
		GETMGR(SceneManager)->ChangeScene(SCENE_STAGE);
	
	return 0;
}

void MainMenu::Render(HANDLE& frameBuffer)
{
	Scene::Render(frameBuffer);
}

void MainMenu::Release()
{
}
