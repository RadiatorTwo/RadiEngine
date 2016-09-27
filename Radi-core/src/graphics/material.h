#pragma once

#include <map>

#include <radi_types.h>
#include <graphics/shaders/Shader.h>

namespace radi {
	namespace graphics {

		class Material
		{
		private:
			Shader* m_shader;
			byte* m_uniformData;
			uint m_uniformDataSize;
		public:
			Material(Shader* shader);
			~Material();

			void Bind() const;
			void Unbind() const;
			void DumpUniformData() const;

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

		class MaterialInstance
		{
		private:
			Material* m_material;
			byte* m_uniformData;
		public:
			MaterialInstance(Material* material);

			inline Material* GetMaterial() const { return m_material; }

			void Bind() const;
			void Unbind() const;

			template<typename T>
			void SetUniform(const String& name, const T& value)
			{
				RADI_ASSERT(false, "Unknown type");
			}

			template<> void SetUniform<float>(const String& name, const float& value) { }
		private:
			void InitUniformStorage();
		};

	}
}