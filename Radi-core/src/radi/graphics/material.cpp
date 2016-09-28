#include "radi/rd.h"
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

			m_shader->Bind();
			m_shader->ResolveAndSetUniforms(m_uniformData, m_uniformDataSize);
		}

		void Material::Unbind() const
		{
			m_shader->Unbind();
		}

		MaterialInstance::MaterialInstance(Material* material)
			: m_material(material), m_setUniforms(0)
		{
			InitUniformStorage();
		}

		void MaterialInstance::InitUniformStorage()
		{
			m_uniformDataSize = 0;
			const std::vector<ShaderUniformDeclaration*>& uniforms = m_material->m_shader->GetUniformDeclarations();
			for (ShaderUniformDeclaration* uniform : uniforms)
				m_uniformDataSize += uniform->GetSize();

			m_uniformData = new byte[m_uniformDataSize];
			memset(m_uniformData, 0, m_uniformDataSize);
		}

		int MaterialInstance::GetUniformDeclarationIndex(const String& name) const
		{
			std::vector<ShaderUniformDeclaration*> uniforms = m_material->m_shader->GetUniformDeclarations();
			for (uint i = 0; i < uniforms.size(); i++)
			{
				if (uniforms[i]->GetName() == name)
					return i;
			}
			return -1;
		}

		void MaterialInstance::UnsetUniform(const String& name)
		{
			int index = GetUniformDeclarationIndex(name);
			uint mask = !(1 << index);
			m_setUniforms &= mask;
		}

		void MaterialInstance::Bind() const
		{
			// TODO: Textures. This needs to be resolved by the renderer.

			m_material->Bind();

			uint overrides = m_setUniforms;
			uint index = 0;
			while (overrides > 0)
			{
				if (overrides & 1)
					m_material->m_shader->ResolveAndSetUniform(index, m_uniformData);

				overrides >>= 1;
				index++;
			}
		}

		void MaterialInstance::Unbind() const
		{
			m_material->m_shader->Unbind();
		}
	}
}