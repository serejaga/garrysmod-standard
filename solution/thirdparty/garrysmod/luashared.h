#pragma once

class CLuaShared {
public:
	virtual ~CLuaShared() = 0;

	virtual void Init(void* (*)(const char*, int*), bool, void*, void*) = 0;
	virtual void Shutdown() = 0;
	virtual void DumpStats() = 0;
	virtual ILuaBase* CreateLuaInterface(unsigned char, bool) = 0;
	virtual void CloseLuaInterface(ILuaBase*) = 0;
	virtual ILuaBase* GetLuaInterface(unsigned char) = 0;
	virtual void* LoadFile(const char& path, const char& pathId, bool fromDatatable, bool fromFile) = 0;
	virtual void* GetCache(const char&) = 0;
	virtual void MountLua(const char*) = 0;
	virtual void MountLuaAdd(const char*, const char*) = 0;
	virtual void UnMountLua(const char*) = 0;
	virtual void SetFileContents(const char*, const char*) = 0;
	virtual void SetLuaFindHook(void*) = 0;
	virtual void FindScripts(const char&, const char&, void*) = 0;
	virtual const char* GetStackTraces() = 0;
	virtual void InvalidateCache(const char&) = 0;
	virtual void EmptyCache() = 0;
};