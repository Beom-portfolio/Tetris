#include "pch.h"
#include "Block.h"

Block::Block(BLOCK_STYLE style, BLOCK_ROTATE rotate)
	: m_shapeStyle(style), m_rotState(rotate),
	GameObject()
{
	memset(m_Shape, 0, sizeof(int) * (4 * 4 * 4));
}

Block::~Block()
{
}

bool Block::Initialize()
{
	switch(m_shapeStyle)
	{
	case BLOCK_SQUARE:
	{
		int square[ROTATE_END][4][4] = {
		{{0, 1, 1, 0},
		 {0, 1, 1, 0},
		 {0, 0, 0, 0},
		 {0, 0, 0, 0}},
		{{0, 1, 1, 0},
		 {0, 1, 1, 0},
		 {0, 0, 0, 0},
		 {0, 0, 0, 0}},
		{{0, 1, 1, 0},
		 {0, 1, 1, 0},
		 {0, 0, 0, 0},
		 {0, 0, 0, 0}},
		{{0, 1, 1, 0},
		 {0, 1, 1, 0},
		 {0, 0, 0, 0},
		 {0, 0, 0, 0}} };
		memcpy(m_Shape, square, sizeof(int) * (4 * 4 * 4));
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
		 {0, 0, 0, 0},
		 {1, 1, 1, 1}},
		{{0, 1, 0, 0},
		 {0, 1, 0, 0},
		 {0, 1, 0, 0},
		 {0, 1, 0, 0}},
		{{0, 0, 0, 0},
		 {0, 0, 0, 0},
		 {0, 0, 0, 0},
		 {1, 1, 1, 1}} };
		memcpy(m_Shape, line, sizeof(int) * (4 * 4 * 4));
		break;
	}
	case BLOCK_MIDDLE:
	{
		int middle[ROTATE_END][4][4] = {
		{{0, 1, 0, 0},
		 {1, 1, 1, 0},
		 {0, 0, 0, 0},
		 {0, 0, 0, 0}},
		{{0, 1, 0, 0},
		 {0, 1, 1, 0},
		 {0, 1, 0, 0},
		 {0, 0, 0, 0}},
		{{0, 0, 0, 0},
		 {1, 1, 1, 0},
		 {0, 1, 0, 0},
		 {0, 0, 0, 0}},
		{{0, 1, 0, 0},
		 {1, 1, 0, 0},
		 {0, 1, 0, 0},
		 {0, 0, 0, 0}} };
		memcpy(m_Shape, middle, sizeof(int) * (4 * 4 * 4));
		break;
	}
	case BLOCK_TWIST:
	{
		int twist[ROTATE_END][4][4] = {
		{{0, 1, 0, 0},
		 {0, 1, 1, 0},
		 {0, 0, 1, 0},
		 {0, 0, 0, 0}},
		{{0, 1, 1, 0},
		 {1, 1, 0, 0},
		 {0, 0, 0, 0},
		 {0, 0, 0, 0}},
		{{0, 1, 0, 0},
		 {0, 1, 1, 0},
		 {0, 0, 1, 0},
		 {0, 0, 0, 0}},
		{{0, 1, 1, 0},
		 {1, 1, 0, 0},
		 {0, 0, 0, 0},
		 {0, 0, 0, 0}} };
		memcpy(m_Shape, twist, sizeof(int) * (4 * 4 * 4));
		break;
	}
	case BLOCK_TWIST_R:
	{
		int twist_r[ROTATE_END][4][4] = {
		{{0, 0, 1, 0},
		 {0, 1, 1, 0},
		 {0, 1, 0, 0},
		 {0, 0, 0, 0}},
		{{1, 1, 0, 0},
		 {0, 1, 1, 0},
		 {0, 0, 0, 0},
		 {0, 0, 0, 0}},
		{{0, 0, 1, 0},
		 {0, 1, 1, 0},
		 {0, 1, 0, 0},
		 {0, 0, 0, 0}},
		{{1, 1, 0, 0},
		 {0, 1, 1, 0},
		 {0, 0, 0, 0},
		 {0, 0, 0, 0}} };
		memcpy(m_Shape, twist_r, sizeof(int)* (4 * 4 * 4));
		break;
	}
	case BLOCK_BENT:
	{
		int bent[ROTATE_END][4][4] = {
		{{0, 1, 1, 0},
		 {0, 1, 0, 0},
		 {0, 1, 0, 0},
		 {0, 0, 0, 0}},
		{{0, 0, 0, 0},
		 {1, 1, 1, 0},
		 {0, 0, 1, 0},
		 {0, 0, 0, 0}},
		{{0, 1, 0, 0},
		 {0, 1, 0, 0},
		 {1, 1, 0, 0},
		 {0, 0, 0, 0}},
		{{1, 0, 0, 0},
		 {1, 1, 1, 0},
		 {0, 0, 0, 0},
		 {0, 0, 0, 0}} };
		memcpy(m_Shape, bent, sizeof(int)* (4 * 4 * 4));
		break;
	}
	case BLOCK_BENT_R:
	{
		int bent_r[ROTATE_END][4][4] = { 
		{{1, 1, 0, 0},
		 {0, 1, 0, 0},
		 {0, 1, 0, 0},
		 {0, 0, 0, 0}},
		{{0, 0, 1, 0},
		 {1, 1, 1, 0},
		 {0, 0, 0, 0},
		 {0, 0, 0, 0}},
		{{0, 1, 0, 0},
		 {0, 1, 0, 0},
		 {0, 1, 1, 0},
		 {0, 0, 0, 0}},
		{{0, 0, 0, 0},
		 {1, 1, 1, 0},
		 {1, 0, 0, 0},
		 {0, 0, 0, 0}} };
		memcpy(m_Shape, bent_r, sizeof(int)* (4 * 4 * 4));
		break;
	}
	}

	return true;
}

int Block::Update(const float& timeDelta)
{
	m_posY += m_speed * timeDelta;

	return 0;
}

void Block::Render(int* board)
{
}

void Block::Rotate(bool clockwise)
{
	if (clockwise)
	{
		m_rotState = BLOCK_ROTATE((m_rotState + 1) % ROTATE_END);
	}
	else
	{
		if (0 > m_rotState - 1)
			m_rotState = BLOCK_ROTATE(ROTATE_END - 1);
		else
			m_rotState = BLOCK_ROTATE(m_rotState - 1);
	}
}
