#include "Timer.h"

size_t Timer::s_ObjectCount = 0;

Timer::Timer()
	:m_Start(std::chrono::high_resolution_clock::now())
{
	
}

Timer::~Timer()
{
	s_ObjectCount--;
}

void Timer::Start()
{
	i_Start();
}

const double Timer::operator()() const
{
	return GetElapsedTime();
}

void Timer::i_Start()
{
	m_Start = std::chrono::high_resolution_clock::now();
}