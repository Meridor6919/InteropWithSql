#include "pch.h"
#include "LoginPage.h"

void LoginPage::ButtonClicked()
{
	exit(0);
}

void LoginPage::LoginChanged()
{
	exit(0);
}

void LoginPage::PasswordChanged()
{
	exit(0);
}

void LoginPage::Init()
{
	auto temp_ptr = gcnew WPF::LoginPage();
	auto login_change_delegate = gcnew WPF::LoginPage::EventHandlerDelegate(this, &LoginPage::LoginChanged);
	auto password_change_delegate = gcnew WPF::LoginPage::EventHandlerDelegate(this, &LoginPage::PasswordChanged);
	auto button_click_delegate = gcnew WPF::LoginPage::EventHandlerDelegate(this, &LoginPage::ButtonClicked);
	temp_ptr->event_ptrs[(int)WPF::Events::LoginChange] = login_change_delegate;
	temp_ptr->event_ptrs[(int)WPF::Events::PasswordChange] = password_change_delegate;
	temp_ptr->event_ptrs[(int)WPF::Events::ButtonClick] = button_click_delegate;
	this->page = temp_ptr;
}
