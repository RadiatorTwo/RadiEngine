#pragma once

#define WINDOWS_TIMER 1

#if WINDOWS_TIMER
#include <Windows.h>
#else
#include <chrono>
#endif


namespace radi
{
	namespace utils
	{
#if WINDOWS_TIMER
		class Timer
		{
		private:
			LARGE_INTEGER m_start;
			double m_frequency;
		public:
			Timer()
			{
				LARGE_INTEGER frequency;
				QueryPerformanceFrequency(&frequency);
				m_frequency = 1.0 / frequency.QuadPart;
				QueryPerformanceCounter(&m_start);
			}

			void reset()
			{
				QueryPerformanceCounter(&m_start);
			}

			float elapsed()
			{
				LARGE_INTEGER current;
				QueryPerformanceCounter(&current);
				unsigned __int64 cycles = current.QuadPart - m_start.QuadPart;
				return (float)(cycles * m_frequency);
			}
		};
#else
		class Timer
		{
		private:
			typedef std::chrono::high_resolution_clock HighResolutionClock;
			typedef std::chrono::duration<float, std::milli> milliseconds_type;
			std::chrono::time_point<HighResolutionClock> m_start;
		public:
			Timer()
			{
				reset();
			}

			void reset()
			{
				m_start = HighResolutionClock::now();
			}

			float elapsed()
			{
				return std::chrono::duration_cast<milliseconds_type>(HighResolutionClock::now() - m_start).count() / 1000.0f;
			}
		};
#endif

	}
}