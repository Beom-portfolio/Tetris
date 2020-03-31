#include "pch.h"
#include "GameObject.h"


GameObject::GameObject()
	: m_posX(0), m_posY(0), m_speed(0)
{
}


GameObject::~GameObject()
{
}

void GameObject::SetPos(int x, int y)
{
	m_posX = (float)x;
	m_posY = (float)y;
}

void GameObject::SetPosX(int x)
{
	m_posX = (float)x;
}

void GameObject::SetPosY(int y)
{
	m_posY = (float)y;
}

void GameObject::SetSpeed(float speed)
{
	m_speed = speed;
}

void GameObject::GetPos(int& x, int& y)
{
	x = (int)m_posX;
	y = (int)m_posY;
}

void GameObject::GetSpeed(float& speed)
{
	speed = m_speed;
}
