#pragma once
class Maingame
{
public:
	Maingame();
	~Maingame();

public:
	bool Initialize();
	void Logic();

private:
	void Flipping();
	void Clear();

private:
	HANDLE m_FrameBuffer[2];
	int m_currentBuffer = 0;

	class SceneManager* m_SceneMgr = nullptr;
};

