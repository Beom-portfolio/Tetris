#pragma once
class InputManager
	: public Singleton<InputManager>
{
public:
	InputManager();
	virtual ~InputManager();

public:
	const int& GetInputKey() { return m_inputKey; }

public:
	virtual bool Initialize();
	virtual void Release();

public:
	void Update();

private:
	int m_inputKey = -1;
};

