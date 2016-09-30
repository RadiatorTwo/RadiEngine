#include "radi/rd.h"
#include "TextureCube.h"

#include "radi/system/Memory.h"

#include "radi/platform/opengl/GLTextureCube.h"
#include "radi/platform/directx/DXTextureCube.h"

#include "radi/graphics/API/Context.h"

namespace radi { namespace graphics { namespace API {

	TextureCube* TextureCube::CreateFromFile(const String& filepath)
	{
		switch (Context::GetRenderAPI())
		{
			case RenderAPI::OPENGL:		return spnew GLTextureCube(filepath, filepath);
			case RenderAPI::DIRECT3D:	return spnew D3DTextureCube(filepath, filepath);
		}
		return nullptr;
	}

	TextureCube* TextureCube::CreateFromFiles(const String* files)
	{
		switch (Context::GetRenderAPI())
		{
			case RenderAPI::OPENGL:		return spnew GLTextureCube(files[0], files);
			case RenderAPI::DIRECT3D:	return spnew D3DTextureCube(files[0], files);
		}
		return nullptr;
	}

	TextureCube* TextureCube::CreateFromVCross(const String* files, int32 mips)
	{
		switch (Context::GetRenderAPI())
		{
			case RenderAPI::OPENGL:		return spnew GLTextureCube(files[0], files, mips, InputFormat::VERTICAL_CROSS);
			case RenderAPI::DIRECT3D:	return spnew D3DTextureCube(files[0], files, mips, InputFormat::VERTICAL_CROSS);
		}
		return nullptr;
	}

} } }