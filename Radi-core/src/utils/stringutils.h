#pragma once

#include <radi_types.h>
#include <string>
#include <sstream>
#include <vector>

namespace radi {

	static std::vector<String> split_string(const String &s, char delimeter) {
		std::vector<String> elems;
		std::stringstream ss(s);
		String item;
		while (std::getline(ss, item, delimeter)) {
			elems.push_back(item);
		}
		return elems;
	}

}