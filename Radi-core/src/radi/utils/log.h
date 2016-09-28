#pragma once

#include <stdio.h>
#include <algorithm>
#include <string>
#include <vector>
#include <list>
#include <map>

#include <radi_types.h>
#include <radi/maths/vec2.h>

#define RADI_LOG_LEVEL_FATAL 0
#define RADI_LOG_LEVEL_ERROR 1
#define RADI_LOG_LEVEL_WARN  2
#define RADI_LOG_LEVEL_INFO  3

namespace std
{
	template <typename T>
	string to_string(const T& t)
	{
		return string("[Unsupported type (") + typeid(T).name() + string(")!] (to_string)");
	}
}

//
// Work in progress!
//
// -------------------------------
//			TODO: 
// -------------------------------
//	- Better container type logging
//	- Better platform support
//	- Logging to other destinations (eg. files)
//	- Include (almost) ALL Radi class types
//	- More...
namespace radi {
	namespace internal {

		static char to_string_buffer[1024 * 10];

		void PlatformLogMessage(uint level, const char* message);

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

		template <>
		static const char* to_string<char>(char const& t)
		{
			return &t;
		}

		template <>
		static const char* to_string<char*>(char* const& t)
		{
			return t;
		}

		template <>
		static const char* to_string<unsigned char const*>(unsigned char const* const& t)
		{
			return (const char*)t;
		}


		template <>
		static const char* to_string<char const*>(char const* const& t)
		{
			return t;
		}

		template <>
		static const char* to_string<String>(const String& t)
		{
			return t.c_str();
		}

		template <>
		static const char* to_string<maths::vec2>(const maths::vec2& t)
		{
			// TODO: sprintf
			String string = String("vec2: (") + std::to_string(t.x) + ", " + std::to_string(t.y) + ")";
			char* result = new char[string.length()];
			strcpy(result, &string[0]);
			return result;
		}

		template <typename T>
		static String format_iterators(T& begin, T& end)
		{
			String result;
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
		static const char* to_string_internal<const char*>(const char* const& v, const std::false_type& ignored)
		{
			return v;
		}

		template <typename First>
		static void print_log_internal(char* buffer, int& position, First&& first)
		{
			const char* formatted = radi::internal::to_string<First>(first);
			int length = strlen(formatted);
			memcpy(&buffer[position], formatted, length);
			position += length;
		}

		template <typename First, typename... Args>
		static void print_log_internal(char* buffer, int& position, First&& first, Args&&... args)
		{
			const char* formatted = radi::internal::to_string<First>(first);
			int length = strlen(formatted);
			memcpy(&buffer[position], formatted, length);
			position += length;
			if (sizeof...(Args))
				print_log_internal(buffer, position, std::forward<Args>(args)...);
		}

		template <typename... Args>
		static void log_message(int level, bool newline, Args... args)
		{
			char buffer[1024 * 10];
			int position = 0;
			print_log_internal(buffer, position, std::forward<Args>(args)...);

			if (newline)
				buffer[position++] = '\n';

			buffer[position] = 0;

			PlatformLogMessage(level, buffer);
		}
	}
}

#ifndef RADI_LOG_LEVEL
#define RADI_LOG_LEVEL RADI_LOG_LEVEL_INFO
#endif

#if RADI_LOG_LEVEL >= RADI_LOG_LEVEL_FATAL
#define RADI_FATAL(...) radi::internal::log_message(RADI_LOG_LEVEL_FATAL, true, "RADI:    ", __VA_ARGS__)
#define _RADI_FATAL(...) radi::internal::log_message(RADI_LOG_LEVEL_FATAL, false, __VA_ARGS__)
#else
#define RADI_FATAL(...)
#endif

#if RADI_LOG_LEVEL >= RADI_LOG_LEVEL_ERROR
#define RADI_ERROR(...) radi::internal::log_message(RADI_LOG_LEVEL_ERROR, true, "RADI:    ", __VA_ARGS__)
#define _RADI_ERROR(...) radi::internal::log_message(RADI_LOG_LEVEL_ERROR, false, __VA_ARGS__)
#else
#define RADI_ERROR(...)
#endif

#if RADI_LOG_LEVEL >= RADI_LOG_LEVEL_WARN
#define RADI_WARN(...) radi::internal::log_message(RADI_LOG_LEVEL_WARN, true, "RADI:    ", __VA_ARGS__)
#define _RADI_WARN(...) radi::internal::log_message(RADI_LOG_LEVEL_WARN, false, __VA_ARGS__)
#else
#define RADI_WARN(...)
#endif

#if RADI_LOG_LEVEL >= RADI_LOG_LEVEL_INFO
#define RADI_INFO(...) radi::internal::log_message(RADI_LOG_LEVEL_INFO, true, "RADI:    ", __VA_ARGS__)
#define _RADI_INFO(...) radi::internal::log_message(RADI_LOG_LEVEL_INFO, false, __VA_ARGS__)
#else
#define RADI_INFO(...)
#endif

#ifdef RADI_DEBUG
#define RADI_ASSERT(x, ...) \
 		if (!(x)) {\
 			RADI_FATAL("*************************"); \
 			RADI_FATAL("    ASSERTION FAILED!    "); \
 			RADI_FATAL("*************************"); \
 			RADI_FATAL(__FILE__, ": ", __LINE__); \
 			RADI_FATAL("Condition: ", #x); \
 			RADI_FATAL(__VA_ARGS__); \
 			__debugbreak(); \
 		}
#else
#define RADI_ASSERT(x, ...)
#endif

#include <GL/glew.h>

static bool log_gl_call(const char* function, const char* file, int line)
{
	GLenum error = glGetError();
	if (error != GL_NO_ERROR)
	{
		RADI_ERROR("[OpenGL Error] (", error, "): ", function, " ", file, ":", line);
		return false;
	}
	return true;
}

#ifdef RADI_DEBUG
#define GLCall(x) glGetError();\
		x; \
		if (!log_gl_call(#x, __FILE__, __LINE__)) __debugbreak();
#else
#define GLCall(x) x
#endif