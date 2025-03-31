#ifndef ESP_H
#define ESP_H

#define NOCOMM
#define WIN32_LEAN_AND_MEAN

#include <imgui.h>
#include <imgui_impl_dx11.h>
#include <imgui_impl_win32.h>

#include <print>
#include <stdexcept>

#include <Windows.h>

#include <d3d11.h>
#include <dwmapi.h>

class ESP
{
public:
	ESP();
	~ESP() noexcept { cleanupImGui(); }

	void run() noexcept; // Not Const

private:
	void showMenu()            noexcept;
	void mainMenu()            noexcept;

	bool m_showMenu {};

	static LRESULT WINAPI windowProcedure(HWND window, UINT message, WPARAM wordParameter
		, LPARAM longParameter)             noexcept;

	[[nodiscard]] bool initializeWindow()       noexcept;
	[[nodiscard]] bool initializeDeviceD3D()    noexcept;
	[[nodiscard]] bool initializeRenderTarget() noexcept;
	[[nodiscard]] bool initializeImGui()        noexcept;

	void startFrame()          noexcept;
	void endFrame()            noexcept;

	void cleanupDeviceD3D()    noexcept;
	void cleanupRenderTarget() noexcept;
	void cleanupImGui()        noexcept;

	WNDCLASSEXW             m_windowClass      {};
	HWND                    m_window           {};
	ID3D11Device*           m_device           {};
	ID3D11DeviceContext*    m_deviceContext    {};
	IDXGISwapChain*         m_swapChain        {};
	ID3D11RenderTargetView* m_renderTargetView {};
};

#endif