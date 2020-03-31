#include "pch.h"
#include "Timer.h"

Timer::Timer()
{
}

Timer::~Timer()
{
}

int Timer::initialize()
{
	QueryPerformanceFrequency(&m_cpuTick);
	QueryPerformanceCounter(&m_lastTime);
	QueryPerformanceCounter(&m_nowTime);

	return 0;
}

void Timer::Update()
{
	QueryPerformanceCounter(&m_nowTime);
	m_timeDelta = float(m_nowTime.QuadPart - m_lastTime.QuadPart) / (float)m_cpuTick.QuadPart;
	m_lastTime = m_nowTime;
}
