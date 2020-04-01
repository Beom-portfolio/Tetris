#pragma once
#include "GameObject.h"
class Block 
	: public GameObject
{
public:
	Block(BLOCK_STYLE style, BLOCK_ROTATE rotate);
	virtual ~Block();

public:
	void GetShape(int shape[4][4]) { memcpy(shape, m_Shape[m_rotState], sizeof(int) * (4 * 4)); }

public:
	virtual bool Initialize();
	virtual int Update(const float& timeDelta);
	virtual void Render(int* board);

public:
	void Rotate(bool clockwise = true);

private:
	int m_Shape[ROTATE_END][4][4];
	int m_shapeStyle = BLOCK_SQUARE;
	BLOCK_ROTATE m_rotState;
};

