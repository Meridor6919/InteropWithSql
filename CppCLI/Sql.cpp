#include "Sql.h"
#include "pch.h"

bool SQLConnector::EstablishConnection(System::String^ conn_string)
{
	auto connection_builder = gcnew System::Data::SqlClient::SqlConnection(conn_string);
	sql_connection = gcnew System::Data::SqlClient::SqlConnection(connection_builder->ConnectionString);
	try
	{
		sql_connection->Open();
		if (sql_connection->State == System::Data::ConnectionState::Open)
		{
			return true;
		}
	}
	catch (System::Exception^ e)
	{
		return false;
	}
	return false;
}

System::Data::SqlClient::SqlCommand^ SQLConnector::SendQuery(System::String^ query)
{
	return gcnew System::Data::SqlClient::SqlCommand(query, sql_connection);
}