#pragma once

#include "radi/rd.h"
#include "radi/radi_types.h"
#include "radi/radi_string.h"

namespace radi {
	namespace utils {

		static std::vector<String> SplitString(const String& string, const char delimiter)
		{
			size_t start = 0;
			size_t end = string.find_first_of(delimiter);

			std::vector<String> result;

			while (end <= String::npos)
			{
				result.emplace_back(string.substr(start, end - start));

				if (end == String::npos)
					break;

				start = end + 1;
				end = string.find_first_of(delimiter, start);
			}

			return result;
		}

	}
}