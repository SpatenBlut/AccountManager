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

	/*
	TODO:
	vector<string> zu vector<Account> ändern mit struct
	*/

    return 0;
}