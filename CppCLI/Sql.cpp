#include "Sql.h"
#include "pch.h"

bool SQLConnector::SanitizeConnectionString(const System::String^ conn_string)
{
	//TODO implement this method
	return true;
}

bool SQLConnector::EstablishConnection(System::String^ conn_string)
{
	if (!SanitizeConnectionString(conn_string))
	{
		return false;
	}

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

/*
* auto query = gcnew System::String("SELECT * FROM SalesLT.Address");
		{
			auto command = gcnew System::Data::SqlClient::SqlCommand(query, sql_connection);
			sql_connection->Open();
			{
				{
					System::Data::SqlClient::SqlDataReader^ reader = command->ExecuteReader();
					if (reader->HasRows)
					{
						System::Console::WriteLine("{0}", reader->GetName(0));
					}
				}
			}
		}
*/