#include "pch.h"
#include "Scene.h"


Scene::Scene()
{
}


Scene::~Scene()
{
}

bool Scene::Initialize()
{
	for (int i = 0; i < SIZE_Y; ++i)
	{
		for (int j = 0; j < SIZE_X; ++j)
		{
			m_SceneBuffer[i][j] = L'¡¡';
		}
		m_SceneBuffer[i][SIZE_X - 1] = L'\n';
	}
	
	return true;
}

void Scene::Render(HANDLE& frameBuffer)
{
	DWORD dw;
	COORD CursorPosition = { 0, 0 };
	SetConsoleCursorPosition(frameBuffer, CursorPosition);
	WriteConsoleW(frameBuffer, m_SceneBuffer, SIZE_X * SIZE_Y, &dw, NULL);
}
