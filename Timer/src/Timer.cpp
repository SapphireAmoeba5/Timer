#include "Timer.h"

uint32_t Timer::m_ObjectCount = 0;

Timer::Timer()
	:m_Start(std::chrono::high_resolution_clock::now())
{
	
}

Timer::~Timer()
{
	m_ObjectCount--;
}

const void Timer::Start()
{
	i_Start();
}

const double Timer::operator()() const
{
	return GetElapsedTime();
}

inline const void Timer::i_Start()
{
	m_Start = std::chrono::high_resolution_clock::now();
}
