#pragma once

template<typename tempType>
tempType* CaptureInterface(const char* _module, const char* version) {
	const HMODULE hModule = GetModuleHandleA(_module);

	typedef void* (*interface_type)(const char* ver, int ret);
	const auto temp = reinterpret_cast<interface_type>(GetProcAddress(hModule, "CreateInterface"));

	return static_cast<tempType*>(temp(version, 0));
}

namespace framework {
	inline CLuaShared* LuaInterface;

	extern void Attach(HINSTANCE hInstance);
	extern void Detach();
}