#include "radi/rd.h"
#include "memory.h"

void* operator new(size_t size)
{
	return radi::Allocator::Allocate(size);
}

void* operator new(size_t size, const char* file, uint line)
{
	return radi::Allocator::AllocateDebug(size, file, line);
}

void* operator new[](size_t size)
{
	return radi::Allocator::Allocate(size);
}

void* operator new[](size_t size, const char* file, uint line)
{
	return radi::Allocator::AllocateDebug(size, file, line);
}

void operator delete(void* block)
{
	radi::Allocator::Free(block);
}

void operator delete(void* block, const char* file, uint line)
{
	radi::Allocator::FreeDebug(block, file, line);
}

void operator delete[](void* block)
{
	radi::Allocator::Free(block);
}

void operator delete[](void* block, const char* file, uint line)
{
	radi::Allocator::FreeDebug(block, file, line);
}