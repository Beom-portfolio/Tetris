#include "pch.h"
#include "Stage.h"


Stage::Stage()
{
}

Stage::~Stage()
{
}

bool Stage::Initialize()
{
	// 벽 만들기
	// 맨 마지막 줄은 모두 벽
	// 나머지는 앞뒤로 벽
	for (int i = 0; i < SIZE_Y; ++i)
	{
		for (int j = 0; j < SIZE_X; ++j)
		{
			m_SceneBuffer[i][j] = L'　';
		}
		m_SceneBuffer[i][SIZE_X - 1] = L'\n';
	}


	for (int i = 0; i < BOARD_SIZE_Y; ++i)
	{
		for (int j = 0; j < BOARD_SIZE_X; ++j)
		{
			if (BOARD_SIZE_Y == i + 1)
				m_Board[i][j] = BOARD_WALL;
			else if (0 == j % (BOARD_SIZE_X - 1) || 1 == j / (BOARD_SIZE_X - 1))
				m_Board[i][j] = BOARD_WALL;
			else
				m_Board[i][j] = BOARD_EMPTY;
		}
	}

	for (int i = 1; i < BOARD_SIZE_X - 1; ++i)
	{
		m_Board[0][i] = BOARD_LINE;
	}

	return true;
}

int Stage::Update(const float & timeDelta)
{

	return 0;
}

void Stage::Render(HANDLE& frameBuffer)
{
	for (int i = 0; i < BOARD_SIZE_Y; ++i)
	{
		for (int j = 0; j < BOARD_SIZE_X; ++j)
		{
			switch (m_Board[i][j])
			{
			case BOARD_EMPTY: 
				m_SceneBuffer[i + m_intervalY][j + m_intervalX] = L'　'; break;
			case BOARD_WALL:  
				m_SceneBuffer[i + m_intervalY][j + m_intervalX] = L'□'; break;
			case BOARD_LINE:
				m_SceneBuffer[i + m_intervalY][j + m_intervalX] = L'＿'; break;
			}
		}
	}

	DWORD dw;
	COORD CursorPosition = {0, 0};
	SetConsoleCursorPosition(frameBuffer, CursorPosition);
	WriteConsoleW(frameBuffer, m_SceneBuffer, SIZE_X * SIZE_Y, &dw, NULL);
	//WriteFile(frameBuffer, m_SceneBuffer, sizeof(m_SceneBuffer), &dw, NULL);
}

void Stage::Release()
{
}
