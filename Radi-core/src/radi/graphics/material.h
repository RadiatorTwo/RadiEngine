#pragma once

#include "radi/rd.h"
#include "radi/common.h"

#include <radi/radi_types.h>
#include <radi/graphics/shaders/Shader.h>

namespace radi {
	namespace graphics {

		class RD_API Material
		{
		private:
			friend class MaterialInstance;

			Shader* m_shader;
			byte* m_uniformData;
			uint m_uniformDataSize;
		public:
			Material(Shader* shader);
			~Material();

			void Bind() const;
			void Unbind() const;
			void DumpUniformData() const;

			inline Shader* GetShader() const { return m_shader; }

			template<typename T>
			void SetUniform(const String& name, const T& value)
			{
				const ShaderUniformDeclaration* uniform = GetUniformDeclaration(name);
				if (!uniform)
				{
					RADI_ERROR("Could not find uniform '", name, "'!");
					return;
				}
				memcpy(m_uniformData + uniform->GetOffset(), &value, uniform->GetSize());
			}

			template<typename T>
			const T* GetUniform(const String& name) const
			{
				return GetUniform<T>(GetUniformDeclaration(name));
			}

			template<typename T>
			const T* GetUniform(const ShaderUniformDeclaration* uniform) const
			{
				return (T*)&m_uniformData[uniform->GetOffset()];
			}

		private:
			void InitUniformStorage();
			const ShaderUniformDeclaration* GetUniformDeclaration(const String& name) const;
		};

		class RD_API MaterialInstance
		{
		private:
			Material* m_material;
			byte* m_uniformData;
			uint m_uniformDataSize;
			uint m_setUniforms;
		public:
			MaterialInstance(Material* material);

			inline Material* GetMaterial() const { return m_material; }

			void Bind() const;
			void Unbind() const;
			void UnsetUniform(const String& name);

			template<typename T>
			void SetUniform(const String& name, const T& value)
			{
				int index = GetUniformDeclarationIndex(name);
				if (index == -1)
				{
					RADI_ERROR("Could not find uniform '", name, "'!");
					return;
				}
				ShaderUniformDeclaration* uniform = m_material->m_shader->GetUniformDeclarations()[index];
				memcpy(m_uniformData + uniform->GetOffset(), &value, uniform->GetSize());

				m_setUniforms |= 1 << index;
			}

		private:
			void InitUniformStorage();
			int GetUniformDeclarationIndex(const String& name) const;
		};

	}
}