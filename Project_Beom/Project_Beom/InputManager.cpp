#include "pch.h"
#include "InputManager.h"

InputManager::InputManager()
{
}

InputManager::~InputManager()
{
}

bool InputManager::Initialize()
{
	return true;
}

void InputManager::Release()
{
}

void InputManager::Update()
{
	if (1 == _kbhit())
	{
		m_inputKey = _getch();
		// 특수 문자, 유니 코드의 경우는 입력값을 한번 더 받아야 한다.
		if (224 == m_inputKey)
		{
			m_inputKey = _getch();
		}
	}
	else
		m_inputKey = -1;
}
