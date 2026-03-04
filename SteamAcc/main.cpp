#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <windows.h>

#include <imgui.h>
#include <imgui_impl_dx11.h>
#include <imgui_impl_win32.h>

#include "FileManage.h"
#include "gui.h"

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, INT) {

	gui();

    return 0;
}