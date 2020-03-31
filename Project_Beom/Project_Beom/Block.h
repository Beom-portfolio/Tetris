#pragma once
#include "GameObject.h"
class Block 
	: public GameObject
{
public:
	Block(BLOCK_STYLE style);
	virtual ~Block();

public:
	SHAPE& GetShape() { return m_BlockShape; }

public:
	virtual bool Initialize();
	virtual int Update(const float& timeDelta);
	virtual void Render(int* board);

public:
	void Rotate();

private:
	SHAPE m_BlockShape;
	int m_shapeStyle = BLOCK_SQUARE;
};

