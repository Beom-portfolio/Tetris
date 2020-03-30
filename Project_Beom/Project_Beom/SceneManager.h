#pragma once
class SceneManager
	: public Singleton<SceneManager>
{
public:
	SceneManager();
	~SceneManager();

public:
	virtual bool Initialize();
	virtual void Release();

public:
	void ChangeScene(SCENE curScene);
	int Update(const float& timeDelta);
	void Render(HANDLE& frameBuffer);

private:
	class Scene* m_Scene = nullptr;
	SCENE m_currentScene = SCENE_END;
};

