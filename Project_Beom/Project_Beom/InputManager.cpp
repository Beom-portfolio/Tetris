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
		// Ư�� ����, ���� �ڵ��� ���� �Է°��� �ѹ� �� �޾ƾ� �Ѵ�.
		if (224 == m_inputKey)
		{
			m_inputKey = _getch();
		}
	}
	else
		m_inputKey = -1;
}
