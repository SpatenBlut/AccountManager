#include "gui.h"

static ID3D11Device* g_device = nullptr;
static ID3D11DeviceContext* g_ctx = nullptr;
static IDXGISwapChain* g_swap = nullptr;
static ID3D11RenderTargetView* g_rtv = nullptr;

extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND, UINT, WPARAM, LPARAM);

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    if (ImGui_ImplWin32_WndProcHandler(hwnd, msg, wParam, lParam))
        return true;
    if (msg == WM_DESTROY) {
        PostQuitMessage(0);
        return 0;
    }
    return DefWindowProcW(hwnd, msg, wParam, lParam);
}

void CreateRenderTarget() {
    ID3D11Texture2D* buf = nullptr;
    g_swap->GetBuffer(0, IID_PPV_ARGS(&buf));
    g_device->CreateRenderTargetView(buf, nullptr, &g_rtv);
    buf->Release();
}

void setup() {
    HINSTANCE hInst = GetModuleHandle(nullptr);

    int screenW = GetSystemMetrics(SM_CXSCREEN);
    int screenH = GetSystemMetrics(SM_CYSCREEN);

    WNDCLASSEXW wc = { sizeof(wc), CS_CLASSDC, WndProc, 0, 0, hInst, 0, 0, 0, 0, L"ImGui", 0 };
    RegisterClassExW(&wc);
    HWND hwnd = CreateWindowW(wc.lpszClassName, L"ImGui App",
        WS_POPUP, 0, 0, screenW, screenH, 0, 0, hInst, 0);

    SetWindowLong(hwnd, GWL_EXSTYLE, GetWindowLong(hwnd, GWL_EXSTYLE) | WS_EX_LAYERED);
    SetLayeredWindowAttributes(hwnd, RGB(0, 0, 0), 0, LWA_COLORKEY);

    DXGI_SWAP_CHAIN_DESC sd = {};
    sd.BufferCount = 2; sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    sd.OutputWindow = hwnd; sd.SampleDesc.Count = 1;
    sd.Windowed = TRUE; sd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
    D3D_FEATURE_LEVEL fl;
    D3D11CreateDeviceAndSwapChain(nullptr, D3D_DRIVER_TYPE_HARDWARE, nullptr, 0, nullptr, 0, D3D11_SDK_VERSION, &sd, &g_swap, &g_device, &fl, &g_ctx);

    CreateRenderTarget();
    ShowWindow(hwnd, SW_SHOWDEFAULT);

    ImGui::CreateContext();
    ImGui::StyleColorsDark();
    ImGui_ImplWin32_Init(hwnd);
    ImGui_ImplDX11_Init(g_device, g_ctx);

    ImGuiIO& io = ImGui::GetIO();
    io.Fonts->AddFontFromFileTTF("C:\\Windows\\Fonts\\segoeuib.ttf", 18.0f);
}

void gui() {

    setup();

    ReadFromFile();
    MSG msg = {};
    while (msg.message != WM_QUIT) {

        if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE)) {
            TranslateMessage(&msg); DispatchMessage(&msg); continue;
        }

        ImGui_ImplDX11_NewFrame();
        ImGui_ImplWin32_NewFrame();        

        ImGui::NewFrame();

        ImGui::SetNextWindowSize(ImVec2(900, 600));
        ImGui::Begin("Account Manager", nullptr, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse);

        static bool AddCheck = false;
        static char inputBuf[1024] = "";

        if (AddCheck == true) {
            ImGui::InputTextMultiline("##input", inputBuf, sizeof(inputBuf), ImVec2(883, 500));
            if (ImGui::Button("Done")) {
                // write each line to file
                std::string text(inputBuf);
                std::stringstream ss(text);
                std::string line;
                while (getline(ss, line)) {
                    if (!line.empty())
                        WriteToFile(line);
                }
                memset(inputBuf, 0, sizeof(inputBuf));
                AddCheck = false;
            }
        }
        else
        {
            static bool myCheckbox = false;
            static bool myButton = false;

            for (int i = 0; i < Accounts.size(); i++) { 

                ImGui::PushID(i);

                ImGui::SetNextItemWidth(750.0f);
                char myText[256];

                // strcpy converts Accounts vector to myText char
                strcpy_s(myText, Accounts[i].c_str()); // c_str converts the string to const char*                
                ImGui::InputText("##text", myText, sizeof(myText), ImGuiInputTextFlags_ReadOnly);
                
                ImGui::SameLine();
                if (ImGui::Button("Using")) {

                }

                ImGui::SameLine();
                if (ImGui::Button("Delete")) {

                }
                ImGui::PopID();
            }

            

            ImGui::SetCursorPos(ImVec2(10, 565));
            if (ImGui::Button("Add Account")) {
                AddCheck = true;
            }
        }        

		ImGui::End();

        ImGui::Render();
        const float clear[4] = { 0.0f, 0.0f, 0.0f, 0.0f };
        g_ctx->OMSetRenderTargets(1, &g_rtv, nullptr);
        g_ctx->ClearRenderTargetView(g_rtv, clear);
        ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
        g_swap->Present(1, 0);
    }

    ImGui_ImplDX11_Shutdown();
    ImGui_ImplWin32_Shutdown();
    ImGui::DestroyContext();
    g_rtv->Release(); g_swap->Release(); g_ctx->Release(); g_device->Release();
}