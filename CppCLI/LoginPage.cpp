#include "pch.h"
#include "LoginPage.h"
#include "WinAPIWindow.h"
#include "GlobalData.h"

void LoginPage::ButtonClicked()
{
	//TODO refactor this method
	auto temp_ptr = safe_cast<WPF::LoginPage^>(page);
	System::String^ login = temp_ptr->GetLogin()->Text;
	System::String^ password = temp_ptr->GetPassword()->Text;

	if (sql_connector->EstablishConnection(GetConnectionString(login, password)))
	{
		SendMessage(main_window, ChangePageMsg, 0, 0);
	}
	else
	{
		temp_ptr->GetLogin()->Text = "Login";
		temp_ptr->GetPassword()->Text = "Password";
	}
	SendMessage(main_window, ChangePageMsg, 0, 0);
}
void LoginPage::LoginChanged()
{
	
}
void LoginPage::PasswordChanged()
{
	//TODO
	//Add * for typing password
}
System::String^ LoginPage::GetConnectionString(System::String^ login, System::String^ password)
{
	System::String^ conn_string = "";
	conn_string += "Server=tcp:meridor-server.database.windows.net,1433;";
	conn_string += "Initial Catalog=SQLProjectDatabase;";
	conn_string += "Persist Security Info=False;";
	conn_string += "User ID=";
	conn_string += login + "@meridor-server;";
	conn_string += "Password=";
	conn_string += password + ";";
	conn_string += "MultipleActiveResultSets=False;";
	conn_string += "Encrypt=True;";
	conn_string += "TrustServerCertificate=False;";
	conn_string += "Connection Timeout=30;";
	return conn_string;
}
void LoginPage::Init()
{
	auto temp_ptr = gcnew WPF::LoginPage();
	auto login_change_delegate = gcnew WPF::LoginPage::EventHandlerDelegate(this, &LoginPage::LoginChanged);
	auto password_change_delegate = gcnew WPF::LoginPage::EventHandlerDelegate(this, &LoginPage::PasswordChanged);
	auto button_click_delegate = gcnew WPF::LoginPage::EventHandlerDelegate(this, &LoginPage::ButtonClicked);
	temp_ptr->event_ptrs[(int)WPF::LoginPageEvents::LoginChange] = login_change_delegate;
	temp_ptr->event_ptrs[(int)WPF::LoginPageEvents::PasswordChange] = password_change_delegate;
	temp_ptr->event_ptrs[(int)WPF::LoginPageEvents::ButtonClick] = button_click_delegate;
	this->page = temp_ptr;
}
