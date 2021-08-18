#pragma once

#include <chrono>
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

	public: // non-static Public funtions
		void Start();
		template<typename F, typename... A>
		void Invoke(uint32_t ms, F&& func, A... args);

	public: // Public operator overloads
		const double operator()() const;

	private: // Private non-static variables
		time_point m_Start;

	private: // Private static variables
		static size_t s_ObjectCount;

	private: // Non-static private functions
		inline const void i_Start();
	private: // Static private functions
		template<typename F, typename ...A>
		static void FuncDispatcher(uint32_t ms, F&& func, A&&... args);
	};

	template<typename F, typename ...A>
	void Timer::Invoke(uint32_t ms, F&& func, A... args)
	{
		std::thread dispatch([ms, func, &args...]() {FuncDispatcher(ms, func, std::forward<A>(args)...); });
		dispatch.detach();
	}

	template<typename F, typename ...A>
	void Timer::FuncDispatcher(uint32_t ms, F&& func, A && ...args)
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(ms));
		func(std::forward<A>(args)...);
	}
}