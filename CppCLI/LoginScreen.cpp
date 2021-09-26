#include "pch.h"
#include "LoginScreen.h"

void LoginScreen::ButtonClicked()
{
	exit(0);
}

void LoginScreen::LoginChanged()
{
	exit(0);
}

void LoginScreen::PasswordChanged()
{
	exit(0);
}

void LoginScreen::Init()
{
	auto temp_ptr = gcnew WPF::LoginPage();
	auto login_change_delegate = gcnew WPF::LoginPage::EventHandlerDelegate(this, &LoginScreen::LoginChanged);
	auto password_change_delegate = gcnew WPF::LoginPage::EventHandlerDelegate(this, &LoginScreen::PasswordChanged);
	auto button_click_delegate = gcnew WPF::LoginPage::EventHandlerDelegate(this, &LoginScreen::ButtonClicked);
	temp_ptr->event_ptrs[(int)WPF::Events::LoginChange] = login_change_delegate;
	temp_ptr->event_ptrs[(int)WPF::Events::PasswordChange] = password_change_delegate;
	temp_ptr->event_ptrs[(int)WPF::Events::ButtonClick] = button_click_delegate;
	this->page = temp_ptr;
}
