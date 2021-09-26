#pragma once

public ref class SQLConnector
{
	System::Data::SqlClient::SqlConnection^ sql_connection;

	bool SanitizeConnectionString(const System::String^ conn_string);

public:
	bool EstablishConnection(System::String^ conn_string);
};