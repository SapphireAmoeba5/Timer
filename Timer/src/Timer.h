#pragma once

#include <chrono>
#include <array>
#include <memory>

typedef std::chrono::steady_clock::time_point time_point_timer;

class Timer
{
public:
	Timer();
	~Timer();

public: // Getters
	inline const double GetElapsedTime() const { return std::chrono::duration<double>
													(std::chrono::high_resolution_clock::now() - m_Start).count(); }
	inline static const uint32_t GetObjectCount() { return m_ObjectCount; }

public: // non-static Public funtions
	const void Start();

public: // Public operator overloads
	const double operator()() const;

private:
	time_point_timer m_Start;

private: // Private static variables
	static uint32_t m_ObjectCount;

private: // Non-static private functions
	inline const void i_Start();
};

