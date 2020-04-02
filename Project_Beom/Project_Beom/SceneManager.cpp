#include "pch.h"
#include "SceneManager.h"
#include "Stage.h"
#include "MainMenu.h"

SceneManager::SceneManager()
{
}

SceneManager::~SceneManager()
{
}

bool SceneManager::Initialize()
{
	return false;
}

void SceneManager::Release()
{
}

void SceneManager::ChangeScene(SCENE curScene)
{
	if (curScene == m_currentScene)
		return;

	if (nullptr != m_Scene)
		SAFE_RELEASE(m_Scene);
	
	switch (curScene)
	{
	case SCENE_MENU: m_Scene = new MainMenu; break;
	case SCENE_STAGE: m_Scene = new Stage; break;
	}

	m_Scene->Initialize();
	m_currentScene = curScene;
}

int SceneManager::Update(const float& timeDelta)
{
	m_Scene->Update(timeDelta);

	return 0;
}

void SceneManager::Render(HANDLE& frameBuffer)
{
	m_Scene->Render(frameBuffer);
}
