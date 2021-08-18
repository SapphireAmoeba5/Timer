#include "Timer.h"

#include <iostream>

size_t Timer::s_ObjectCount = 0;

Timer::Timer()
	:m_Start(std::chrono::high_resolution_clock::now()), m_Threads(new std::vector<std::thread>)
{
	
}

Timer::~Timer()
{
	s_ObjectCount--;
	delete m_Threads;
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



namespace multithread
{
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

	inline const void Timer::i_Start()
	{
		m_Start = std::chrono::high_resolution_clock::now();
	}
}