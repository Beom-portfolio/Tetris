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

	bool CheckCollision(int x, int y);
	void RenewBoard();

private:
	WCHAR m_SceneBuffer[SIZE_Y + 1][SIZE_X + 1] = { 0, };
	int m_Board[BOARD_SIZE_Y][BOARD_SIZE_X] = {0,};

	short m_intervalX = 3;
	short m_intervalY = 2;

	class GameObject* m_Block = nullptr;

	bool m_eventCheck = false;
};

