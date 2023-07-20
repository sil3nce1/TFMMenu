#include "tfm.hpp"



void tfm::initialize()
{
	uintptr_t sendAddress = (uintptr_t)GetProcAddress(GetModuleHandleA("ws2_32.dll"), "send");
	uintptr_t recvAddress = (uintptr_t)GetProcAddress(GetModuleHandleA("ws2_32.dll"), "recv");

	// Initialize network based hooks:
	tfm::network::oSend = (f_send)Hook::TrampHook((char*)sendAddress, (char*)tfm::hooks::hookedSend, 8);
	tfm::network::oRecv = (f_send)Hook::TrampHook((char*)recvAddress, (char*)tfm::hooks::hookedRecv, 8);

#ifdef _LOG
	AllocConsole();
	freopen("CONOUT$", "w", stdout);
#endif

	// Initialize packet handlers:
	packets::handlers::registerHandlers();

	// Initialize Menu:
	CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)menu::initialize, NULL, 0, 0);

}