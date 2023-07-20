#ifndef X2295_UTILS_OVERLAY
#define X2295_UTILS_OVERLAY 1

#include <windows.h>
#include <tchar.h>
#include <memory>
#include <thread>
#include <functional>
#include <array>
#include <dwmapi.h>
#include <d3d11.h>
#include <string>
#include <d3dcompiler.h>

#include "imgui/imgui.h"
#include "imgui/imgui_impl_dx11.h"
#include "imgui/imgui_impl_win32.h"

#pragma comment(lib,"d3d11.lib")
#pragma comment(lib,"dwmapi.lib")
#pragma comment(lib,"d3dcompiler") // Automatically link with d3dcompiler.lib as we are using D3DCompile() below.

namespace X2295
{
	using _D3DOVERLAY_USER_RENDER = std::function<VOID(FLOAT, FLOAT)>;
	class D3DOverlay
	{
	private:
		static HWND m_vWnd;
		static BOOLEAN m_vMsgLoop;
		static WNDCLASSEX m_vWndClass;
		static MSG m_vWndMsg;
		static FLOAT m_vRenderWidth;
		static FLOAT m_vRenderHeight;
		static RECT m_vOldRect;
		static _D3DOVERLAY_USER_RENDER m_vUserRender;

		static ID3D11Device* ms_vD3dDevice;
		static ID3D11DeviceContext* ms_vDeviceContext;
		static IDXGISwapChain* ms_vSwapChain;
		static ID3D11RenderTargetView* ms_vRenderTargetView;

		static auto WINAPI WndProc(HWND aHwnd, UINT aMsg, WPARAM aWParam, LPARAM aLParam)->LRESULT;

		static auto Reset()->VOID;
		static auto CreateOverlay(LPCTSTR aWndClassName, LPCTSTR aWndName)->BOOLEAN;
		static auto CleanupOverlay()->VOID;
		static auto CreateDeviceD3D()->BOOLEAN;
		static auto CleanupDeviceD3D()->VOID;
		static auto CreateRenderTarget()->VOID;
		static auto CleanupRenderTarget()->VOID;
		static auto CreateImGuiContext()->VOID;
		static auto CleanupImGuiContext()->VOID;
	public:
		static auto SetUserRender(const _D3DOVERLAY_USER_RENDER& aUserRender)->VOID;
		static auto InitOverlay(LPCTSTR aWndClassName, LPCTSTR aWndName)->BOOLEAN;
		static auto UninitOverlay()->VOID;
		static auto MsgLoop()->BOOLEAN;
		static auto AttachWindow(const HWND aWnd)->BOOLEAN;
		static auto DrawCrossHair(const FLOAT aSize, ImU32 aColor)->VOID;
		static auto DrawEspBox(const ImVec2& aPos, const FLOAT aWidth, const FLOAT aHeight, ImU32 aColor, const FLOAT aLineWidth=2.f)->VOID;
		static auto DrawLine(const ImVec2& aPoint1, const ImVec2 aPoint2,ImU32 aColor, const FLOAT aLineWidth=2.f)->VOID;
		static auto DrawCircle(const ImVec2& aPoint, const FLOAT aR, ImU32 aColor, const FLOAT aLineWidth=2.f)->VOID;
		static auto DrawString(const ImVec2& aPos, const std::string& aString, ImU32 aColor)->VOID;
		static auto IsInScrren(const ImVec2& aPos)->BOOLEAN;
		static auto GetOverlayWindow() -> HWND;
	};
}

#endif