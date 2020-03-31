#pragma once
class Timer
{
public:
	Timer();
	~Timer();

public:
	const float& GetTimeDelta() { return m_timeDelta; }

public:
	int initialize();
	void Update();

private:
	LARGE_INTEGER m_cpuTick;
	LARGE_INTEGER m_lastTime;
	LARGE_INTEGER m_nowTime;
	float m_timeDelta = 0.f;
};

