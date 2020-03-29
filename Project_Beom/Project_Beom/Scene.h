#pragma once
class Scene
{
public:
	Scene();
	virtual ~Scene();

public:
	virtual bool Initialize() = 0;
	virtual int Update(const float& timeDelta) = 0;
	virtual void Render() = 0;
};

