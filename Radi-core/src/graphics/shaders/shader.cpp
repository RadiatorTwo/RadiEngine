#include "shader.h"
#include <iostream>

namespace radi
{
	namespace graphics
	{
		Shader::Shader(const char* name, const char* vertSrc, const char* fragSrc)
			: m_name(name), m_vertSrc(vertSrc), m_fragSrc(fragSrc)
		{
			m_shaderID = load(m_vertSrc, m_fragSrc);
		}

		Shader::Shader(const char* vertPath, const char* fragPath)
			: m_name(vertPath), m_vertPath(vertPath), m_fragPath(fragPath)
		{
			std::string vertSourceString = utils::read_file(m_vertPath);
			std::string fragSourceString = utils::read_file(m_fragPath);

			m_vertSrc = vertSourceString.c_str();
			m_fragSrc = fragSourceString.c_str();
			m_shaderID = load(m_vertSrc, m_fragSrc);
		}

		Shader* Shader::FromFile(const char* vertPath, const char* fragPath)
		{
			return new Shader(vertPath, fragPath);
		}

		Shader* Shader::FromSource(const char* vertSrc, const char* fragSrc)
		{
			return new Shader(vertSrc, vertSrc, fragSrc);
		}

		Shader* Shader::FromSource(const char* name, const char* vertSrc, const char* fragSrc)
		{
			return new Shader(name, vertSrc, fragSrc);
		}

		Shader::~Shader()
		{
			glDeleteProgram(m_shaderID);
		}

		GLuint Shader::load(const char* vertSrc, const char* fragSrc)
		{
			GLuint program = glCreateProgram();

			GLuint vertex = glCreateShader(GL_VERTEX_SHADER);
			GLuint fragment = glCreateShader(GL_FRAGMENT_SHADER);

			glShaderSource(vertex, 1, &vertSrc, NULL);
			glCompileShader(vertex);

			GLint result;
			glGetShaderiv(vertex, GL_COMPILE_STATUS, &result);
			if (result == GL_FALSE)
			{
				GLint length;
				glGetShaderiv(vertex, GL_INFO_LOG_LENGTH, &length);
				std::vector<char> error(length);
				glGetShaderInfoLog(vertex, length, &length, &error[0]);
				std::cout << "Failed to compile vertex shader!" << std::endl << &error[0] << std::endl;
				glDeleteShader(vertex);
				return 0;
			}

			glShaderSource(fragment, 1, &fragSrc, NULL);
			glCompileShader(fragment);

			glGetShaderiv(fragment, GL_COMPILE_STATUS, &result);
			if (result == GL_FALSE)
			{
				GLint length;
				glGetShaderiv(fragment, GL_INFO_LOG_LENGTH, &length);
				std::vector<char> error(length);
				glGetShaderInfoLog(fragment, length, &length, &error[0]);
				std::cout << "Failed to compile fragment shader!" << std::endl << &error[0] << std::endl;
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

		GLint Shader::getUniformLocation(const GLchar* name)
		{
			GLint result = glGetUniformLocation(m_shaderID, name);
			if (result == -1)
				RADI_ERROR(m_name, ": could not find uniform ", name, " in shader!");

			return result;
		}

		void Shader::setUniform1f(const GLchar* name, float value)
		{
			glUniform1f(getUniformLocation(name), value);
		}

		void Shader::setUniform1fv(const GLchar* name, int count, float* value)
		{
			glUniform1fv(getUniformLocation(name), count, value);
		}

		void Shader::setUniform1i(const GLchar* name, int value)
		{
			glUniform1i(getUniformLocation(name), value);
		}

		void Shader::setUniform1iv(const GLchar* name, int count, int* value)
		{
			glUniform1iv(getUniformLocation(name), count, value);
		}

		void Shader::setUniform2f(const GLchar* name, const maths::vec2& vector)
		{
			glUniform2f(getUniformLocation(name), vector.x, vector.y);
		}

		void Shader::setUniform3f(const GLchar* name, const maths::vec3& vector)
		{
			glUniform3f(getUniformLocation(name), vector.x, vector.y, vector.z);
		}

		void Shader::setUniform4f(const GLchar* name, const maths::vec4& vector)
		{
			glUniform4f(getUniformLocation(name), vector.x, vector.y, vector.z, vector.w);
		}

		void Shader::setUniformMat4(const GLchar* name, const maths::mat4& matrix)
		{
			glUniformMatrix4fv(getUniformLocation(name), 1, GL_FALSE, matrix.elements);
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
