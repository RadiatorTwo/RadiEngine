#include "shader.h"

#include <GL/glew.h>

namespace radi
{
	namespace graphics
	{
		Shader::Shader(const char* name, const char* vertSrc, const char* fragSrc)
			: m_name(name), m_vertSrc(vertSrc), m_fragSrc(fragSrc)
		{
			m_shaderID = Load(m_vertSrc, m_fragSrc);
		}

		Shader::Shader(const char* vertPath, const char* fragPath)
			: m_name(vertPath), m_vertPath(vertPath), m_fragPath(fragPath)
		{
			std::string vertSourceString = utils::read_file(m_vertPath);
			std::string fragSourceString = utils::read_file(m_fragPath);

			m_vertSrc = vertSourceString.c_str();
			m_fragSrc = fragSourceString.c_str();
			m_shaderID = Load(m_vertSrc, m_fragSrc);
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

		GLuint Shader::Load(const char* vertSrc, const char* fragSrc)
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
				RADI_ERROR("Failed to compile vertex shader!");
				RADI_ERROR(&error[0]);
				RADI_ASSERT(false, "Failed to compile vertex shader!");
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
				RADI_ERROR("Failed to compile fragment shader!");
				RADI_ERROR(&error[0]);
				RADI_ASSERT(false, "Failed to compile fragment shader!");
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

		GLint Shader::GetUniformLocation(const GLchar* name)
		{
			GLint result = glGetUniformLocation(m_shaderID, name);
			if (result == -1)
				RADI_ERROR(m_name, ": could not find uniform ", name, " in shader!");

			return result;
		}

		void Shader::SetUniform1f(const GLchar* name, float value)
		{
			glUniform1f(GetUniformLocation(name), value);
		}

		void Shader::SetUniform1fv(const char* name, float* value, int count)
		{
			glUniform1fv(GetUniformLocation(name), count, value);
		}

		void Shader::SetUniform1i(const GLchar* name, int value)
		{
			glUniform1i(GetUniformLocation(name), value);
		}

		void Shader::SetUniform1iv(const char* name, int* value, int count)
		{
			glUniform1iv(GetUniformLocation(name), count, value);
		}

		void Shader::SetUniform2f(const GLchar* name, const maths::vec2& vector)
		{
			glUniform2f(GetUniformLocation(name), vector.x, vector.y);
		}

		void Shader::SetUniform3f(const GLchar* name, const maths::vec3& vector)
		{
			glUniform3f(GetUniformLocation(name), vector.x, vector.y, vector.z);
		}

		void Shader::SetUniform4f(const GLchar* name, const maths::vec4& vector)
		{
			glUniform4f(GetUniformLocation(name), vector.x, vector.y, vector.z, vector.w);
		}

		void Shader::SetUniformMat4(const GLchar* name, const maths::mat4& matrix)
		{
			glUniformMatrix4fv(GetUniformLocation(name), 1, GL_FALSE, matrix.elements);
		}

		void Shader::bind() const
		{
			glUseProgram(m_shaderID);
		}

		void Shader::unbind() const
		{
			glUseProgram(0);
		}

	}
}
