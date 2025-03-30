#ifndef ESP_H
#define ESP_H

#define NOCOMM
#define WIN32_LEAN_AND_MEAN

#include <imgui.h>
#include <imgui_impl_dx11.h>
#include <imgui_impl_win32.h>

#include <stdexcept>

#include <Windows.h>

#include <d3d11.h>
#include <dwmapi.h>

class ESP
{
public:
	ESP();

	void drawCircle() noexcept;

private:
	static LRESULT WINAPI windowProcedure(HWND window, UINT message, WPARAM wordParameter
		, LPARAM longParameter);

	[[nodiscard]] bool initializeWindow();
	[[nodiscard]] bool initializeDeviceD3D();
	[[nodiscard]] bool initializeRenderTarget();
	[[nodiscard]] bool initializeImGui();

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