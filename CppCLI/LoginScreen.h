#pragma once
#include "Page.h"

public ref class LoginScreen : public Page
{
	void ButtonClicked();
	void LoginChanged();
	void PasswordChanged();

public:
	void Init() override;
};

