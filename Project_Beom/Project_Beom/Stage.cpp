#include "pch.h"
#include "Stage.h"


Stage::Stage()
{
}


Stage::~Stage()
{
	CloseHandle(m_Screen[0]);
	CloseHandle(m_Screen[1]);
}

bool Stage::Initialize()
{
	COORD size = { SIZE_X, SIZE_Y };
	SMALL_RECT rect = SMALL_RECT{ 0, SIZE_X - 1, 0, SIZE_Y - 1 };

	m_Screen[0] = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE,
		0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
	SetConsoleScreenBufferSize(m_Screen[0], size);
	SetConsoleWindowInfo(m_Screen[0], TRUE, &rect);

	m_Screen[1] = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE,
		0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
	SetConsoleScreenBufferSize(m_Screen[1], size);
	SetConsoleWindowInfo(m_Screen[1], TRUE, &rect);

	CONSOLE_CURSOR_INFO cci;
	cci.bVisible = FALSE;
	cci.dwSize = 1;
	SetConsoleCursorInfo(m_Screen[0], &cci);
	SetConsoleCursorInfo(m_Screen[1], &cci);

	return true;
}

int Stage::Update(const float & timeDelta)
{
	return 0;
}

void Stage::Render()
{
	Flipping();

	Clear();
	DWORD dw;
	COORD CursorPosition = { 10, 10 };
	SetConsoleCursorPosition(m_Screen[m_currentBuffer], CursorPosition);
	WriteFile(m_Screen[m_currentBuffer], "æ»≥Á«œººø‰", sizeof("æ»≥Á«œººø‰"), &dw, NULL);
}

void Stage::Flipping()
{
	SetConsoleActiveScreenBuffer(m_Screen[m_currentBuffer]);
	m_currentBuffer = !m_currentBuffer;
}

void Stage::Clear()
{
	COORD Coor = { 0, 0 };
	DWORD dw;
	FillConsoleOutputCharacter(m_Screen[m_currentBuffer], ' ', sizeof("æ»≥Á«œººø‰"), Coor, &dw);
}
