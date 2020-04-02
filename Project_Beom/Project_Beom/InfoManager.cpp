#include "pch.h"
#include "InfoManager.h"

InfoManager::InfoManager()
{
}

InfoManager::~InfoManager()
{
}

bool InfoManager::Initialize()
{
	return true;
}

void InfoManager::Release()
{
}

void InfoManager::SaveFile()
{
	if (m_bestScore > m_score)
		return;

	ofstream file;
	file.open("score.txt");

	file << m_score;

	file.close();
}

void InfoManager::LoadFile()
{
	ifstream file;
	file.open("score.txt");

	if (!file.is_open())
		return;

	file >> m_bestScore;

	file.close();
}
