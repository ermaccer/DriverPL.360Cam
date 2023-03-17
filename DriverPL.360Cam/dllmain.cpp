// dllmain.cpp : Defines the entry point for the DLL application.
#include "pch.h"
#include "plugin/PatternHelper.h"
#include "utils/MemoryMgr.h"
#include <Windows.h>
#include <iostream>

using namespace Memory::VP;


static bool* bIsUsingTankControls = nullptr;
static bool* bUnkCameraRelated = nullptr;
static int   pContinueAddress = 0;

void __declspec(naked) LookAroundHook()
{
    _asm {
        movss   dword ptr[ebx + 0x28], xmm0
    }
    if (bUnkCameraRelated)
         *bUnkCameraRelated = true;
    _asm      jmp pContinueAddress
}

void Init()
{
    bIsUsingTankControls = nullptr;
    bUnkCameraRelated = nullptr;
    int tankControlsPat = _pat("EB 07 C6 05 ? ? ? ? 00 A1", 4);
    bIsUsingTankControls = (bool*)(*(int*)tankControlsPat);

    int unknownCameraPat = _pat("F3 0F 11 43 28 80 3D ? ? ? ? 00", 7);
    bUnkCameraRelated = (bool*)(*(int*)unknownCameraPat);

    int togglePat = _pat("F3 0F 11 43 28 80 3D ? ? ? ? 00");
    pContinueAddress = togglePat + 5;



    InjectHook(togglePat, LookAroundHook, PATCH_JUMP);
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

