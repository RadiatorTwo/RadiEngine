#include "radi/rd.h"
#include "allocator.h"

#include <malloc.h>

#include "radi/utils/Log.h"
#include "memory_manager.h"

namespace radi {

	#define SP_MEMORY_ALIGNMENT 16
	#define SP_ALLOC(size)	_aligned_malloc(size, SP_MEMORY_ALIGNMENT)
	#define SP_FREE(block)	_aligned_free(block);

	void* Allocator::Allocate(size_t size)
	{
		RADI_ASSERT(size < 1024 * 1024 * 1024);

		radi::internal::MemoryManager::Get()->m_MemoryStats.totalAllocated += size;
		radi::internal::MemoryManager::Get()->m_MemoryStats.currentUsed += size;
		radi::internal::MemoryManager::Get()->m_MemoryStats.totalAllocations++;

		size_t actualSize = size + sizeof(size_t);
		byte* result = (byte*)SP_ALLOC(actualSize);
		memset(result, 0, actualSize);
		memcpy(result, &size, sizeof(size_t));
		result += sizeof(size_t);
		return result;
	}

	void* Allocator::AllocateDebug(size_t size, const char* file, uint line)
	{
		RADI_ASSERT(size < 1024 * 1024 * 1024);

		if (size > 1024 * 1024)
			RADI_WARN("Large allocation (>1mb) at ", file, ":", line);

		return Allocate(size);
	}

	void Allocator::Free(void* block)
	{
		byte* memory = ((byte*)block) - sizeof(size_t);
		size_t size = *(size_t*)memory;
		radi::internal::MemoryManager::Get()->m_MemoryStats.totalFreed += size;
		radi::internal::MemoryManager::Get()->m_MemoryStats.currentUsed -= size;
		SP_FREE(memory);
	}

	void Allocator::FreeDebug(void* block, const char* file, uint line)
	{
		Free(block);
	}

}