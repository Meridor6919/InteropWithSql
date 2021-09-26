#pragma once
public ref class Page
{
public:
	SQLConnector^ sql_connector;
	System::Windows::Controls::Grid^ page;
	HWND main_window;

	Page(SQLConnector^ sql_connector, HWND main_window) : sql_connector(sql_connector), main_window(main_window) {}
	virtual void Init() {}
};

