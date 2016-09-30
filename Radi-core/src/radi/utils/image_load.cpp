#include "radi/rd.h"
#include "image_load.h"

#include <FreeImage.h>
#include <FreeImage/Utilities.h>

#include "radi/system/Memory.h"

namespace radi {

	byte* LoadImage(const char* filename, uint* width, uint* height, uint* bits, bool flipY)
	{
		FREE_IMAGE_FORMAT fif = FIF_UNKNOWN;
		FIBITMAP* dib = nullptr;
		fif = FreeImage_GetFileType(filename, 0);
		if (fif == FIF_UNKNOWN)
			fif = FreeImage_GetFIFFromFilename(filename);
		if (fif == FIF_UNKNOWN)
			return nullptr;

		if (FreeImage_FIFSupportsReading(fif))
			dib = FreeImage_Load(fif, filename);

		RADI_ASSERT(dib, "Could not load image '", filename, "'!");

		FIBITMAP* bitmap = FreeImage_ConvertTo32Bits(dib);
		FreeImage_Unload(dib);

		byte* pixels = FreeImage_GetBits(bitmap);
		uint w = FreeImage_GetWidth(bitmap);
		uint h = FreeImage_GetHeight(bitmap);
		uint b = FreeImage_GetBPP(bitmap);

		if (flipY)
			FreeImage_FlipVertical(bitmap);

		if (FreeImage_GetRedMask(bitmap) == 0xff0000)
			SwapRedBlue32(bitmap);

		if (width)
			*width = w;
		if (height)
			*height = h;
		if (bits)
			*bits = b;

		int32 size = w * h * (b / 8);
		byte* result = rdnew byte[size];
		memcpy(result, pixels, size);
		FreeImage_Unload(bitmap);
		return result;
	}

	byte* LoadImage(const String& filename, uint* width, uint* height, uint* bits, bool flipY)
	{
		return LoadImage(filename.c_str(), width, height, bits, flipY);
	}

}