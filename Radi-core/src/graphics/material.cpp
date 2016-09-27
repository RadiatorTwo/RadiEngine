#include "material.h"

#include <sstream>

namespace radi {
	namespace graphics {

		Material::Material(Shader* shader)
			: m_shader(shader)
		{
			InitUniformStorage();
		}

		Material::~Material()
		{
			delete m_shader;
		}

		void Material::InitUniformStorage()
		{
			m_uniformDataSize = 0;
			const std::vector<ShaderUniformDeclaration*>& uniforms = m_shader->GetUniformDeclarations();
			for (ShaderUniformDeclaration* uniform : uniforms)
				m_uniformDataSize += uniform->GetSize();

			m_uniformData = new byte[m_uniformDataSize];
			memset(m_uniformData, 0, m_uniformDataSize);
		}

		const ShaderUniformDeclaration* Material::GetUniformDeclaration(const String& name) const
		{
			for (ShaderUniformDeclaration* uniform : m_shader->GetUniformDeclarations())
			{
				if (uniform->GetName() == name)
					return uniform;
			}
			return nullptr;
		}

		void Material::DumpUniformData() const
		{
			RADI_INFO("Dumping uniforms for Material ", (long)this);
			const std::vector<ShaderUniformDeclaration*>& uniforms = m_shader->GetUniformDeclarations();
			for (uint i = 0; i < uniforms.size(); i++)
			{
				ShaderUniformDeclaration* declaration = uniforms[i];
				switch (declaration->GetType())
				{
				case ShaderUniformDeclaration::Type::MAT4:
					RADI_INFO(declaration->GetName(), " = ", GetUniform<maths::mat4>(declaration)->ToString());
					break;
				}
			}
		}

		void Material::Bind() const
		{
			// TODO: Textures. This needs to be resolved by the renderer.

			m_shader->bind();
			m_shader->ResolveAndSetUniforms(m_uniformData, m_uniformDataSize);
		}

		void Material::Unbind() const
		{
			m_shader->unbind();
		}

		MaterialInstance::MaterialInstance(Material* material)
			: m_material(material)
		{

		}

	}
}