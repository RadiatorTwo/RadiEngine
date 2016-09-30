#include "radi/rd.h"
#include "System.h"

#include "memory_manager.h"
#include "vfs.h"

#include "radi/utils/Log.h"

namespace radi { namespace internal {

	SystemInfo System::s_SystemInfo;

	void System::Init()
	{
		RADI_INFO("Initializing RadiEngine System...");
		MemoryManager::Init();
		VFS::Init();

		s_SystemInfo.memoryInfo = MemoryManager::Get()->GetSystemInfo();
		LogSystemInfo();
	}

	void System::Shutdown()
	{
		RADI_INFO("Shutting down RadiEngine System...");
		VFS::Shutdown();
		MemoryManager::Shutdown();
	}

	SystemInfo System::GetSystemInfo()
	{
		return s_SystemInfo;
	}

	void System::LogSystemInfo()
	{
		RADI_INFO("--------------------");
		RADI_INFO(" System Information ");
		RADI_INFO("--------------------");
		s_SystemInfo.memoryInfo.Log();
	}

} }