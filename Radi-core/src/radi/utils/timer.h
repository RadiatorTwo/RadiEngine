#pragma once

#include "radi/common.h"

namespace radi {

	class RD_API Timer
	{
	public:
		// Creates and starts timer
		Timer();
		// Resets and restarts timer
		void Reset();
		// Returns time in milliseconds
		float Elapsed();
	};

}