#pragma once

struct WinAPIWindowDesc
{
	HINSTANCE instance_handle;
	UINT window_width;
	UINT window_height;
	std::wstring title;
	std::wstring class_name;
};

class WinAPIWindow
{
	HWND hwnd;
	WinAPIWindowDesc desc;

	static LRESULT CALLBACK DefaultMsgProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);
	static LRESULT CALLBACK MsgRedirect(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);
	LRESULT EventHandler(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);

	bool Register();

public:
	WinAPIWindow(WinAPIWindowDesc desc) : desc(desc) {};
	bool InitWindow();
	void Run();
};

