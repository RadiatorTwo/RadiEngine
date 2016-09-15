#pragma once

#include <vector>
#include <GL/glew.h>
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

			void enable() const;
			void disable() const;
		private:
			GLuint load();
		};
	}
}