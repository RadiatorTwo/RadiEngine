#pragma once

#include <vector>
#include <radigl.h>
#include "../maths/maths.h"
#include "../utils/fileutils.h"

namespace radi
{
	namespace graphics
	{
		class Shader
		{
		public:
			GLuint m_shaderID;
			const char* m_vertPath;
			const char* m_fragPath;
		public:
			Shader(const char* vertPath, const char* fragPath);
			~Shader();

			void setUniform1f(const GLchar* name, float value);
			void setUniform1fv(const GLchar* name, int count, float* value);
			void setUniform1i(const GLchar* name, int value);
			void setUniform1iv(const GLchar* name, int count, int* value);
			void setUniform2f(const GLchar* name, const maths::vec2& vector);
			void setUniform3f(const GLchar* name, const maths::vec3& vector);
			void setUniform4f(const GLchar* name, const maths::vec4& vector);
			void setUniformMat4(const GLchar* name, const maths::mat4& matrix);

			void enable() const;
			void disable() const;
		private:
			GLuint load();
			GLint getUniformLocation(const GLchar* name);
		};
	}
}