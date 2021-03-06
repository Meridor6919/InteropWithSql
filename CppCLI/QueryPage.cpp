#include "pch.h"
#include "QueryPage.h"

void QueryPage::ButtonClicked()
{
	auto temp_ptr = safe_cast<WPF::QueryPage^>(page);
	System::String^ query = temp_ptr->GetSQLQuery()->Text;
	try
	{
	auto reader = sql_connector->SendQuery(query)->ExecuteReader();
	auto data_table = gcnew System::Data::DataTable();
	data_table->Load(reader);
	temp_ptr->GetDataGrid()->DataContext = data_table->DefaultView;
	reader->Close();
	}
	catch (System::Exception^ e)
	{
		temp_ptr->GetError()->Text = "SQL command error";
	}
}

void QueryPage::SQLQueryChanged()
{
	auto temp_ptr = safe_cast<WPF::QueryPage^>(page);
	temp_ptr->GetError()->Text = "";
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
