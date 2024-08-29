#include "../main.h"

/* Dynamic library is being loaded */
void framework::Attach(HINSTANCE hInstance) {
	LuaInterface = CaptureInterface<CLuaShared>("lua_shared.dll", "LUASHARED003");

	if (!LuaInterface)
		throw;

	ILuaBase* menu = LuaInterface->GetLuaInterface(2);

	if (!menu)
		throw;
	 
	Features::Push(menu);
}

/* Dynamic library is being unloaded */
void framework::Detach() {

} 