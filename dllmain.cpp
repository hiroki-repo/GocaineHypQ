// dllmain.cpp : DLL アプリケーションのエントリ ポイントを定義します。
#include "pch.h"
#include "stdlib.h"

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}

struct HyperQObj{
	UINT64 Gposin;
	UINT64 Gposout;
	UINT64 Gposmax;
	char Obj[1];
};

extern "C" __declspec(dllexport) HyperQObj* NewQueue(UINT64 size) { HyperQObj* ret = (HyperQObj*)malloc(sizeof(HyperQObj) + size); if (ret == 0) { return 0; } ret->Gposmax = size; return ret; }
extern "C" __declspec(dllexport) void PushQueueb(HyperQObj* Q, UINT8 data) { *(UINT8*)(Q->Obj[Q->Gposin]) = data; Q->Gposin += 1; if (Q->Gposin >= Q->Gposmax) { Q->Gposin = 0; } }
extern "C" __declspec(dllexport) void PushQueuew(HyperQObj* Q, UINT16 data) { *(UINT16*)(Q->Obj[Q->Gposin]) = data; Q->Gposin += 2; if (Q->Gposin >= Q->Gposmax) { Q->Gposin = 0; } }
extern "C" __declspec(dllexport) void PushQueued(HyperQObj* Q, UINT32 data) { *(UINT32*)(Q->Obj[Q->Gposin]) = data; Q->Gposin += 4; if (Q->Gposin >= Q->Gposmax) { Q->Gposin = 0; } }
extern "C" __declspec(dllexport) void PushQueueq(HyperQObj* Q, UINT64 data) { *(UINT64*)(Q->Obj[Q->Gposin]) = data; Q->Gposin += 8; if (Q->Gposin >= Q->Gposmax) { Q->Gposin = 0; } }
extern "C" __declspec(dllexport) UINT8 PopQueueb(HyperQObj* Q) { UINT8 ret = *(UINT8*)(Q->Obj[Q->Gposout]); Q->Gposout += 1; if (Q->Gposout >= Q->Gposmax) { Q->Gposout = 0; } return ret; }
extern "C" __declspec(dllexport) UINT16 PopQueuew(HyperQObj* Q) { UINT16 ret = *(UINT16*)(Q->Obj[Q->Gposout]); Q->Gposout += 2; if (Q->Gposout >= Q->Gposmax) { Q->Gposout = 0; } return ret; }
extern "C" __declspec(dllexport) UINT32 PopQueued(HyperQObj* Q) { UINT32 ret = *(UINT32*)(Q->Obj[Q->Gposout]); Q->Gposout += 4; if (Q->Gposout >= Q->Gposmax) { Q->Gposout = 0; } return ret; }
extern "C" __declspec(dllexport) UINT64 PopQueueq(HyperQObj* Q) { UINT64 ret = *(UINT64*)(Q->Obj[Q->Gposout]); Q->Gposout += 8; if (Q->Gposout >= Q->Gposmax) { Q->Gposout = 0; } return ret; }
