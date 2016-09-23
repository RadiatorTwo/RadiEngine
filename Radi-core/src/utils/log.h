#pragma once

#include <stdio.h>
#include <algorithm>
#include <string>
#include <vector>
#include <list>
#include <map>

#include <Windows.h>

#define RADI_LOG_LEVEL_FATAL 0
#define RADI_LOG_LEVEL_ERROR 1
#define RADI_LOG_LEVEL_WARN  2
#define RADI_LOG_LEVEL_INFO  3

namespace std
{
	template <typename T>
	string to_string(const T& t)
	{
		return "[Unsupported type!] (to_string)";
	}
}

//
// Work in progress!
//
// -------------------------------
//			TODO: 
// -------------------------------
//	- Besseres container type logging
//	- Besserer platform support
//	- In Datei loggen
//	- Include (fast) alle Radi Klassentypen
//	- Und Mehr...

namespace radi
{
	namespace internal
	{
		static char to_string_buffer[1024 * 10];
		template <class T>
		struct has_iterator
		{
			template<class U> static char(&test(typename U::iterator const*))[1];
			template<class U> static char(&test(...))[2];
			static const bool value = (sizeof(test<T>(0)) == 1);
		};

		template <typename T>
		static const char* to_string(const T& t)
		{
			return to_string_internal<T>(t, std::integral_constant<bool, has_iterator<T>::value>());
		}

		template <typename T>
		static std::string format_iterators(T& begin, T& end)
		{
			std::string result;
			bool first = true;
			while (begin != end)
			{
				if (!first)
					result += ", ";
				result += to_string(*begin);
				first = false;
				begin++;
			}
			return result;
		}

		//template <typename T> const char* container_to_string_internal(const std::vector<T>& v)
			//{
			//	static char buffer[1024];
			//	sprintf(buffer, "Vector of %s - size: %d, contents: %s", typeid(T).name(), v.size(), format_iterators(v.begin(), v.end()).c_str());
			//	return buffer;
			//}
			//
			//template <typename T> const char* container_to_string_internal(const std::list<T>& v)
			//{
			//	static char buffer[1024];
			//	sprintf(buffer, "List of %s - size: %d, contents: %s", typeid(T).name(), v.size(), format_iterators(v.begin(), v.end()).c_str());
			//	return buffer;
			//}

		template <typename T>
		static const char* to_string_internal(const T& v, const std::true_type& ignored)
		{
			sprintf(to_string_buffer, "Container of size: %d, contents: %s", v.size(), format_iterators(v.begin(), v.end()).c_str());
			return to_string_buffer;
		}

		template <typename T>
		static const char* to_string_internal(const T& t, const std::false_type& ignored)
		{
			auto x = std::to_string(t);
			return strcpy(to_string_buffer, x.c_str());
		}

		template<typename X, typename Y>
		static const char* to_string(const std::pair<typename X, typename Y>& v)
		{
			sprintf(to_string_buffer, "(Key: %s, Value: %s)", to_string(v.first), to_string(v.second));
			return to_string_buffer;
		}

		template<>
		static  const char* to_string_internal<const char*>(const char* const& v, const std::false_type& ignored)
		{
			return v;
		}

		template <typename First>
		static void print_log_internal(char* buffer, int& position, First&& first)
		{
			const char* formatted = to_string<First>(first);
			int length = strlen(formatted);
			memcpy(&buffer[position], formatted, length);
			position += length;
		}

		template <typename First, typename... Args>
		static void print_log_internal(char* buffer, int& position, First&& first, Args&&... args)
		{
			const char* formatted = to_string<First>(first);
			int length = strlen(formatted);
			memcpy(&buffer[position], formatted, length);
			position += length;
			if (sizeof...(Args))
			{
				print_log_internal(buffer, position, std::forward<Args>(args)...);
			}
		}

		template <typename... Args>
		static void log_message(int level, Args... args)
		{
			char buffer[1024 * 10];
			int position = 0;
			print_log_internal(buffer, position, std::forward<Args>(args)...);

			buffer[position++] = '\n';
			buffer[position] = 0;

			HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
			switch (level)
			{
			case RADI_LOG_LEVEL_FATAL:
				SetConsoleTextAttribute(hConsole, BACKGROUND_RED | BACKGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
				break;
			case RADI_LOG_LEVEL_ERROR:
				SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_INTENSITY);
				break;
			case RADI_LOG_LEVEL_WARN:
				SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
				break;
			case RADI_LOG_LEVEL_INFO:
				SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
				break;
			}
			std::cout << buffer;
			SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN);
		}
	}
}

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

#ifndef RADI_LOG_LEVEL
#define RADI_LOG_LEVEL RADI_LOG_LEVEL_INFO
#endif

#if RADI_LOG_LEVEL >= RADI_LOG_LEVEL_FATAL
#define RADI_FATAL(...) radi::internal::log_message(RADI_LOG_LEVEL_FATAL, "RADI:    ", __VA_ARGS__)
#else
#define RADI_FATAL(...)
#endif

#if RADI_LOG_LEVEL >= RADI_LOG_LEVEL_ERROR
#define RADI_ERROR(...) radi::internal::log_message(RADI_LOG_LEVEL_ERROR, "RADI:    ", __VA_ARGS__)
#else
#define RADI_ERROR(...)
#endif

#if RADI_LOG_LEVEL >= RADI_LOG_LEVEL_WARN
#define RADI_WARN(...) radi::internal::log_message(RADI_LOG_LEVEL_WARN, "RADI:    ", __VA_ARGS__)
#else
#define RADI_WARN(...)
#endif

#if RADI_LOG_LEVEL >= RADI_LOG_LEVEL_INFO
#define RADI_INFO(...) radi::internal::log_message(RADI_LOG_LEVEL_INFO, "RADI:    ", __VA_ARGS__)
#else
#define RADI_INFO(...)
#endif 