#pragma once
#include "Scene.h"

class Stage 
	: public Scene
{
public:
	Stage();
	virtual ~Stage();

public:
	virtual bool Initialize();
	virtual int Update(const float& timeDelta);
	virtual void Render(HANDLE& frameBuffer);
	virtual void Release();

private:
	int UpdateObject(const float& timeDelta);
	int UpdateBoard();
	int UpdateInput();
	int UpdateCollision();
	int UpdateLineClear();
	int UpdateStatus();

	bool CheckCollision(int x, int y);
	bool CheckGameOver();
	void RenewBoard();
	void NextBlock();
	void MakeBlock();
private:
	int m_Board[BOARD_SIZE_Y][BOARD_SIZE_X] = {0,};
	class GameObject* m_Block = nullptr;
	bool m_eventCheck = false;

	int m_level = 1;
	int m_goal = 5;
	int m_score = 0;
	int m_bestScore = 0;

	BLOCK_ROTATE m_nextRotState = ROTATE_END;
	BLOCK_STYLE m_nextBlockStyle = BLOCK_END;
	int m_NextShape[4][4];
	POINT m_willShapePos[4];

	bool m_waitCheck = false;
	float m_timeForWait = 0.f;
	WAIT_EVENT m_event = EVENT_END;
};

