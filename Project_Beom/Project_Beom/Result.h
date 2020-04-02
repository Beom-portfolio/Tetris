#pragma once
#include "Scene.h"
class Result
	: public Scene
{
public:
	Result();
	virtual ~Result();

public:
	virtual bool Initialize();
	virtual int Update(const float& timeDelta);
	virtual void Render(HANDLE& frameBuffer);
	virtual void Release();
};

