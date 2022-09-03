// dllmain.cpp : Defines the entry point for the DLL application.
#include "pch.h"
#include "plugin/PatternHelper.h"
#include "utils/MemoryMgr.h"

using namespace Memory::VP;


void Init()
{
    int togglePat = _pat("F3 0F 11 43 28 80 3D ? ? ? ? 00",11);
    Patch<char>(togglePat, 1);
}


BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
        Init();
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}

