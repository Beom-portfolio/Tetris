#include "pch.h"
#include "Block.h"

Block::Block(BLOCK_STYLE style)
	: m_shapeStyle(style), GameObject()
{
	memset(&m_BlockShape.shape, 0, sizeof(int) * (4 * 4));
	m_BlockShape.rotatePoint.x = -1;
	m_BlockShape.rotatePoint.y = -1;
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
		int square[4][4] = { {1, 1, 0, 0},
							 {1, 1, 0, 0},
							 {0, 0, 0, 0},
							 {0, 0, 0, 0} };
		memcpy(m_BlockShape.shape, square, sizeof(int) * (4 * 4));
		break;
	}
	case BLOCK_LINE:
	{
		int line[4][4] = { {1, 0, 0, 0},
						   {1, 0, 0, 0},
						   {1, 0, 0, 0},
						   {1, 0, 0, 0} };
		memcpy(m_BlockShape.shape, line, sizeof(int) * (4 * 4));
		m_BlockShape.rotatePoint.x = 0;
		m_BlockShape.rotatePoint.y = 0;
		break;
	}
	case BLOCK_MIDDLE:
	{
		int middle[4][4] = { {0, 1, 0, 0},
							 {1, 1, 1, 0},
							 {0, 0, 0, 0},
							 {0, 0, 0, 0} };
		memcpy(m_BlockShape.shape, middle, sizeof(int) * (4 * 4));
		m_BlockShape.rotatePoint.x = 1;
		m_BlockShape.rotatePoint.y = 1;
		break;
	}
	case BLOCK_TWIST:
	{
		int twist[4][4] = { {0, 1, 0, 0},
							 {0, 1, 1, 0},
							 {0, 0, 1, 0},
							 {0, 0, 0, 0} };
		memcpy(m_BlockShape.shape, twist, sizeof(int) * (4 * 4));
		m_BlockShape.rotatePoint.x = 1;
		m_BlockShape.rotatePoint.y = 1;
		break;
	}
	case BLOCK_TWIST_R:
	{
		int twist_r[4][4] = { {0, 0, 1, 0},
							  {0, 1, 1, 0},
							  {0, 1, 0, 0},
							  {0, 0, 0, 0} };
		memcpy(m_BlockShape.shape, twist_r, sizeof(int) * (4 * 4));
		m_BlockShape.rotatePoint.x = 1;
		m_BlockShape.rotatePoint.y = 1;
		break;
	}
	case BLOCK_BENT:
	{
		int bent[4][4] = { {0, 1, 1, 0},
							 {0, 1, 0, 0},
							 {0, 1, 0, 0},
							 {0, 0, 0, 0} };
		memcpy(m_BlockShape.shape, bent, sizeof(int) * (4 * 4));
		m_BlockShape.rotatePoint.x = 1;
		m_BlockShape.rotatePoint.y = 1;
		break;
	}
	case BLOCK_BENT_R:
	{
		int bent_r[4][4] = { {1, 1, 0, 0},
							 {0, 1, 0, 0},
							 {0, 1, 0, 0},
							 {0, 0, 0, 0} };
		memcpy(m_BlockShape.shape, bent_r, sizeof(int) * (4 * 4));
		m_BlockShape.rotatePoint.x = 1;
		m_BlockShape.rotatePoint.y = 1;
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
