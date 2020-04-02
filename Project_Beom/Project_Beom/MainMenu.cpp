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
	title += L"                 ¡á¡à¡à¡à¡á¡á¡á¡à¡à¡á¡á¡à¡à¡á¡á\n";
	title += L"                 ¡á¡á¡á¡à  ¡á¡à¡à    ¡á¡á¡à¡à¡á\n";
	title += L"                 ¡à¡à¡à¡á  T E T R I S ¡à¡á  ¡á\n";
	title += L"                 ¡á¡á¡à¡á¡á  ¡à  ¡á  ¡à¡à¡á¡à¡à\n";
	title += L"                 ¡á¡á  ¡á¡à¡à¡à¡á¡á¡á¡à¡á¡á¡à¡à\n";
	title += L"                  https://lipcoder.tistory.com/ \n\n";
	title += L"                 Please Enter Any Key to Start.. \n";
	title += L"                   ¡â   : Shift\n";
	title += L"                 ¢·  ¢¹ : Left / Right\n";
	title += L"                   ¡ä   : Soft Drop\n";
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
