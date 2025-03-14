#pragma once

#include "../Vendor/imgui/imgui.h                    "
#include "../Vendor/imgui/backends/imgui_impl_dx11.h "
#include "../Vendor/imgui/backends/imgui_impl_win32.h"

#include <d3d11.h>
#include <dwmapi.h>

class ESP
{
public:
	ESP() noexcept;
	
	void draw();

private:
	static LRESULT WINAPI windowProcedure(HWND window, UINT message, WPARAM wordParameter
		, LPARAM longParameter);

	void setupWindow()         noexcept;
	void setupDirect3DDevice() noexcept;
	void setupRenderTarget()   noexcept;
	void setupImgui()          noexcept;
	void startFrame()          noexcept;
	void endFrame()            noexcept;
	void cleanup()             noexcept;

	WNDCLASSEXW             m_windowClass      {};
	HWND                    m_window           {};
	ID3D11Device*           m_device           {};
	ID3D11DeviceContext*    m_deviceContext    {};
	IDXGISwapChain*         m_swapChain        {};
	ID3D11RenderTargetView* m_renderTargetView {};
};