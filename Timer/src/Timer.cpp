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



















//Multithreaded version of Timer (has extra functionality including 'Invoke')

//TODO Finish this class. DONT USE RIGHT NOW!)
namespace multithread
{
	size_t Timer::s_ObjectCount = 0;
	size_t Timer::s_ThreadCountStatic = 0;

	Timer::Timer()
		:m_Start(std::chrono::high_resolution_clock::now()), m_Threads(new std::vector<std::thread>())/*m_Threads(std::make_unique<std::vector<std::thread>>())*/, m_ThreadCount(0),
		m_DispatcherActive(true)
	{
		m_InvokeDispatcher = new std::thread(&InvokeDispatcherFunc, this);
	}

	Timer::~Timer()
	{
		s_ObjectCount--;

		m_DispatcherActive = false;
		m_InvokeDispatcher->join();
		delete m_InvokeDispatcher;

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
	
	void Timer::InvokeDispatcherFunc(const multithread::Timer* caller)
	{
		using namespace std::literals::chrono_literals;

		while (caller->m_DispatcherActive)
		{
			std::cout << "Dispatcher Active!" << std::endl;
			std::this_thread::sleep_for(1s);
		}
		std::cout << "Dispatcher Destroyed!\n";
	}
}