#include "shader.h"
#include <iostream>

namespace radi
{
	namespace graphics
	{
		Shader::Shader(const char* vertPath, const char* fragPath)
		:m_vertPath(vertPath), m_fragPath(fragPath)
		{
			m_shaderID = load();
		}

		Shader::~Shader()
		{
			glDeleteProgram(m_shaderID);
		}

		GLuint Shader::load()
		{
			GLuint program = glCreateProgram();

			GLuint vertex = glCreateShader(GL_VERTEX_SHADER);
			GLuint fragment = glCreateShader(GL_FRAGMENT_SHADER);

			std::string vertSourceString = utils::FileUtils::read_file(m_vertPath);
			std::string fragSourceString = utils::FileUtils::read_file(m_fragPath);

			const char* vertSource = vertSourceString.c_str();
			const char* fragSource = fragSourceString.c_str();

			glShaderSource(vertex, 1, &vertSource, NULL);
			glCompileShader(vertex);

			GLint result;
			glGetShaderiv(vertex, GL_COMPILE_STATUS, &result);
			if (result == GL_FALSE)
			{
				GLint length;
				glGetShaderiv(vertex, GL_INFO_LOG_LENGTH, &length);
				std::vector<char> error(length);
				glGetShaderInfoLog(vertex, length, &length, &error[0]);
				std::cout << "Failed to compile Vertex shader!" << std::endl;
				std::cout << &error[0] << std::endl;
				glDeleteShader(vertex); 
				return 0;
			}

			glShaderSource(fragment, 1, &fragSource, NULL);
			glCompileShader(fragment);
			
			glGetShaderiv(fragment, GL_COMPILE_STATUS, &result);
			if (result == GL_FALSE)
			{
				GLint length;
				glGetShaderiv(fragment, GL_INFO_LOG_LENGTH, &length);
				std::vector<char> error(length);
				glGetShaderInfoLog(fragment, length, &length, &error[0]);
				std::cout << "Failed to compile Fragment shader!" << std::endl;
				std::cout << &error[0] << std::endl;
				glDeleteShader(fragment);
				return 0;
			}

			glAttachShader(program, vertex);
			glAttachShader(program, fragment);

			glLinkProgram(program);
			glValidateProgram(program);

			glDeleteShader(vertex);
			glDeleteShader(fragment);

			return program;
		}

		void Shader::enable() const
		{
			glUseProgram(m_shaderID);
		}

		void Shader::disable() const
		{
			glUseProgram(0);
		}



	}
}
