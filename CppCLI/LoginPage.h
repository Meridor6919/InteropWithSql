#pragma once
#include "Page.h"

public ref class LoginPage : public Page
{
	void ButtonClicked();
	void LoginChanged();
	void PasswordChanged();

public:
	void Init() override;
};

