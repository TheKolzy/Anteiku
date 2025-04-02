#ifndef ESP_H
#define ESP_H

#define NOCOMM
#define WIN32_LEAN_AND_MEAN

#include "Player.h"
#include "Vector3.h"
#include "ViewMatrix.h"

#include <imgui.h>
#include <imgui_impl_dx11.h>
#include <imgui_impl_win32.h>

#include <print>
#include <stdexcept>
#include <vector>

#include <Windows.h>

#include <d3d11.h>
#include <dwmapi.h>

class ESP // Not Const
{
public:
	ESP (const ViewMatrix& viewMatrix, const std::vector<Player>& playerList);
	~ESP()                 noexcept { cleanupImGui(); }

	void run()             noexcept; // Not Const

private:
	void showMenu()        noexcept; // Not Const
	void mainMenu()        noexcept; // Not Const

	void renderESP() const noexcept;

	bool                       m_showMenu    {};
	bool                       m_activateESP {};

	const ViewMatrix&          m_viewMatrix;
	const std::vector<Player>& m_playerList;

	// --- //

	static LRESULT WINAPI windowProcedure(HWND window, UINT message, WPARAM wordParameter
		, LPARAM longParameter)             noexcept;

	[[nodiscard]] bool initializeWindow()       noexcept;
	[[nodiscard]] bool initializeDeviceD3D()    noexcept;
	[[nodiscard]] bool initializeRenderTarget() noexcept;
	[[nodiscard]] bool initializeImGui()        noexcept;

	void startFrame()                           noexcept;
	void endFrame()                             noexcept;

	void cleanupDeviceD3D()                     noexcept;
	void cleanupRenderTarget()                  noexcept;
	void cleanupImGui()                         noexcept;

	WNDCLASSEXW             m_windowClass      {};
	HWND                    m_window           {};
	ID3D11Device*           m_device           {};
	ID3D11DeviceContext*    m_deviceContext    {};
	IDXGISwapChain*         m_swapChain        {};
	ID3D11RenderTargetView* m_renderTargetView {};
};

#endif