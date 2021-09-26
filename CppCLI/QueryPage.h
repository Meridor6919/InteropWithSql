#pragma once
#include "Page.h"

public ref class QueryPage : public Page
{
	void ButtonClicked();
	void SQLQueryChanged();

public:
	QueryPage(SQLConnector^ sql_connector, HWND main_window) : Page(sql_connector, main_window) {}
	void Init() override;
};

