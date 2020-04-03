#include "pch.h"
#include "Stage.h"
#include "Block.h"
#include "InputManager.h"
#include "SceneManager.h"
#include "InfoManager.h"

Stage::Stage()
{
}

Stage::~Stage()
{
}

bool Stage::Initialize()
{
	Scene::Initialize();

	// 벽 만들기
	// 맨 마지막 줄은 모두 벽
	// 나머지는 앞뒤로 벽
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
		m_Board[GAME_OVER_LINE][i] = BOARD_LINE;
	}

	NextBlock();
	MakeBlock();

	m_bestScore = GETMGR(InfoManager)->GetBestScore();

	return true;
}

int Stage::Update(const float & timeDelta)
{
	if (CheckGameOver())
	{
		GETMGR(InfoManager)->SetCurrentScore(m_score);
		GETMGR(SceneManager)->ChangeScene(SCENE_RESULT);
		return 0;
	}

	if (m_waitCheck)
		m_timeForWait += timeDelta;
	else
		UpdateObject(timeDelta);

	UpdateLineClear();
	UpdateInput();
	UpdateCollision();
	UpdateStatus();
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
				m_SceneBuffer[i + INTERVAL_Y][j + INTERVAL_X] = L'　'; break;
			case BOARD_WALL:  
				m_SceneBuffer[i + INTERVAL_Y][j + INTERVAL_X] = L'▦'; break;
			case BOARD_BLOCK:
				m_SceneBuffer[i + INTERVAL_Y][j + INTERVAL_X] = L'□'; break;
			case BOARD_ARRANGED:
				m_SceneBuffer[i + INTERVAL_Y][j + INTERVAL_X] = L'■'; break;
			case BOARD_WILL:
				m_SceneBuffer[i + INTERVAL_Y][j + INTERVAL_X] = L'▣'; break;
			case BOARD_LINE:
				m_SceneBuffer[i + INTERVAL_Y][j + INTERVAL_X] = L'＿'; break;
			}
		}
	}
	Scene::Render(frameBuffer);
}

void Stage::Release()
{
	SAFE_DELETE(m_Block);
}

int Stage::UpdateObject(const float& timeDelta)
{
	m_Block->Update(timeDelta);
	return 0;
}

int Stage::UpdateBoard()
{
	RenewBoard();

	if (nullptr == m_Block)
		return 0;
	// block
	int shapeInfo[4][4]; 
	((Block*)m_Block)->GetShape(shapeInfo);
	int shapePosX, shapePosY;
	m_Block->GetPos(shapePosX, shapePosY);

	// 놓일 위치를 보여줄 블록
	for (int willY = shapePosY; willY < BOARD_SIZE_Y; ++willY)
	{
		if (!CheckCollision(shapePosX, willY + 1))
		{
			int count = 0;
			for (int y = 0; y < 4; ++y)
			{
				if (y + willY < 0)
					continue;

				for (int x = 0; x < 4; ++x)
				{
					if (shapeInfo[y][x] == 1)
					{
						m_Board[y + willY][x + shapePosX] = BOARD_WILL;
						m_willShapePos[count].x = x + shapePosX;
						m_willShapePos[count].y = y + willY;
						++count;
					}
				}
			}
			break;
		}
	}

	// 현재 블록
	for (int y = 0; y < 4; ++y)
	{
		if (y + shapePosY < 0)
			continue;

		for (int x = 0; x < 4; ++x)
		{
			if (shapeInfo[y][x] == 1)
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
		if (CheckCollision(shapePosX - 1, shapePosY))
			shapePosX -= 1; 
		m_Block->SetPosX(shapePosX);
		break;
	case ARROW_RIGHT: 
		if (CheckCollision(shapePosX + 1, shapePosY))
			shapePosX += 1; 
		m_Block->SetPosX(shapePosX);
		break;
	case ARROW_UP:
		((Block*)m_Block)->Rotate();
		if(!CheckCollision(shapePosX, shapePosY))
			((Block*)m_Block)->Rotate(false);
		break;
	case ARROW_DOWN: 
		shapePosY += 1;
		m_Block->SetPosY(shapePosY);
		// 블록을 계속해서 내리고 있으면 바로 배치한다.
		if (CheckCollision(shapePosX, shapePosY))
			break;
	case SPACE:
		for (int i = 0; i < 4; ++i)
		{
			m_Board[m_willShapePos[i].y][m_willShapePos[i].x] = BOARD_ARRANGED;
		}
		SAFE_DELETE(m_Block);

		if(!CheckGameOver())
			MakeBlock();
		break;
	}

	return 0;
}

int Stage::UpdateCollision()
{
	if (nullptr == m_Block)
		return 0;

	int shapePosX, shapePosY;
	m_Block->GetPos(shapePosX, shapePosY);

	int shapeInfo[4][4];
	((Block*)m_Block)->GetShape(shapeInfo);
	if (!CheckCollision(shapePosX, shapePosY + 1))
	{
		if (!m_waitCheck)
		{
			m_waitCheck = true;
			m_event = EVENT_ARRANGE;
		}
	}
	else if(EVENT_ARRANGE == m_event)
	{
		m_waitCheck = false;
		m_timeForWait = 0.f;
	}

	// 블럭이 곧 배치되려고 하는 경우 
	// 1초정도 놓을 시간을 주고 배치
	if (m_waitCheck && 
		EVENT_ARRANGE == m_event && 
		2.f <= m_timeForWait)
	{
		m_waitCheck = false;
		m_timeForWait = 0.f;

		for (int i = 0; i < 4; ++i)
		{
			m_Board[m_willShapePos[i].y][m_willShapePos[i].x] = BOARD_ARRANGED;
		}

		SAFE_DELETE(m_Block);
		MakeBlock();
	}

	return 0;
}

int Stage::UpdateLineClear()
{
	// 라인 검사
	// 범위 y축 0번째는 게임오버 BOARD_SIZE_Y - 1번째는 벽
	// 범위 x축 0번째와 BOARD_SIZE_X - 1번째는 벽

	int lineClearCount = 0;

	for (int y = GAME_OVER_LINE + 1; y < BOARD_SIZE_Y - 1; ++y)
	{
		int count = 0;
		for (int x = 1; x < BOARD_SIZE_X - 1; ++x)
		{
			if (BOARD_ARRANGED == m_Board[y][x])
				++count;
		}
		if (BOARD_SIZE_X - 2 == count)
		{
			++lineClearCount;
			// 라인 삭제
			memset(&m_Board[y][1], BOARD_EMPTY, sizeof(int) * (BOARD_SIZE_X - 2));

			// 앞으로 땡기기
			for (int pull_y = y - 1; pull_y >= GAME_OVER_LINE + 1; --pull_y)
			{
				memcpy(&m_Board[pull_y + 1][1], &m_Board[pull_y][1], sizeof(int) * (BOARD_SIZE_X - 2));
			}

			// 마지막 줄은 땡겨주는 작업을 하면 안되므로(라인줄모양이 땡겨져옴) 그냥 비워준다. 
			memset(&m_Board[GAME_OVER_LINE + 1][1], BOARD_EMPTY, sizeof(int) * (BOARD_SIZE_X - 2));

		}
	}

	if (0 < lineClearCount)
	{
		m_goal -= lineClearCount;
		m_score += 100 * m_level * (lineClearCount + (lineClearCount - 1));

		if (0 >= m_goal)
		{
			++m_level;
			m_goal = 5 * m_level;
		}
	}

	return 0;
}

int Stage::UpdateStatus()
{
	wstring temp;
	temp = L"LEVEL  : " + to_wstring(m_level);
	lstrcpy(&m_SceneBuffer[INTERVAL_Y + 1][STATUS_X], temp.c_str());
	temp = L"GOAL   : " + to_wstring(m_goal);
	lstrcpy(&m_SceneBuffer[INTERVAL_Y + 3][STATUS_X], temp.c_str());

	temp = L"+-　N E X T　-+";
	lstrcpy(&m_SceneBuffer[INTERVAL_Y + 6][STATUS_X], temp.c_str());
	
	for (int y = 0; y < 4; ++y)
	{
		temp = L"|　　　　　 　|";
		
		for (int x = 0; x < 4; ++x)
		{
			if(1 == m_NextShape[y][x])
				temp[x + 2] = L'□';
		}
		
		lstrcpy(&m_SceneBuffer[INTERVAL_Y + 7 + y][STATUS_X], temp.c_str());
	}

	temp = L"+--  - - -  --+";
	lstrcpy(&m_SceneBuffer[INTERVAL_Y + 11][STATUS_X], temp.c_str());

	temp = L"YOUR SCORE  : " + to_wstring(m_score);
	lstrcpy(&m_SceneBuffer[INTERVAL_Y + 14][STATUS_X], temp.c_str());

	temp = L"BEST SCORE  : " + to_wstring(m_bestScore);
	lstrcpy(&m_SceneBuffer[INTERVAL_Y + 16][STATUS_X], temp.c_str());

	temp = L"  △   : Shift";
	lstrcpy(&m_SceneBuffer[INTERVAL_Y + 18][STATUS_X], temp.c_str());
	temp = L"◁  ▷ : Left / Right";
	lstrcpy(&m_SceneBuffer[INTERVAL_Y + 19][STATUS_X], temp.c_str());
	temp = L"  ▽   : Soft Drop";
	lstrcpy(&m_SceneBuffer[INTERVAL_Y + 20][STATUS_X], temp.c_str());
	temp = L" SPACE : Hard Drop";
	lstrcpy(&m_SceneBuffer[INTERVAL_Y + 21][STATUS_X], temp.c_str());

	return 0;
}

bool Stage::CheckCollision(int x, int y)
{
	int shapeInfo[4][4];
	((Block*)m_Block)->GetShape(shapeInfo);
	for (int i = 0; i < 4; ++i)
	{
		for (int j = 0; j < 4; ++j)
		{
			if (1 == shapeInfo[i][j])
			{
				if (BOARD_WALL == m_Board[i + y][j + x] ||
					BOARD_ARRANGED == m_Board[i + y][j + x])
					return false;	
			}
		}
	}

	return true;
}

bool Stage::CheckGameOver()
{
	for (int y = GAME_OVER_LINE; y >= 0; --y)
	{
		for (int x = 1; x < BOARD_SIZE_X - 1; ++x)
		{
			if (BOARD_ARRANGED == m_Board[y][x])
				return true;
		}
	}
	return false;
}

void Stage::RenewBoard()
{
	// clear
	for (int i = 0; i < BOARD_SIZE_Y - 1; ++i)
	{
		for (int j = 1; j < BOARD_SIZE_X - 1; ++j)
		{
			if (BOARD_BLOCK == m_Board[i][j] || BOARD_WILL == m_Board[i][j])
				m_Board[i][j] = BOARD_EMPTY;
		}
	}
	for (int i = 1; i < BOARD_SIZE_X - 1; ++i)
	{
		m_Board[BOARD_SIZE_Y - 1][i] = BOARD_WALL;

		if(BOARD_ARRANGED != m_Board[GAME_OVER_LINE][i])
			m_Board[GAME_OVER_LINE][i] = BOARD_LINE;
	}
}

void Stage::MakeBlock()
{
	if (nullptr == m_Block)
	{
		// 블럭
		m_Block = new Block(m_nextBlockStyle, m_nextRotState);
		m_Block->Initialize();
		m_Block->SetPos(4, 0);
		m_Block->SetSpeed((float)m_level);
	}

	NextBlock();
}

void Stage::NextBlock()
{
	random_device rd;
	mt19937_64 mt(rd());

	uniform_int_distribution<int> range_style(0, BLOCK_END - 1);
	int rand_style = range_style(mt);

	uniform_int_distribution<int> range_rot(0, ROTATE_END - 1);
	int rand_rot = range_rot(mt);

	m_nextBlockStyle = BLOCK_STYLE(rand_style);
	m_nextRotState = BLOCK_ROTATE(rand_rot);

	switch (m_nextBlockStyle)
	{
	case BLOCK_SQUARE:
	{
		int square[ROTATE_END][4][4] = {
		{{0, 0, 0, 0},
		 {0, 1, 1, 0},
		 {0, 1, 1, 0},
		 {0, 0, 0, 0}},
		{{0, 0, 0, 0},
		 {0, 1, 1, 0},
		 {0, 1, 1, 0},
		 {0, 0, 0, 0}},
		{{0, 0, 0, 0},
		 {0, 1, 1, 0},
		 {0, 1, 1, 0},
		 {0, 0, 0, 0}},
		{{0, 0, 0, 0},
		 {0, 1, 1, 0},
		 {0, 1, 1, 0},
		 {0, 0, 0, 0}} };
		memcpy(m_NextShape, square[m_nextRotState], sizeof(int) * (4 * 4));
		break;
	}
	case BLOCK_LINE:
	{
		int line[ROTATE_END][4][4] = {
		{{0, 1, 0, 0},
		 {0, 1, 0, 0},
		 {0, 1, 0, 0},
		 {0, 1, 0, 0}},
		{{0, 0, 0, 0},
		 {0, 0, 0, 0},
		 {1, 1, 1, 1},
		 {0, 0, 0, 0}},
		{{0, 1, 0, 0},
		 {0, 1, 0, 0},
		 {0, 1, 0, 0},
		 {0, 1, 0, 0}},
		{{0, 0, 0, 0},
		 {0, 0, 0, 0},
		 {1, 1, 1, 1},
		 {0, 0, 0, 0}} };
		memcpy(m_NextShape, line[m_nextRotState], sizeof(int) * (4 * 4));
		break;
	}
	case BLOCK_MIDDLE:
	{
		int middle[ROTATE_END][4][4] = {
		{{0, 0, 0, 0},
		 {0, 0, 1, 0},
		 {0, 1, 1, 1},
		 {0, 0, 0, 0}},
		{{0, 0, 0, 0},
		 {0, 0, 1, 0},
		 {0, 0, 1, 1},
		 {0, 0, 1, 0}},
		{{0, 0, 0, 0},
		 {0, 1, 1, 1},
		 {0, 0, 1, 0},
		 {0, 0, 0, 0}},
		{{0, 0, 0, 0},
		 {0, 0, 1, 0},
		 {0, 1, 1, 0},
		 {0, 0, 1, 0}} };
		memcpy(m_NextShape, middle[m_nextRotState], sizeof(int) * (4 * 4));
		break;
	}
	case BLOCK_TWIST:
	{
		int twist[ROTATE_END][4][4] = {
		{{0, 0, 0, 0},
		 {0, 1, 0, 0},
		 {0, 1, 1, 0},
		 {0, 0, 1, 0}},
		{{0, 0, 0, 0},
		 {0, 0, 1, 1},
		 {0, 1, 1, 0},
		 {0, 0, 0, 0}},
		{{0, 0, 0, 0},
		 {0, 1, 0, 0},
		 {0, 1, 1, 0},
		 {0, 0, 1, 0} },
		{{0, 0, 0, 0},
		 {0, 0, 1, 1},
		 {0, 1, 1, 0},
		 {0, 0, 0, 0}} };
		memcpy(m_NextShape, twist[m_nextRotState], sizeof(int) * (4 * 4));
		break;
	}
	case BLOCK_TWIST_R:
	{
		int twist_r[ROTATE_END][4][4] = {
		{{0, 0, 0, 0},
		 {0, 0, 1, 0},
		 {0, 1, 1, 0},
		 {0, 1, 0, 0}},
		{{0, 0, 0, 0},
		 {0, 1, 1, 0},
		 {0, 0, 1, 1},
		 {0, 0, 0, 0}},
		{{0, 0, 0, 0},
		 {0, 0, 1, 0},
		 {0, 1, 1, 0},
		 {0, 1, 0, 0}},
		{{0, 0, 0, 0},
		 {0, 1, 1, 0},
		 {0, 0, 1, 1},
		 {0, 0, 0, 0}} };
		memcpy(m_NextShape, twist_r[m_nextRotState], sizeof(int)* (4 * 4));
		break;
	}
	case BLOCK_BENT:
	{
		int bent[ROTATE_END][4][4] = {
		{{0, 0, 0, 0},
		 {0, 1, 1, 0},
		 {0, 1, 0, 0},
		 {0, 1, 0, 0}},
		{{0, 0, 0, 0},
		 {0, 1, 1, 1},
		 {0, 0, 0, 1},
		 {0, 0, 0, 0}},
		{{0, 0, 0, 0},
		 {0, 0, 1, 0},
		 {0, 0, 1, 0},
		 {0, 1, 1, 0}},
		{{0, 0, 0, 0},
		 {0, 1, 0, 0},
		 {0, 1, 1, 1},
		 {0, 0, 0, 0}} };
		memcpy(m_NextShape, bent[m_nextRotState], sizeof(int)* (4 * 4));
		break;
	}
	case BLOCK_BENT_R:
	{
		int bent_r[ROTATE_END][4][4] = {
		{{0, 0, 0, 0},
		 {0, 1, 1, 0},
		 {0, 0, 1, 0},
		 {0, 0, 1, 0}},
		{{0, 0, 0, 0},
		 {0, 0, 0, 1},
		 {0, 1, 1, 1},
		 {0, 0, 0, 0}},
		{{0, 0, 0, 0},
		 {0, 1, 0, 0},
		 {0, 1, 0, 0},
		 {0, 1, 1, 0}},
		{{0, 0, 0, 0},
		 {0, 1, 1, 1},
		 {0, 1, 0, 0},
		 {0, 0, 0, 0}} };
		memcpy(m_NextShape, bent_r[m_nextRotState], sizeof(int)* (4 * 4));
		break;
	}
	}
}
