#include <windows.h>
#include "tfm.hpp"
#include "utils.hpp"

//typedef int(__stdcall* f_send)(SOCKET s, const char* buf, int len, int flags);
//typedef int(__stdcall* f_recv)(SOCKET s, char* buf, int len, int flags);
//
f_send oSend;
f_recv oRecv;

typedef HRESULT(__stdcall* f_EndScene)(IDirect3DDevice9* pDevice);
f_EndScene oEndScene;

SOCKET socketInstance = NULL;
int packetId = -1;
int bytesSent = 0;
int targetPlayerCode = -1;
bool fakeAccumulator = false;
int roundCode = 0;
bool interceptMessage = false;


#define D3D9_DLL_NAME "d3d9.dll"

int SendByteArray(ByteArray byteArr)
{
	ByteArray dataArr;
	dataArr.writeByte(byteArr.getLength());
	dataArr.writeByte(packetId);
	dataArr.writeBytes(byteArr.getData(), byteArr.getLength());
	return oSend(socketInstance, dataArr.getData(), dataArr.getLength(), 0);
}

int SendOldProtocolPacket(char* data)
{
	ByteArray dataArr;
	dataArr.writeByte(1);
	dataArr.writeByte(1);
	dataArr.writeUTF(data);
	return SendByteArray(dataArr);
}

int __stdcall HookedSend(SOCKET s, char* buf, int len, int flags)
{
	ByteArray packet(buf, len);

	int firstInt = packet.readInt();
	int someByte = packet.readByte();

	std::string someData = packet.readUTF();

	log("HookedSend() -> firstInt: [%i], someByte: [%i], someData: [%s]", firstInt, someByte, someData);

	return oSend(s, buf, len, flags);
}

//HRESULT __stdcall hookedEndScene(IDirect3DDevice9* pDevice)
//{
//	MessageBoxA(0, "dd", "dd", 0);
//	tfm::menu::oEndScene = (f_EndScene)(oEndScene);
//	return tfm::menu::hookedEndScene(pDevice);
//}


void SetupHooks()
{
	//if (kiero::init(kiero::RenderType::D3D9) == kiero::Status::Success)
	//{
	//	log("EndScene found at address [%p]", kiero::getMethodsTable()[42]);
	//	oEndScene = (f_EndScene)Hook::TrampHook((char*)kiero::getMethodsTable()[42], (char*)hookedEndScene, 7);
	//}

	uintptr_t sendAddress = (uintptr_t)GetProcAddress(GetModuleHandleA("ws2_32.dll"), "send");
	uintptr_t recvAddress = (uintptr_t)GetProcAddress(GetModuleHandleA("ws2_32.dll"), "recv");

	oSend = (f_send)Hook::DetourFunction64((PVOID)sendAddress, (PVOID)HookedSend, 15);
	//oRecv = (f_recv)Hook::TrampHook((char*)recvAddress, (char*)HookedRecv, 8);

	while (true)
	{
		if (GetAsyncKeyState(VK_DELETE) & 1)
		{
			POINT mousePos = Utils::GetMousePosition();

			/*for (int i = 1; i < 400; i++)
			{
				ByteArray dataArr;
				dataArr.writeByte(5);
				dataArr.writeByte(19);
				dataArr.writeInt(i);
				dataArr.writeShort(mousePos.x);
				dataArr.writeShort(mousePos.y);
				dataArr.writeShort(20);
				SendByteArray(dataArr);
			}*/

			ByteArray dataArr;
			dataArr.writeByte(5);
			dataArr.writeByte(19);
			dataArr.writeInt(roundCode);
			dataArr.writeShort(mousePos.x);
			dataArr.writeShort(mousePos.y);
			dataArr.writeShort(20);

		
			SendByteArray(dataArr);
			roundCode += 1;
			

		}

		if (GetAsyncKeyState(VK_F1) & 1)
		{
			ByteArray arr;
			arr.writeByte(6);
			arr.writeByte(6);
			arr.writeUTF("hello");
			SendByteArray(arr);
		}


		if (GetAsyncKeyState(VK_F2) & 1)
		{
			POINT mousePos = Utils::GetMousePosition();
			ByteArray arr;
			arr.writeByte(4);
			arr.writeByte(9);
			arr.writeByte(1);
			interceptMessage = true;
			SendByteArray(arr);

			/*arr.writeByte(5);
			arr.writeByte(20);
			arr.writeInt(0);
			arr.writeShort(2);
			arr.writeShort(mousePos.x);
			arr.writeShort(mousePos.y);
			arr.writeShort(0);
			arr.writeByte(0);
			arr.writeByte(0);
			arr.writeByte(1);
			arr.writeByte(0);*/

			/*ByteArray arr2;
			arr2.writeByte(arr.getLength());
			arr2.writeBytes(arr.getData(), arr.getLength());
			oRecv(socketInstance, arr2.getData(), arr2.getLength(), 0);*/

		}

		if (GetAsyncKeyState(VK_F3) & 1)
		{
			POINT p = Utils::GetMousePosition();
			ByteArray byteArr;
			byteArr.writeByte(29);
			byteArr.writeByte(21);
			byteArr.writeInt(2);
			byteArr.writeUTF("desativarStaffChat");
			SendByteArray(byteArr);

		}

		if (GetAsyncKeyState(VK_F4) & 1)
		{
			tfm::room::changeGravity(400, 400);
		}

		if (GetAsyncKeyState(VK_F5) & 1)
		{
			POINT p = Utils::GetMousePosition();

			ByteArray byteArr;
			byteArr.writeByte(1);
			byteArr.writeByte(1);
			char packet[] = { 14, 11, 1, 'dsa'};
			byteArr.writeUTF(packet);
			SendByteArray(byteArr);
		}

		Sleep(100);
	}

}





BOOL WINAPI DllMain(HMODULE hModule, DWORD dwReason, LPVOID)
{
	switch (dwReason)
	{
	case DLL_PROCESS_ATTACH:
		DisableThreadLibraryCalls(hModule);
		//AllocConsole();
		//freopen("CONOUT$", "w", stdout);
		CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)tfm::initialize, NULL, 0, 0);
		//SetupHooks();
		break;
	}


	return TRUE;
}