#include "hook.hpp"

bool Hook::Detour(char* pSrc, char* pDst, unsigned int len)
{
    if (len < 5) return false;

    DWORD curProtection;
    VirtualProtect(pSrc, len, PAGE_EXECUTE_READWRITE, &curProtection);

    memset(pSrc, 0x90, len);

    uintptr_t relativeAddress = ((uintptr_t)pDst - (uintptr_t)pSrc) - 5;

    *(BYTE*)pSrc = 0xE9;
    *(uintptr_t*)((uintptr_t)pSrc + 1) = relativeAddress;

    DWORD temp;
    VirtualProtect(pSrc, len, curProtection, &temp);

    return true;
}

PVOID Hook::TrampHook(char* pSrc, char* pDst, unsigned int len)
{
    if (len < 5) return 0;

    // Create the gateway (len + 5 for the overwritten bytes + the jmp)
    void* gateway = VirtualAlloc(0, len + 5, MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE);

    //Write the stolen bytes into the gateway
    memcpy(gateway, pSrc, len);

    // Get the gateway to destination addy
    intptr_t  gatewayRelativeAddr = ((intptr_t)pSrc - (intptr_t)gateway) - 5;

    // Add the jmp opcode to the end of the gateway
    *(char*)((intptr_t)gateway + len) = 0xE9;

    // Add the address to the jmp
    *(intptr_t*)((intptr_t)gateway + len + 1) = gatewayRelativeAddr;

    // Perform the detour
    Detour(pSrc, pDst, len);

    return (char*)gateway;


}

PVOID Hook::DetourFunction64(PVOID pSource, PVOID pDestination, int dwLen)
{
    DWORD MinLen = 14;

    if (dwLen < MinLen) return NULL;

    BYTE stub[] = {
    0xFF, 0x25, 0x00, 0x00, 0x00, 0x00, // jmp qword ptr [$+6]
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 // ptr
    };

    void* pTrampoline = VirtualAlloc(0, dwLen + sizeof(stub), MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE);

    DWORD dwOld = 0;
    VirtualProtect(pSource, dwLen, PAGE_EXECUTE_READWRITE, &dwOld);

    DWORD64 retto = (DWORD64)pSource + dwLen;

    // trampoline
    memcpy(stub + 6, &retto, 8);
    memcpy((void*)((DWORD_PTR)pTrampoline), pSource, dwLen);
    memcpy((void*)((DWORD_PTR)pTrampoline + dwLen), stub, sizeof(stub));

    // orig
    memcpy(stub + 6, &pDestination, 8);
    memcpy(pSource, stub, sizeof(stub));

    for (int i = MinLen; i < dwLen; i++)
    {
        *(BYTE*)((DWORD_PTR)pSource + i) = 0x90;
    }

    VirtualProtect(pSource, dwLen, dwOld, &dwOld);
    return (void*)((DWORD_PTR)pTrampoline);
}