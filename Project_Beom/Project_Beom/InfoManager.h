#pragma once
class InfoManager
	: public Singleton<InfoManager>
{
public:
	InfoManager();
	virtual ~InfoManager();


public:
	int GetCurrentScore() { return m_score; }
	int GetBestScore() { return m_bestScore; }
	void SetCurrentScore(int score) { m_score = score; }

public:
	virtual bool Initialize();
	virtual void Release();

public:
	void SaveFile();
	void LoadFile();

private:
	int m_score = 0;
	int m_bestScore = 0;
};

