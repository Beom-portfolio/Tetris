#include "pch.h"
#include "Maingame.h"
#include "SceneManager.h"
#include "InputManager.h"
#include "InfoManager.h"
#include "Timer.h"

Maingame::Maingame()
{
}

Maingame::~Maingame()
{
	CloseHandle(m_FrameBuffer[0]);
	CloseHandle(m_FrameBuffer[1]);
	DESTROYMGR(SceneManager);
	DESTROYMGR(InputManager);
	DESTROYMGR(InfoManager);
	SAFE_DELETE(m_Timer);
}

bool Maingame::Initialize()
{
	// 콘솔 커서 클릭 비활성화
	HANDLE hInput;
	DWORD prev_mode;
	hInput = GetStdHandle(STD_INPUT_HANDLE);
	GetConsoleMode(hInput, &prev_mode);
	SetConsoleMode(hInput, prev_mode & ~ENABLE_QUICK_EDIT_MODE);

	SetConsoleTitle(L"T E T R I S");
	HWND console;
	console = GetConsoleWindow();
	// 화면 최대화, resize 비활성화
	SetWindowLong(console, GWL_STYLE, GetWindowLong(console, GWL_STYLE) & ~WS_MAXIMIZEBOX & ~WS_SIZEBOX);


	m_FrameBuffer[0] = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE,
		0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);

	m_FrameBuffer[1] = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE,
		0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);


	CONSOLE_CURSOR_INFO cci;
	cci.bVisible = FALSE;
	cci.dwSize = 1;
	SetConsoleCursorInfo(m_FrameBuffer[0], &cci);
	SetConsoleCursorInfo(m_FrameBuffer[1], &cci);

	m_SceneMgr = GETMGR(SceneManager);
	m_SceneMgr->ChangeScene(SCENE_MENU);

	m_Timer = new Timer;
	m_Timer->initialize();

	return true;
}

void Maingame::Logic()
{
	InputManager* inputManager = GETMGR(InputManager);

	while (true)
	{
		// update
		m_Timer->Update();

		inputManager->Update();
		m_SceneMgr->Update(m_Timer->GetTimeDelta());

		// render
		Flipping();
		Clear();
		m_SceneMgr->Render(m_FrameBuffer[m_currentBuffer]);
	}
}

void Maingame::Flipping()
{
	SetConsoleActiveScreenBuffer(m_FrameBuffer[m_currentBuffer]);
	m_currentBuffer = !m_currentBuffer;
}

void Maingame::Clear()
{
	COORD Coor = { 0, 0 };
	DWORD dw;
	FillConsoleOutputCharacter(m_FrameBuffer[m_currentBuffer], ' ', SIZE_X * SIZE_Y * 2, Coor, &dw);
}
