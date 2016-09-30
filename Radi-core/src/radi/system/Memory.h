#pragma once

#include "allocator.h"

#define rdnew		new(__FILE__, __LINE__)
#define rddel		delete

void* operator new(size_t size);
RD_API void* operator new(size_t size, const char* file, uint line);
void* operator new[](size_t size);
RD_API void* operator new[](size_t size, const char* file, uint line);
void operator delete(void* block);
RD_API void operator delete(void* block, const char* file, uint line);
void operator delete[](void* block);
RD_API void operator delete[](void* block, const char* file, uint line);