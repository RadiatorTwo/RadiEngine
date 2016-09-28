#pragma once

#include "radi/common.h"
#include "radi/radi_types.h"
#include "radi/radi_string.h"

namespace radi {
	namespace graphics {


		class RD_API ShaderUniformDeclaration
		{
		public:
			enum class Type
			{
				NONE, FLOAT32, INT32, VEC2, VEC3, VEC4, MAT3, MAT4, SAMPLER2D
			};
		private:
			friend class Shader;

			Type m_type;
			String m_name;
			uint m_size;
			uint m_count;
			uint m_offset;
			const Shader* m_shader;
			mutable int m_location;
		public:
			ShaderUniformDeclaration(Type type, const String& name, const Shader* shader, uint count = 1);
			uint GetSize() const;
			int GetLocation() const;
			inline int GetOffset() const { return m_offset; }
			inline const String& GetName() const { return m_name; }
			inline Type GetType() const { return m_type; }
		private:
			uint SizeOfUniformType(Type type);
		};

	}
}