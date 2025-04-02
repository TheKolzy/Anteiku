#include "ESP.h"

ESP::ESP(const ViewMatrix& viewMatrix, const std::vector<Player>& playerList)
	: m_viewMatrix { viewMatrix }, m_playerList { playerList }
{
	if (!initializeWindow())
		throw std::runtime_error("The overlay could not be initialized.");

	if (!initializeDeviceD3D())
	{
		cleanupDeviceD3D();
		UnregisterClassW(m_windowClass.lpszClassName, m_windowClass.hInstance);
		throw std::runtime_error("The DeviceDirect3D could not be initialized.");
	}

	if (!initializeImGui())
	{
		cleanupImGui();
		throw std::runtime_error("ImGui could not be initialized.");
	}
}

void ESP::run() noexcept // Not Const
{
	startFrame();

	mainMenu();

	endFrame();
}

void ESP::showMenu() noexcept // Not Const
{
	m_showMenu = !m_showMenu;
	LONG style { GetWindowLong(m_window, GWL_EXSTYLE) };
	if (m_showMenu)
		style &= ~WS_EX_TRANSPARENT;
	else
		style |=  WS_EX_TRANSPARENT;

	SetWindowLongW(m_window, GWL_EXSTYLE, style);
	SetLayeredWindowAttributes(m_window, RGB(0, 0, 0), BYTE(255), LWA_ALPHA | LWA_COLORKEY);
}

void ESP::mainMenu() noexcept // Not Const
{
	if (m_showMenu)
	{
		ImGui::Begin("Anteiku", &m_showMenu);

		if (ImGui::Button("Press me"))
			std::println("You pressed me.");

		if (ImGui::Button("ESP"))
			m_activateESP = !m_activateESP;	

		ImGui::End();
	}

	if (m_activateESP)
		renderESP();
}

void ESP::renderESP() const noexcept
{
	if (m_playerList[0].isAlive())
	{
		const Vector3<float> headPosition { m_playerList[0].getHead() };
		const Vector3<float> feetPosition { m_playerList[0].getBody() };

		Vector3<float> top    {};
		Vector3<float> bottom {};
		if (m_viewMatrix.worldToScreen(headPosition, top)
			&& m_viewMatrix.worldToScreen(feetPosition, bottom))
		{
			const float height { bottom.getY() - top.getY() };
			const float width  { height * 0.35f };
			ImGui::GetBackgroundDrawList()->AddRect({ top.getX() - width, top.getY() }
				, { top.getX() + width, bottom.getY() }, ImColor(255, 255, 255) );
		}
	}
}

extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND window, UINT message
	, WPARAM wordParameter, LPARAM longParameter);

LRESULT WINAPI ESP::windowProcedure(HWND window, UINT message, WPARAM wordParameter
	, LPARAM longParameter) noexcept
{
	if (ImGui_ImplWin32_WndProcHandler(window, message, wordParameter, longParameter))
		return 0L;

	if (message == WM_DESTROY)
	{
		PostQuitMessage(0);
		return 0L;
	}

	return DefWindowProcW(window, message, wordParameter, longParameter);
}

bool ESP::initializeWindow() noexcept
{
	m_windowClass = { .cbSize { sizeof(WNDCLASSEXW) }, .lpfnWndProc { windowProcedure }
		, .hInstance { GetModuleHandle(nullptr) }, .lpszClassName { L"ESP Window Class" } };
	if (!RegisterClassExW(&m_windowClass))
		return false;

	m_window = { CreateWindowExW(WS_EX_LAYERED | WS_EX_TOOLWINDOW | WS_EX_TOPMOST
		| WS_EX_TRANSPARENT, m_windowClass.lpszClassName, L"ESP Window", WS_POPUP, 0, 0
		, 800, 600, nullptr, nullptr, m_windowClass.hInstance, nullptr) };
	if (!m_window)
		return false;

	SetLayeredWindowAttributes(m_window, RGB(0, 0, 0), BYTE(255), LWA_ALPHA | LWA_COLORKEY);
	// Register Keyboard Key for the Menu
	RegisterHotKey(nullptr, 1, MOD_NOREPEAT, VK_DELETE);

	return true;
}

bool ESP::initializeDeviceD3D() noexcept
{
	DXGI_SWAP_CHAIN_DESC swapChainDescription {};
	swapChainDescription.BufferDesc.RefreshRate.Numerator   = 60U;
	swapChainDescription.BufferDesc.RefreshRate.Denominator = 1U;
	swapChainDescription.BufferDesc.Format                  = DXGI_FORMAT_R8G8B8A8_UNORM;
	swapChainDescription.SampleDesc.Count                   = 1U;
	swapChainDescription.SampleDesc.Quality                 = 0U;
	swapChainDescription.BufferUsage                        = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	swapChainDescription.BufferCount                        = 1U;
	swapChainDescription.OutputWindow                       = m_window;
	swapChainDescription.Windowed                           = TRUE;
	swapChainDescription.SwapEffect                         = DXGI_SWAP_EFFECT_DISCARD;
	swapChainDescription.Flags                              = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;

	constexpr D3D_FEATURE_LEVEL levelArray[2] { D3D_FEATURE_LEVEL_11_0, D3D_FEATURE_LEVEL_10_0 };	
	D3D_FEATURE_LEVEL level {};
	const HRESULT deviceResult { D3D11CreateDeviceAndSwapChain(nullptr, D3D_DRIVER_TYPE_HARDWARE
		, nullptr, 0U, levelArray, 2U, D3D11_SDK_VERSION, &swapChainDescription, &m_swapChain
		, &m_device, &level, &m_deviceContext) };
	if (FAILED(deviceResult))
		return false;

	return initializeRenderTarget();
}

bool ESP::initializeRenderTarget() noexcept
{
	ID3D11Texture2D* backBuffer {};
	const HRESULT bufferResult { m_swapChain->GetBuffer(0U, IID_PPV_ARGS(&backBuffer)) };
	if (FAILED(bufferResult))
		return false;

	const HRESULT renderTargetResult { m_device->CreateRenderTargetView(backBuffer
		, nullptr, &m_renderTargetView) };
	if (FAILED(renderTargetResult))
		return false;
	
	backBuffer->Release();

	return true;
}

bool ESP::initializeImGui() noexcept
{
	if (m_window)
	{
		ShowWindow  (m_window, SW_SHOWDEFAULT);
		UpdateWindow(m_window);
	}

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& inputOutput     = ImGui::GetIO();
	inputOutput.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
	inputOutput.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;

	ImGui::StyleColorsDark();

	if (!ImGui_ImplWin32_Init(m_window) || !ImGui_ImplDX11_Init(m_device, m_deviceContext))
		return false;

	return true;
}

void ESP::startFrame() noexcept
{
	MSG message {};
	while (PeekMessage(&message, nullptr, 0U, 0U, PM_REMOVE))
	{
		// Checks if any Registered Key has been Pressed
		if (message.message == WM_HOTKEY)
		{
			if (message.wParam == 1)
				showMenu();
		}
		TranslateMessage(&message);
		DispatchMessage(&message);
	}

	ImGui_ImplDX11_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();
}

void ESP::endFrame() noexcept
{
	ImGui::Render();
	constexpr float alphaColor[4] {};
	m_deviceContext->OMSetRenderTargets(1U, &m_renderTargetView, nullptr);
	if (m_renderTargetView)
		m_deviceContext->ClearRenderTargetView(m_renderTargetView, alphaColor);

	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
	m_swapChain->Present(1U, 0U);
}

void ESP::cleanupDeviceD3D() noexcept
{
	cleanupRenderTarget();
	if (m_swapChain)     { m_swapChain    ->Release(); m_swapChain     = nullptr; }
	if (m_deviceContext) { m_deviceContext->Release(); m_deviceContext = nullptr; }
	if (m_device)        { m_device       ->Release(); m_device        = nullptr; }
}

void ESP::cleanupRenderTarget() noexcept
{
	if (m_renderTargetView) { m_renderTargetView->Release(); m_renderTargetView = nullptr; }
}

void ESP::cleanupImGui() noexcept
{
	UnregisterHotKey(nullptr, 1);

	ImGui_ImplDX11_Shutdown();
	ImGui_ImplWin32_Shutdown();
	ImGui::DestroyContext();

	cleanupDeviceD3D();
	DestroyWindow   (m_window);
	UnregisterClassW(m_windowClass.lpszClassName, m_windowClass.hInstance);
}