#include "tfm.hpp"
#include "dwmapi.h"
#include "D3DOverlay.h"

bool tfm::variables::menu::showMenu = true;
HWND tfm::menu::windowHandle = NULL;
HWND tfm::menu::overlayWindow = NULL;

tfm::enums::TfmMenuTabs tfm::variables::menu::selectedTab;

using X2295::D3DOverlay;
int currentItem;

auto tfm::menu::render(FLOAT aWidth, FLOAT aHeight) -> VOID
{
	static bool vIsEnableEsp = FALSE;

	if (!tfm::variables::menu::showMenu || 
		windowHandle != GetForegroundWindow() &&
		overlayWindow != GetForegroundWindow())
		return;

	//ImGui::ShowDemoWindow();
	ImGui::Begin("TFM Packet Builder");
	/*ImGui::Columns(2);
	ImGui::SetColumnOffset(1, 120);

	ImGui::Spacing();

	if (ImGui::Button("Room", ImVec2(100, 40)))
		variables::menu::selectedTab = tfm::enums::TfmMenuTabs::Room;

	ImGui::Spacing();

	if (ImGui::Button("Players", ImVec2(100, 40)))
		variables::menu::selectedTab = tfm::enums::TfmMenuTabs::Players;

	ImGui::Spacing();

	if (ImGui::Button("Me", ImVec2(100,40)))
		variables::menu::selectedTab = tfm::enums::TfmMenuTabs::Me;

	ImGui::NextColumn();

	switch (variables::menu::selectedTab)
	{
		case tfm::enums::TfmMenuTabs::Room:
			ImGui::Button("Simple button", ImVec2(100,40));
			break;

		case tfm::enums::TfmMenuTabs::Me:
			ImGui::Checkbox("Instant Cheese", &tfm::variables::instantCheese);
			ImGui::Checkbox("Instant Hole", &tfm::variables::instantHole);
			break;
	}*/
	static const char* items[] = {"Byte(1)", "Short(255)", "Short(255)" , "Short(255)" , "Short(255)" , "Short(255)" , "Short(255)" , "Short(255)" , "Short(255)" , "Short(255)" , "Short(255)" };

	ImGui::SetWindowSize(ImVec2(427, 308));
	ImGui::Columns(2, nullptr, false);
	ImGui::SetColumnWidth(0, 170);
	ImGui::SetColumnWidth(1, 250);



	//listbox
	ImGui::BeginListBox("", ImVec2(150, 250));
	ImGui::ListBox("", &currentItem, items, 11);
	ImGui::EndListBox();
	
	ImGui::NextColumn();

	ImGui::SetCursorPos(ImVec2(100, 50));
	ImGui::Text("Hello");

	//ImGui::ListBox("", &currentItem, items, 2);

	ImGui::End();
}

BOOL CALLBACK EnumWindowsProc(
	_In_ HWND   hwnd,
	_In_ LPARAM lParam
)
{
	DWORD pid;
	GetWindowThreadProcessId(hwnd, &pid);

	if (pid == GetCurrentProcessId())
	{
		tfm::menu::windowHandle = hwnd;
		return FALSE;
	}

	return TRUE;
}

HWND tfm::menu::getCurrentWindow()
{
	EnumWindows(EnumWindowsProc, 0);
	return windowHandle;
}

void tfm::menu::listenKeyPress()
{
	while (true)
	{
		if (GetAsyncKeyState(VK_DELETE) & 1)
			tfm::variables::menu::showMenu = !tfm::variables::menu::showMenu;

		Sleep(100);
	}
}


void tfm::menu::initialize()
{
	windowHandle = FindWindowA(NULL, "Transformice");

	CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)listenKeyPress, NULL, 0, 0);

	if (IsWindow(windowHandle))
	{
		if (D3DOverlay::InitOverlay(L"xxxxxxx", L"xxxxxx"))
		{
			overlayWindow = D3DOverlay::GetOverlayWindow();
			D3DOverlay::SetUserRender(render);
			while (D3DOverlay::MsgLoop() && D3DOverlay::AttachWindow(windowHandle));
		}
	}
}