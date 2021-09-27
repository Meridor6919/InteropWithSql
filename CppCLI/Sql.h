#pragma once

public ref class SQLConnector
{
	System::Data::SqlClient::SqlConnection^ sql_connection;

public:
	bool EstablishConnection(System::String^ conn_string);
	System::Data::SqlClient::SqlDataReader^ SendQuery(System::String^ query);
};