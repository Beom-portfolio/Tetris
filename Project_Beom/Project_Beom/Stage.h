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
	WCHAR m_SceneBuffer[SIZE_Y + 1][SIZE_X + 1] = { 0, };
	int m_Board[BOARD_SIZE_Y][BOARD_SIZE_X] = {0,};

	short m_intervalX = 3;
	short m_intervalY = 1;
};

