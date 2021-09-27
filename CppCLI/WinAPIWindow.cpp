#include "pch.h"
#include "WinAPIWindow.h"
#include "LoginPage.h"
#include "QueryPage.h"
#include "GlobalData.h"

msclr::gcroot<Page^> global_active_page;
msclr::gcroot<SQLConnector^> global_sql_connector;
msclr::gcroot< System::Windows::Interop::HwndSource^> interop_hwnd;

LRESULT WinAPIWindow::DefaultMsgProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
	switch (msg)
	{
		case WM_NCCREATE:
		{
			const CREATESTRUCTW* const struct_w = reinterpret_cast<CREATESTRUCTW*>(lparam);
			WinAPIWindow* window = reinterpret_cast<WinAPIWindow*>(struct_w->lpCreateParams);
			SetWindowLongPtr(hwnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(window));
			SetWindowLongPtr(hwnd, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(MsgRedirect));
			return window->EventHandler(hwnd, msg, wparam, lparam);
		}
		default:
		{
			return DefWindowProc(hwnd, msg, wparam, lparam);
		}
	}
}

LRESULT WinAPIWindow::MsgRedirect(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
	return reinterpret_cast<WinAPIWindow*>(GetWindowLongPtr(hwnd, GWLP_USERDATA))->EventHandler(hwnd, msg, wparam, lparam);
}

LRESULT WinAPIWindow::EventHandler(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
	switch (msg)
	{
		case WM_DESTROY:
		{
			PostQuitMessage(0);
		}
		case WM_CREATE:
		{
			InitializeWPF(hwnd);
			SetPage<LoginPage>(hwnd);
			break;
		}
		default:
		{
			if (msg == ChangePageMsg)
			{
				SetPage<QueryPage>(hwnd);
			}
		}
	}
	return DefWindowProc(hwnd, msg, wparam, lparam);
}

bool WinAPIWindow::Register()
{
	WNDCLASSEX wc = {};
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = this->DefaultMsgProc;
	wc.hInstance = desc.instance_handle;
	wc.hCursor = LoadCursor(0, IDC_ARROW);
	wc.lpszClassName = desc.class_name.c_str();
	if (!RegisterClassEx(&wc))
	{
		return false;
	}
	return true;
}

void WinAPIWindow::InitializeWPF(HWND parent_window)
{
	System::Windows::Interop::HwndSourceParameters^ sourceParams = gcnew System::Windows::Interop::HwndSourceParameters("Page", 800, 600);
	sourceParams->ParentWindow = System::IntPtr(parent_window);
	sourceParams->WindowStyle = WS_VISIBLE | WS_CHILD;
	interop_hwnd = gcnew System::Windows::Interop::HwndSource(*sourceParams);
}

bool WinAPIWindow::InitWindow()
{
	global_sql_connector = gcnew SQLConnector();

	if (!this->Register())
	{
		return false;
	}
	RECT window_rect = { 0, 0, desc.window_width, desc.window_height };
	if (!AdjustWindowRect(&window_rect, WS_OVERLAPPEDWINDOW, true))
	{
		MessageBox(0, L"window rect error", L"Error", 0);
		return false;
	}
	RECT screen_rect;
	GetWindowRect(GetDesktopWindow(), &screen_rect);

	hwnd = CreateWindowEx(
		NULL,
		desc.class_name.c_str(),
		desc.title.c_str(),
		WS_OVERLAPPEDWINDOW,
		(screen_rect.right - desc.window_width) / 2,
		(screen_rect.bottom - desc.window_height) / 2,
		window_rect.right - window_rect.left,
		window_rect.bottom - window_rect.top,
		0,
		0,
		desc.instance_handle,
		this
	);
	if (!hwnd)
	{
		MessageBox(0, L"CreateWindowEx call failed", L"Error", 0);
		return false;
	}
	if (ShowWindow(hwnd, SW_SHOW))
	{
		MessageBox(0, L"ShowWindow call failed", L"Error", 0);
		return false;
	}
	if (!UpdateWindow(hwnd))
	{
		MessageBox(0, L"UpdateWindow call failed", L"Error", 0);
		return false;
	}
	return true;
}

void WinAPIWindow::Run()
{
	double delta_time = 0.0f;
	double current_time = static_cast<double>(clock()) / static_cast<double>(CLOCKS_PER_SEC);

	HANDLE timer;
	LARGE_INTEGER large_int;
	large_int.QuadPart = -166666; //60Hz

	timer = CreateWaitableTimer(0, TRUE, L"WaitableTimer");
	if (timer)
	{
		SetWaitableTimer(timer, &large_int, 0, 0, 0, 0);
	}
	else
	{
		MessageBox(0, L"Couldn't set waitible timer - fatal error", L"Error", 0);
		exit(0);
	}


	MSG msg = { 0 };
	while (msg.message != WM_QUIT)
	{
		if (PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			SetWaitableTimer(timer, &large_int, 0, 0, 0, 0);
			//Update(delta_time);
			//Render(delta_time);
			WaitForSingleObject(timer, INFINITE);

			delta_time = static_cast<double>(clock()) / 1000.0f - current_time;
			current_time = static_cast<double>(clock()) / static_cast<double>(CLOCKS_PER_SEC);
		}
	}
}
