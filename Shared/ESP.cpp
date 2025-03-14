#include "ESP.h"

ESP::ESP() noexcept
{
	setupWindow();
	setupDirect3DDevice();
	setupRenderTarget();
	setupImgui();
}

void ESP::draw()
{
	startFrame();

	ImGui::GetBackgroundDrawList()->AddCircleFilled({ 500, 500 }, 100, ImColor(1.f, 0.f, 0.f));

	endFrame();
}

extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND window, UINT message
	, WPARAM wordParameter, LPARAM longParameter);

LRESULT WINAPI ESP::windowProcedure(HWND window, UINT message, WPARAM wordParameter
	, LPARAM longParameter)
{
	if (ImGui_ImplWin32_WndProcHandler(window, message, wordParameter, longParameter))
		return 1;
	
	if (message == WM_DESTROY)
	{
		PostQuitMessage(0);
		return 0;
	}

	return DefWindowProcW(window, message, wordParameter, longParameter);
}

void ESP::setupWindow() noexcept
{
	m_windowClass = { .cbSize { sizeof(WNDCLASSEXW) }, .style { CS_HREDRAW | CS_VREDRAW }
		, .lpfnWndProc { windowProcedure }, .hInstance { GetModuleHandle(NULL) }
		, .lpszClassName { L"External Overlay Class" } };
	RegisterClassExW(&m_windowClass);
	m_window = { CreateWindowExW(WS_EX_TOPMOST | WS_EX_TRANSPARENT | WS_EX_LAYERED
		, m_windowClass.lpszClassName, L"External Overlay", WS_POPUP,	0, 0, 1920, 1080, nullptr
		, nullptr, m_windowClass.hInstance, nullptr) };

	SetLayeredWindowAttributes(m_window, RGB(0, 0, 0), BYTE(255), LWA_ALPHA);
	RECT  clientArea {};
	GetClientRect(m_window, &clientArea);
	RECT  windowArea {};
	GetWindowRect(m_window, &windowArea);
	POINT difference {};
	ClientToScreen(m_window, &difference);
	const MARGINS margins { windowArea.left + (difference.x - windowArea.left)
		, windowArea.top + (difference.y - windowArea.top), clientArea.right, clientArea.bottom };
	DwmExtendFrameIntoClientArea(m_window, &margins);
}

void ESP::setupDirect3DDevice() noexcept
{
	DXGI_SWAP_CHAIN_DESC swapChainDescriptor {};
	swapChainDescriptor.BufferDesc.Format                  = DXGI_FORMAT_R8G8B8A8_UNORM;
	swapChainDescriptor.BufferDesc.RefreshRate.Numerator   = 60;
	swapChainDescriptor.BufferDesc.RefreshRate.Denominator = 1;
	swapChainDescriptor.SampleDesc.Count                   = 1;
	swapChainDescriptor.BufferUsage                        = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	swapChainDescriptor.BufferCount                        = 2;
	swapChainDescriptor.OutputWindow                       = m_window;
	swapChainDescriptor.Windowed                           = TRUE;
	swapChainDescriptor.SwapEffect                         = DXGI_SWAP_EFFECT_DISCARD;
	swapChainDescriptor.Flags                              = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;

	constexpr D3D_FEATURE_LEVEL featureLevels[2] { D3D_FEATURE_LEVEL_11_0, D3D_FEATURE_LEVEL_10_0 };
	D3D_FEATURE_LEVEL level {};
	D3D11CreateDeviceAndSwapChain(nullptr, D3D_DRIVER_TYPE_HARDWARE, nullptr, 0, featureLevels, 2
		, D3D11_SDK_VERSION, &swapChainDescriptor, &m_swapChain, &m_device, &level, &m_deviceContext);
}

void ESP::setupRenderTarget() noexcept
{
	ID3D11Texture2D* backBuffer {};
	m_swapChain->GetBuffer(0U, IID_PPV_ARGS(&backBuffer));
	if (backBuffer)
	{
		m_device->CreateRenderTargetView(backBuffer, nullptr, &m_renderTargetView);
		backBuffer->Release();
	}
}

void ESP::setupImgui() noexcept
{
	if (m_window)
	{
		ShowWindow(m_window, SW_SHOWDEFAULT);
		UpdateWindow(m_window);
	}

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& inputOutput     = ImGui::GetIO();
	inputOutput.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
	inputOutput.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;

	ImGui::StyleColorsDark();

	ImGui_ImplWin32_Init(m_window);
	ImGui_ImplDX11_Init (m_device, m_deviceContext);
}

void ESP::startFrame() noexcept
{
	ImGui_ImplDX11_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();

	MSG message {};
	while (PeekMessage(&message, nullptr, 0U, 0U, PM_REMOVE)) {
		TranslateMessage(&message);
		DispatchMessage(&message);
	}
}

void ESP::endFrame() noexcept
{
	ImGui::Render();
	constexpr float color[4] {};
	m_deviceContext->OMSetRenderTargets(1, &m_renderTargetView, nullptr);
	if (m_renderTargetView)
		m_deviceContext->ClearRenderTargetView(m_renderTargetView, color);
	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());

	m_swapChain->Present(1, 0);
}

void ESP::cleanup() noexcept
{
	ImGui_ImplDX11_Shutdown();
	ImGui_ImplWin32_Shutdown();
	ImGui::DestroyContext();

	if (m_renderTargetView) {
		m_renderTargetView->Release();
		m_renderTargetView = nullptr;
	}
	if (m_swapChain) {
		m_swapChain->Release();
		m_swapChain = nullptr;
	}
	if (m_deviceContext) {
		m_deviceContext->Release();
		m_deviceContext = nullptr;
	}
	if (m_device) {
		m_device->Release();
		m_device = nullptr;
	}
	DestroyWindow(m_window);
	UnregisterClassW(m_windowClass.lpszClassName, m_windowClass.hInstance);
}