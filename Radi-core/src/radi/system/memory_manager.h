#pragma once

#include "radi/radi_string.h"

namespace radi {
	namespace internal {

		struct RD_API SystemMemoryInfo
		{
			int64 availablePhysicalMemory;
			int64 totalPhysicalMemory;

			int64 availableVirtualMemory;
			int64 totalVirtualMemory;

			void Log();
		};

		struct RD_API MemoryStats
		{
			int64 totalAllocated;
			int64 totalFreed;
			int64 currentUsed;
			int64 totalAllocations;

			MemoryStats()
				: totalAllocated(0), totalFreed(0), currentUsed(0), totalAllocations(0)
			{
			}
		};

		class RD_API MemoryManager
		{
		public:
			static MemoryManager* s_Instance;
		public:
			MemoryStats m_MemoryStats;
		public:
			MemoryManager();

			static void Init();
			static void Shutdown();

			static MemoryManager* Get();
			inline MemoryStats GetMemoryStats() const { return m_MemoryStats; }
		public:
			SystemMemoryInfo GetSystemInfo();
		public:
			static String BytesToString(int64 bytes);
		};

	}
}
