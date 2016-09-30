#include "radi/rd.h"
#include "Shader.h"

#include "radi/platform/opengl/GLShader.h"
#include "radi/platform/directx/DXShader.h"

#include "radi/graphics/API/Context.h"

#include "radi/system/Memory.h"

namespace radi {
	namespace graphics {
		namespace API {

			const Shader* Shader::s_CurrentlyBound = nullptr;

			Shader* Shader::CreateFromFile(const String& name, const String& filepath, void* address)
			{
				String source = VFS::Get()->ReadTextFile(filepath);

				// TODO: Fix dynamic shader reloading
				switch (Context::GetRenderAPI())
				{
				case RenderAPI::OPENGL:
				{
					GLShader* result = address ? new(address) GLShader(name, source) : rdnew GLShader(name, source);
					result->m_Path = filepath;
					return result;
				}
				case RenderAPI::DIRECT3D:
				{
					D3DShader* result = address ? new(address) D3DShader(name, source) : rdnew D3DShader(name, source);
					result->m_FilePath = filepath;
					return result;
				}
				}
				return nullptr;
			}

			Shader* Shader::CreateFromSource(const String& name, const String& source)
			{
				switch (Context::GetRenderAPI())
				{
				case RenderAPI::OPENGL:		return rdnew GLShader(name, source);
				case RenderAPI::DIRECT3D:	return rdnew D3DShader(name, source);
				}
				return nullptr;
			}

			bool Shader::TryCompile(const String& source, String& error)
			{
				switch (Context::GetRenderAPI())
				{
				case RenderAPI::OPENGL:		return GLShader::TryCompile(source, error);
				case RenderAPI::DIRECT3D:	return D3DShader::TryCompile(source, error);
				}
				return nullptr;
			}

			bool Shader::TryCompileFromFile(const String& filepath, String& error)
			{
				String source = VFS::Get()->ReadTextFile(filepath);
				return TryCompile(source, error);
			}

		}
	}
}