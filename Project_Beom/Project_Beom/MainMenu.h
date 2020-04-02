#pragma once
#include "Scene.h"
class MainMenu
	: public Scene
{
public:
	MainMenu();
	virtual ~MainMenu();

public:
	virtual bool Initialize();
	virtual int Update(const float& timeDelta);
	virtual void Render(HANDLE& frameBuffer);
	virtual void Release();
};

