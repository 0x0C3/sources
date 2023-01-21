#include "includes.h"
#include "console.h"

static void Init()
{
	CreateThread(0, 0, console::console, 0, 0, 0);
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD reason, LPVOID lpReserved)
{
	if (reason == DLL_PROCESS_ATTACH)
	{
		Init();
	}

	return TRUE;
}