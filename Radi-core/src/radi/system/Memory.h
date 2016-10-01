#pragma once

#include "Allocator.h"

#define rdnew		new(__FILE__, __LINE__)
#define rddel		delete

#pragma warning(disable : 4595)

inline void* operator new(size_t size)
{
	return radi::Allocator::Allocate(size);
}

inline void* operator new(size_t size, const char* file, uint line)
{
	return radi::Allocator::AllocateDebug(size, file, line);
}

inline void* operator new[](size_t size)
{
	return radi::Allocator::Allocate(size);
}

inline void* operator new[](size_t size, const char* file, uint line)
{
	return radi::Allocator::AllocateDebug(size, file, line);
}

inline void operator delete(void* block)
{
	radi::Allocator::Free(block);
}

inline void operator delete(void* block, const char* file, uint line)
{
	radi::Allocator::FreeDebug(block, file, line);
}

inline void operator delete[](void* block)
{
	radi::Allocator::Free(block);
}

inline void operator delete[](void* block, const char* file, uint line)
{
	radi::Allocator::FreeDebug(block, file, line);
}

#pragma warning(default : 4595)