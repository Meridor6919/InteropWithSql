#include "pch.h"
#include "QueryPage.h"

void QueryPage::ButtonClicked()
{

}

void QueryPage::SQLQueryChanged()
{

}

void QueryPage::Init()
{
	auto temp_ptr = gcnew WPF::QueryPage();
	auto sqlquery_change_delegate = gcnew WPF::QueryPage::EventHandlerDelegate(this, &QueryPage::SQLQueryChanged);
	auto button_click_delegate = gcnew WPF::QueryPage::EventHandlerDelegate(this, &QueryPage::ButtonClicked);
	temp_ptr->event_ptrs[(int)WPF::QueryPageEvents::SQLQuery] = sqlquery_change_delegate;
	temp_ptr->event_ptrs[(int)WPF::QueryPageEvents::ButtonClick] = button_click_delegate;
	this->page = temp_ptr;
}
