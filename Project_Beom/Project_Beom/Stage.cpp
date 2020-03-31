#include "pch.h"
#include "Stage.h"
#include "Block.h"
#include "InputManager.h"

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
	UpdateObject(timeDelta);
	UpdateInput();
	UpdateCollision();
	UpdateBoard();

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
			case BOARD_BLOCK:
				m_SceneBuffer[i + m_intervalY][j + m_intervalX] = L'■'; break;
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

int Stage::UpdateObject(const float& timeDelta)
{
	if (nullptr == m_Block)
	{
		m_Block = new Block(BLOCK_MIDDLE);
		m_Block->Initialize();
		m_Block->SetPos(5, 0);
		m_Block->SetSpeed(0.5);
	}
	m_Block->Update(timeDelta);

	return 0;
}

int Stage::UpdateBoard()
{
	RenewBoard();

	// block
	SHAPE& shapeInfo = ((Block*)m_Block)->GetShape();
	int shapePosX, shapePosY;
	m_Block->GetPos(shapePosX, shapePosY);
	for (int y = 0; y < 4; ++y)
	{
		if (y + shapePosY < 0)
			continue;

		for (int x = 0; x < 4; ++x)
		{
			if (shapeInfo.shape[y][x] == 1)
				m_Board[y + shapePosY][x + shapePosX] = BOARD_BLOCK;
		}
	}

	return 0;
}

int Stage::UpdateInput()
{
	int key = GETMGR(InputManager)->GetInputKey();
	int shapePosX, shapePosY;
	m_Block->GetPos(shapePosX, shapePosY);
	switch (key)
	{
	case ARROW_LEFT:
		shapePosX -= 1; break;
	case ARROW_RIGHT:
		shapePosX += 1; break;
	}

	m_Block->SetPosX(shapePosX);

	return 0;
}

int Stage::UpdateCollision()
{

	return 0;
}

void Stage::RenewBoard()
{
	// clear
	for (int i = 0; i < BOARD_SIZE_Y - 1; ++i)
	{
		for (int j = 1; j < BOARD_SIZE_X - 1; ++j)
		{
			if (BOARD_BLOCK == m_Board[i][j])
				m_Board[i][j] = BOARD_EMPTY;
		}
	}
	for (int i = 1; i < BOARD_SIZE_X - 1; ++i)
	{
		m_Board[0][i] = BOARD_LINE;
	}
}
