#include "shader_uniform.h"

#include "shader.h"

namespace radi {
	namespace graphics {

		ShaderUniformDeclaration::ShaderUniformDeclaration(Type type, const String& name, const Shader* shader, uint count)
			: m_type(type), m_name(name), m_shader(shader), m_count(count)
		{
			m_size = SizeOfUniformType(type) * count;
		}

		uint ShaderUniformDeclaration::GetSize() const
		{
			return m_size;
		}

		int ShaderUniformDeclaration::GetLocation() const
		{
			return m_location;
		}

		uint ShaderUniformDeclaration::SizeOfUniformType(Type type)
		{
			switch (type)
			{
			case ShaderUniformDeclaration::Type::FLOAT32:	return 4;
			case ShaderUniformDeclaration::Type::INT32:		return 4;
			case ShaderUniformDeclaration::Type::VEC2:		return 4 * 2;
			case ShaderUniformDeclaration::Type::VEC3:		return 4 * 3;
			case ShaderUniformDeclaration::Type::VEC4:		return 4 * 4;
			case ShaderUniformDeclaration::Type::MAT3:		return 4 * 3 * 3;
			case ShaderUniformDeclaration::Type::MAT4:		return 4 * 4 * 4;
			case ShaderUniformDeclaration::Type::SAMPLER2D:	return 4;
			}
			return 0;
		}

	}
}