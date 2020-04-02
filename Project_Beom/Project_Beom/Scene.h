#pragma once
class Scene
{
public:
	Scene();
	virtual ~Scene();

public:
	virtual bool Initialize();
	virtual int Update(const float& timeDelta) = 0;
	virtual void Render(HANDLE& frameBuffer);
	virtual void Release() = 0;

protected:
	WCHAR m_SceneBuffer[SIZE_Y + 1][SIZE_X + 1] = { 0, };
};

