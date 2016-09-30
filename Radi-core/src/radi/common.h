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

// Common defines
#define BIT(x) (1 << x)

#define METHOD_1(x) std::bind(x, this, std::placeholders::_1)
#define METHOD(x) METHOD_1(x)

#ifdef RADI_DEBUG
#define RADI_DEBUG_METHOD_V(x) x;
#else
#define RADI_DEBUG_METHOD_V(x) x {}
#endif