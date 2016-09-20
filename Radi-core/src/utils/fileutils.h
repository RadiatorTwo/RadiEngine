#pragma once
#include <string>
#include <iostream>
#include <fstream>

namespace radi
{
	namespace utils
	{
		static std::string read_file(const char* filepath)
		{
			// ReSharper disable once CppDeprecatedEntity
			FILE* file = fopen(filepath, "rt");
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
