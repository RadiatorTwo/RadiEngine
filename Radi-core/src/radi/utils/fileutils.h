#pragma once
#include <string>
#include <fstream>

#include <radi/utils/Log.h>

namespace radi
{
	namespace utils
	{
		static String ReadFile(const String& filepath)
		{
			// ReSharper disable once CppDeprecatedEntity
			FILE* file = fopen(filepath.c_str(), "rt");
			if (file == nullptr)
				RADI_ASSERT(file, "Could not open file '", filepath, "'!");

			fseek(file, 0, SEEK_END);
			unsigned long length = ftell(file);
			char* data = new char[length + 1];
			memset(data, 0, length + 1);
			fseek(file, 0, SEEK_SET);
			fread(data, 1, length, file);
			fclose(file);

			String result(data);
			delete[] data;

			return result;			
		}
	}
}
