#pragma once
#include "Page.h"

public ref class LoginPage : public Page
{
	void ButtonClicked();
	void LoginChanged();
	void PasswordChanged();

	System::String^ GetConnectionString(System::String^ login, System::String^ password);

public:
	LoginPage(SQLConnector^ sql_connector, HWND main_window) : Page(sql_connector, main_window) {}
	void Init() override;
};

