#include "pch.h"
#include "Maingame.h"
#include "SceneManager.h"

Maingame::Maingame()
{
}

Maingame::~Maingame()
{
	CloseHandle(m_FrameBuffer[0]);
	CloseHandle(m_FrameBuffer[1]);
	DESTROYMGR(SceneManager);
}

bool Maingame::Initialize()
{

	m_FrameBuffer[0] = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE,
		0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);

	m_FrameBuffer[1] = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE,
		0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);

	CONSOLE_CURSOR_INFO cci;
	cci.bVisible = FALSE;
	cci.dwSize = 1;
	SetConsoleCursorInfo(m_FrameBuffer[0], &cci);
	SetConsoleCursorInfo(m_FrameBuffer[1], &cci);

	m_SceneMgr = GETMGR(SceneManager);
	m_SceneMgr->ChangeScene(SCENE_STAGE);

	return true;
}

void Maingame::Logic()
{
	while (true)
	{
		m_SceneMgr->Update(0.f);

		Flipping();
		Clear();
		m_SceneMgr->Render(m_FrameBuffer[m_currentBuffer]);
	}
}

void Maingame::Flipping()
{
	SetConsoleActiveScreenBuffer(m_FrameBuffer[m_currentBuffer]);
	m_currentBuffer = !m_currentBuffer;
}

void Maingame::Clear()
{
	COORD Coor = { 0, 0 };
	DWORD dw;
	FillConsoleOutputCharacter(m_FrameBuffer[m_currentBuffer], ' ', SIZE_X * SIZE_Y, Coor, &dw);
}
