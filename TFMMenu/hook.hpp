#include <windows.h>




namespace Hook
{
	bool Detour(char* pSrc, char* pDst, unsigned int len);
	PVOID TrampHook(char* pSrc, char* pDst, unsigned int len);
	PVOID DetourFunction64(PVOID pSource, PVOID pDestination, int dwLen);
}