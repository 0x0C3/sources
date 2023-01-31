
typedef void(__fastcall* Xfunc)(const char* text);
Xfunc newfunc = (Xfunc)0x00007FF7C0F92320;

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
    {
        MessageBoxA(0, "123", "321", 0);
        while (true)
        {
            if (GetAsyncKeyState(VK_NUMPAD2) & 1)
            {
                newfunc("BB");
            }
        }
    }
    return 0;
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}

