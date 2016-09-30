#pragma once

#include "radi/Common.h"
#include "radi/radi_types.h"
#include "radi/radi_string.h"

namespace radi {

	// TODO: Multiple filesystems (eg. binary blob) should be supported
	class FileSystem
	{
	public:
		static bool FileExists(const String& path);
		static int64 GetFileSize(const String& path);

		static byte* ReadFile(const String& path);
		static bool ReadFile(const String& path, void* buffer, int64 size = -1);
		static String ReadTextFile(const String& path);

		static bool WriteFile(const String& path, byte* buffer);
		static bool WriteTextFile(const String& path, const String& text);
	};

}