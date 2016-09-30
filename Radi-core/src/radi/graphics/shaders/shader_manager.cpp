#include "radi/rd.h"
#include "shader_manager.h"

#include "radi/system/Memory.h"

namespace radi {
	namespace graphics {

		std::vector<API::Shader*> ShaderManager::s_Shaders;

		void ShaderManager::Add(API::Shader* shader)
		{
			s_Shaders.push_back(shader);
		}

		API::Shader* ShaderManager::Get(const String& name)
		{
			for (API::Shader* shader : s_Shaders)
			{
				if (shader->GetName() == name)
					return shader;
			}
			return nullptr;
		}

		void ShaderManager::Clean()
		{
			for (uint i = 0; i < s_Shaders.size(); i++)
				rddel s_Shaders[i];
		}

		void ShaderManager::Reload(const String& name)
		{
			for (uint i = 0; i < s_Shaders.size(); i++)
			{
				if (s_Shaders[i]->GetName() == name)
				{
					String path = s_Shaders[i]->GetFilePath();
					String error;
					if (!API::Shader::TryCompileFromFile(path, error))
					{
						RADI_ERROR(error);
					}
					else
					{
						s_Shaders[i]->~Shader();
						s_Shaders[i] = API::Shader::CreateFromFile(name, path, s_Shaders[i]);
						RADI_INFO("Reloaded shader: " + name);
					}
					return;
				}
			}
			RADI_WARN("Could not find '", name, "' shader to reload.");
		}

		void ShaderManager::Reload(const API::Shader* shader)
		{
			for (uint i = 0; i < s_Shaders.size(); i++)
			{
				if (s_Shaders[i] == shader)
				{
					String name = shader->GetName();
					String path = shader->GetFilePath();
					s_Shaders[i]->~Shader();
					s_Shaders[i] = API::Shader::CreateFromFile(name, path, s_Shaders[i]);
					return;
				}
			}
			RADI_WARN("Could not find specified shader to reload.");
		}


	}
}