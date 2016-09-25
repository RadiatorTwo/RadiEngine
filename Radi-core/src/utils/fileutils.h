#pragma once
#include <string>
#include <fstream>

#include <utils/Log.h>

namespace radi
{
	namespace utils
	{
		static std::string read_file(const char* filepath)
		{
			// ReSharper disable once CppDeprecatedEntity
			FILE* file = fopen(filepath, "rt");
			if (file == nullptr)
				RADI_ASSERT(file, "Could not open file '", filepath, "'!");

			fseek(file, 0, SEEK_END);
			unsigned long length = ftell(file);
			char* data = new char[length + 1];
			memset(data, 0, length + 1);
			fseek(file, 0, SEEK_SET);
			fread(data, 1, length, file);
			fclose(file);

			std::string result(data);
			delete[] data;

			return result;

			/*std::string content;
			std::ifstream fileStream(filepath, std::ios::in);

			if (!fileStream.is_open()) {
				std::cerr << "Could not read file " << filepath << ". File does not exist." << std::endl;
				return "";
			}

			std::string line = "";
			while (!fileStream.eof()) {
				std::getline(fileStream, line);
				content.append(line + "\n");
			}

			fileStream.close();
			return content;*/
		}
	}
}
