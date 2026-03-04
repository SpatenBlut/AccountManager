#pragma once
#pragma comment(lib, "d3d11.lib")
#pragma comment(linker, "/SUBSYSTEM:WINDOWS")

#include <windows.h>
#include <d3d11.h>
#include <sstream>
#include "FileManage.h"
#include "imgui/imgui.h"
#include "imgui/imgui_impl_win32.h"
#include "imgui/imgui_impl_dx11.h"

void gui();

