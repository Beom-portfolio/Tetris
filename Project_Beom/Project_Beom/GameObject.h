#pragma once
class GameObject
{
public:
	GameObject();
	virtual ~GameObject();

public:
	void SetPos(int x, int y);
	void SetPosX(int x);
	void SetPosY(int y);
	void SetSpeed(float speed);
	void GetPos(int& x, int& y);
	void GetSpeed(float& speed);



public:
	virtual bool Initialize() = 0;
	virtual int Update(const float& timeDelta) = 0;
	virtual void Render(int* board) = 0;

protected:
	float m_posX, m_posY;
	float m_speed;
};

