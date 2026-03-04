#include "gui.h"

// Global DirectX 11 objects used throughout the program
static ID3D11Device* g_device = nullptr;
static ID3D11DeviceContext* g_ctx = nullptr;
static IDXGISwapChain* g_swap = nullptr;
static ID3D11RenderTargetView* g_rtv = nullptr;

// Required so ImGui can forward Win32 input events to its handler
extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND, UINT, WPARAM, LPARAM);

// FIX: WndProc war undeclared - hier definiert
LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    if (ImGui_ImplWin32_WndProcHandler(hwnd, msg, wParam, lParam))
        return true;
    if (msg == WM_DESTROY) {
        PostQuitMessage(0);
        return 0;
    }
    return DefWindowProcW(hwnd, msg, wParam, lParam);
}

// Gets the back buffer from the swap chain and creates a render target view from it
void CreateRenderTarget() {
    ID3D11Texture2D* buf = nullptr;
    g_swap->GetBuffer(0, IID_PPV_ARGS(&buf));
    g_device->CreateRenderTargetView(buf, nullptr, &g_rtv);
    buf->Release();
}

void setup() {
    // FIX: hInst war undeclared - via GetModuleHandle holen
    HINSTANCE hInst = GetModuleHandle(nullptr);

    // Get the main monitor resolution
    int screenW = GetSystemMetrics(SM_CXSCREEN);
    int screenH = GetSystemMetrics(SM_CYSCREEN);

    // Register the window class and create a borderless fullscreen window
    WNDCLASSEXW wc = { sizeof(wc), CS_CLASSDC, WndProc, 0, 0, hInst, 0, 0, 0, 0, L"ImGui", 0 };
    RegisterClassExW(&wc);
    HWND hwnd = CreateWindowW(wc.lpszClassName, L"ImGui App",
        WS_POPUP, 0, 0, screenW, screenH, 0, 0, hInst, 0);

    // Make the window transparent using a black color key
    SetWindowLong(hwnd, GWL_EXSTYLE, GetWindowLong(hwnd, GWL_EXSTYLE) | WS_EX_LAYERED);
    SetLayeredWindowAttributes(hwnd, RGB(0, 0, 0), 0, LWA_COLORKEY);

    // Describe the swap chain, then create the DirectX 11 device and swap chain together
    DXGI_SWAP_CHAIN_DESC sd = {};
    sd.BufferCount = 2; sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    sd.OutputWindow = hwnd; sd.SampleDesc.Count = 1;
    sd.Windowed = TRUE; sd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
    D3D_FEATURE_LEVEL fl;
    D3D11CreateDeviceAndSwapChain(nullptr, D3D_DRIVER_TYPE_HARDWARE, nullptr, 0,
        nullptr, 0, D3D11_SDK_VERSION, &sd, &g_swap, &g_device, &fl, &g_ctx);

    // Create the render target and show the window
    CreateRenderTarget();
    ShowWindow(hwnd, SW_SHOWDEFAULT);

    // Initialize ImGui and bind it to the Win32 window and DirectX 11 device
    ImGui::CreateContext();
    ImGui::StyleColorsDark();
    ImGui_ImplWin32_Init(hwnd);
    ImGui_ImplDX11_Init(g_device, g_ctx);

    ImGuiIO& io = ImGui::GetIO();
    io.Fonts->AddFontFromFileTTF("C:\\Windows\\Fonts\\segoeuib.ttf", 18.0f);
}

void gui() {

    setup();

    MSG msg = {};
    while (msg.message != WM_QUIT) {

        if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE)) {
            TranslateMessage(&msg); DispatchMessage(&msg); continue;
        }

        // Tell ImGui a new frame is starting
        ImGui_ImplDX11_NewFrame();
        ImGui_ImplWin32_NewFrame();        

        ImGui::NewFrame(); // start ui code

        ImGui::SetNextWindowSize(ImVec2(900, 600));
        ImGui::Begin("Account Manager", nullptr, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse);

        static bool AddCheck = false;

		if (AddCheck == true) {
            static char inputBuf[1024] = "";
            ImGui::InputTextMultiline("##input", inputBuf, sizeof(inputBuf), ImVec2(883, 500));
            if (ImGui::Button("Done")) {
                AddCheck = false;
            }
        }
        else
        {
            

            static bool myCheckbox = false;
            static bool myButton = false;

            ImGui::SetNextItemWidth(750.0f);
            static char myText[256] = "";
            ImGui::InputText("##text", myText, sizeof(myText), ImGuiInputTextFlags_ReadOnly);

            ImGui::SameLine();
            ImGui::Button("Using");

            ImGui::SameLine();
            ImGui::Button("Delete");

            ImGui::SetCursorPos(ImVec2(10, 565));
            if (ImGui::Button("Add Account")) {
                AddCheck = true;
            }
        }        

		ImGui::End(); // end ui code

        // Clear with pure black so the color key makes it fully transparent
        ImGui::Render();
        const float clear[4] = { 0.0f, 0.0f, 0.0f, 0.0f };
        g_ctx->OMSetRenderTargets(1, &g_rtv, nullptr);
        g_ctx->ClearRenderTargetView(g_rtv, clear);
        ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
        g_swap->Present(1, 0);
    }

    // Shutdown ImGui and release all DirectX 11 resources
    ImGui_ImplDX11_Shutdown();
    ImGui_ImplWin32_Shutdown();
    ImGui::DestroyContext();
    g_rtv->Release(); g_swap->Release(); g_ctx->Release(); g_device->Release();
}