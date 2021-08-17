#pragma once

#include <chrono>
#include <array>
#include <memory>
#include <vector>
#include <thread>

typedef std::chrono::steady_clock::time_point time_point;

class Timer
{
public:
	Timer();
	~Timer();

public: // Getters
	inline const double GetElapsedTime() const { return std::chrono::duration<double>
													(std::chrono::high_resolution_clock::now() - m_Start).count(); }
	inline static const size_t GetObjectCount() { return s_ObjectCount; }

public: // non-static Public funtions
	const void Start();

public: // Public operator overloads
	const double operator()() const;
	
private: // Private non-static variables
	time_point m_Start;
	std::vector<std::thread>* m_Threads;

private: // Private static variables
	static size_t s_ObjectCount;

private: // Non-static private functions
	inline const void i_Start();
};


namespace multithread
{
	class Timer
	{
	public:
		Timer();
		~Timer();

	public: // Getters
		inline const double GetElapsedTime() const {
			return std::chrono::duration<double>
				(std::chrono::high_resolution_clock::now() - m_Start).count();
		}
		inline static const size_t GetObjectCount() { return s_ObjectCount; }
		//inline const bool GetDispatcherActive() const { return m_DispatcherActive; }

	public: // non-static Public funtions
		const void Start();

	public: // Public operator overloads
		const double operator()() const;

	private: // Private non-static variables
		time_point m_Start;
		//std::unique_ptr <std::vector<std::thread>> m_Threads;
		std::vector<std::thread>* m_Threads;
		size_t m_ThreadCount;

		bool m_DispatcherActive;

		std::thread* m_InvokeDispatcher;

	private: // Private static variables
		static size_t s_ObjectCount;

		static size_t s_ThreadCountStatic;

	private: // Non-static private functions
		inline const void i_Start();

	private: // Static private functions
		static void InvokeDispatcherFunc(const multithread::Timer* caller);
	};
}