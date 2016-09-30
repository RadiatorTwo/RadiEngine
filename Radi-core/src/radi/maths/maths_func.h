#pragma once

#include "radi/Common.h"

#include <math.h>

#define RD_PI 3.14159265358f

namespace radi {
	namespace maths {

		RD_API inline float toRadians(float degrees)
		{
			return (float)(degrees * (RD_PI / 180.0f));
		}

		RD_API inline float toDegrees(float radians)
		{
			return (float)(radians * (180.0f / RD_PI));
		}

		RD_API inline int32 sign(float value)
		{
			return (value > 0) - (value < 0);
		}

		RD_API inline float sin(float angle)
		{
			return ::sin(angle);
		}

		RD_API inline float cos(float angle)
		{
			return ::cos(angle);
		}

		RD_API inline float tan(float angle)
		{
			return ::tan(angle);
		}

		RD_API inline float sqrt(float value)
		{
			return ::sqrt(value);
		}

		RD_API inline float rsqrt(float value)
		{
			return 1.0f / ::sqrt(value);
		}

		RD_API inline float asin(float value)
		{
			return ::asin(value);
		}

		RD_API inline float acos(float value)
		{
			return ::acos(value);
		}

		RD_API inline float atan(float value)
		{
			return ::atan(value);
		}

		RD_API inline float atan2(float y, float x)
		{
			return ::atan2(y, x);
		}

		RD_API inline float _min(float value, float minimum)
		{
			return (value < minimum) ? minimum : value;
		}

		RD_API inline float _max(float value, float maximum)
		{
			return (value > maximum) ? maximum : value;
		}

		RD_API inline float clamp(float value, float minimum, float maximum)
		{
			return (value > minimum) ? (value < maximum) ? value : maximum : minimum;
		}

	}
}