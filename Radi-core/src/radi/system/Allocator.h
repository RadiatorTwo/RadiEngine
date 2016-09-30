#pragma once

#include "radi/common.h"
#include "radi/radi_types.h"

namespace radi {

	// TODO: Allocation Metrics
	class RD_API Allocator
	{
	public:
		static void* Allocate(size_t size);
		static void* AllocateDebug(size_t size, const char* file, uint line);

		static void Free(void* block);
		static void FreeDebug(void* block, const char* file, uint line);
	};

}