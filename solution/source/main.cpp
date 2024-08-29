#include "../main.h"

GMOD_MODULE_OPEN() { 
    return 0; 
}

GMOD_MODULE_CLOSE() {
    return 0; 
};

int __stdcall DllMain(HINSTANCE hInstDll, DWORD dwReason, void* pReserved) {
    switch (dwReason)
    {
    case DLL_PROCESS_ATTACH:
        framework::Attach(hInstDll);

        break;
    case DLL_PROCESS_DETACH:
        framework::Detach();

        break;
    }

    return 1;
}