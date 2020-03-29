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
	virtual void Render();

private:
	void Flipping();
	void Clear();

private:
	char test[SIZE_Y][SIZE_X] =
	{  
		"###################\n",
		"###################\n",
		"###################\n",
		"###################\n",
		"###################\n",
		"###################\n",
		"###################\n",
		"###################\n",
		"###################\n",
		"###################\n",
		"###################\n",
		"###################\n",
		"###################\n",
		"###################\n",
		"###################\n",
		"###################\n"
	};

	HANDLE m_Screen[2];
	int m_currentBuffer = 0;
};

