#pragma once

#include "DXCommon.h"
#include "radi/Common.h"
#include "radi/radi_types.h"
#include "radi/radi_string.h"

#include "radi/graphics/shaders/shader_resource.h"

namespace radi { namespace graphics { namespace API {

	class D3DShaderResourceDeclaration : public ShaderResourceDeclaration
	{
	private:
		friend class D3DShader;
	public:
		enum class Type
		{
			NONE, TEXTURE2D, TEXTURECUBE, SAMPLERSTATE
		};
	private:
		Type m_Type;
		String m_Name;
		uint m_Count;
		uint m_Register;
	public:
		D3DShaderResourceDeclaration(Type type, const String& name, uint count = 1);

		inline const String& GetName() const override { return m_Name; }
		inline uint GetRegister() const override { return m_Register; }

		inline Type GetType() const { return m_Type; }
		inline uint GetCount() const { return m_Count; }
	public:
		static Type StringToType(const String& type);
		static String TypeToString(Type type);
	};

} } }