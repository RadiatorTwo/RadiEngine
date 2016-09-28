#pragma once
#pragma warning (disable:4251)

#ifdef RADI_PLATFORM_WINDOWS
#ifdef RADI_CORE_DLL
#define RD_API __declspec(dllexport)
#else
#define RD_API __declspec(dllimport)
#endif
#else
#define RD_API
#endif