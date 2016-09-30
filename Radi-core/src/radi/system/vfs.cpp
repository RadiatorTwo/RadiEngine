#include "radi/rd.h"
#include "VFS.h"

#include "Memory.h"
#include "filesystem.h"
#include "radi/utils/Log.h"

namespace radi {

	VFS* VFS::s_Instance = nullptr;

	void VFS::Init()
	{
		s_Instance = rdnew VFS();
	}

	void VFS::Shutdown()
	{
		rddel s_Instance;
	}

	void VFS::Mount(const String& virtualPath, const String& physicalPath)
	{
		RADI_ASSERT(s_Instance);
		m_MountPoints[virtualPath].push_back(physicalPath);
	}

	void VFS::Unmount(const String& path)
	{
		RADI_ASSERT(s_Instance);
		m_MountPoints[path].clear();
	}

	bool VFS::ResolvePhysicalPath(const String& path, String& outPhysicalPath)
	{
		if (path[0] != '/')
		{
			outPhysicalPath = path;
			return FileSystem::FileExists(path);
		}

		std::vector<String> dirs = SplitString(path, '/');
		const String& virtualDir = dirs.front();

		if (m_MountPoints.find(virtualDir) == m_MountPoints.end() || m_MountPoints[virtualDir].empty())
			return false;

		String remainder = path.substr(virtualDir.size() + 1, path.size() - virtualDir.size());
		for (const String& physicalPath : m_MountPoints[virtualDir])
		{
			String path = physicalPath + remainder;
			if (FileSystem::FileExists(path))
			{
				outPhysicalPath = path;
				return true;
			}
		}
		return false;
	}

	byte* VFS::ReadFile(const String& path)
	{
		RADI_ASSERT(s_Instance);
		String physicalPath;
		return ResolvePhysicalPath(path, physicalPath) ? FileSystem::ReadFile(physicalPath) : nullptr;
	}

	String VFS::ReadTextFile(const String& path)
	{
		RADI_ASSERT(s_Instance);
		String physicalPath;
		return ResolvePhysicalPath(path, physicalPath) ? FileSystem::ReadTextFile(physicalPath) : nullptr;
	}

	bool VFS::WriteFile(const String& path, byte* buffer)
	{
		RADI_ASSERT(s_Instance);
		String physicalPath;
		return ResolvePhysicalPath(path, physicalPath) ? FileSystem::WriteFile(physicalPath, buffer) : false;

	}

	bool VFS::WriteTextFile(const String& path, const String& text)
	{
		RADI_ASSERT(s_Instance);
		String physicalPath;
		return ResolvePhysicalPath(path, physicalPath) ? FileSystem::WriteTextFile(physicalPath, text) : false;
	}

}