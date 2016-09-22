#pragma once

#include <stdio.h>

#define RADI_ASSERT(x, m) \
	do { \
	if (!(x)) \
		{ \
		char* file = __FILE__; \
		unsigned int last = 0; \
		char* c; \
		for (c = file; *c != '\0'; c++) \
				{ \
			if (*c == '\\' || *c == '/') \
				last = c - file; \
				} \
		printf("\n"); \
		printf("*************************\n"); \
		printf("    ASSERTION FAILED!    \n"); \
		printf("*************************\n"); \
		printf("%s\n", #x); \
		char* message = m; \
		if (message[0] != '\0') \
			printf("%s\n", m); \
		printf("-> "); \
		for (int i = last + 1; i < c - file; i++) \
			printf("%c", file[i]); \
		printf(":%d\n", __LINE__); \
		*(int*)NULL = 8; \
	} \
	} while(0)

#define RADI_LOG_LEVEL_FATAL 0
#define RADI_LOG_LEVEL_ERROR 1
#define RADI_LOG_LEVEL_WARN  2
#define RADI_LOG_LEVEL_INFO  3

#ifndef RADI_LOG_LEVEL
#define RADI_LOG_LEVEL RADI_LOG_LEVEL_INFO
#endif

#if RADI_LOG_LEVEL >= RADI_LOG_LEVEL_FATAL
#define RADI_FATAL(x, ...) do { printf("[RADI][FATAL]: "); printf(x, __VA_ARGS__); printf("\n"); RADI_ASSERT(false, ""); } while(0)
#endif

#if RADI_LOG_LEVEL >= RADI_LOG_LEVEL_ERROR
#define RADI_ERROR(x, ...) do { printf("[RADI][ERROR]: "); printf(x, __VA_ARGS__); printf("\n"); } while(0)
#endif

#if RADI_LOG_LEVEL >= RADI_LOG_LEVEL_WARN
#define RADI_WARN(x, ...) do { printf("[RADI][WARN]: "); printf(x, __VA_ARGS__); printf("\n"); } while(0)
#endif

#if RADI_LOG_LEVEL >= RADI_LOG_LEVEL_INFO
#define RADI_INFO(x, ...) do { printf("[RADI][INFO]: "); printf(x, __VA_ARGS__); printf("\n"); } while(0)
#endif