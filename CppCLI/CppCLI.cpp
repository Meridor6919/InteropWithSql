#include "pch.h"

#include "WinAPIWindow.h"

using namespace System;
using namespace WPF;

[STAThreadAttribute]
int APIENTRY _tWinMain(HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPTSTR    lpCmdLine,
	int       nCmdShow)
{	
	WinAPIWindowDesc desc;
	desc.class_name = L"winApi";
	desc.title = L"InteropProject";
	desc.instance_handle = hInstance;
	desc.window_width = 800;
	desc.window_height = 600;
	
	WinAPIWindow window(desc);
	window.InitWindow();
	window.Run();
    return 0;
}
