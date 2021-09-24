#pragma once
#include <iostream>
#include <fstream>
#include <string>

inline std::string GetConnectionString()
{
	std::string sql_connection_string;
	std::ifstream f("sql_connection_string.txt");
	std::getline(f, sql_connection_string);
	f.close();
	return sql_connection_string;
}
inline void SqlTestConnection()
{
	auto s = gcnew System::String(GetConnectionString().c_str());
	auto connection_builder = gcnew System::Data::SqlClient::SqlConnectionStringBuilder(s);
	{
		auto sql_connection = gcnew System::Data::SqlClient::SqlConnection(connection_builder->ConnectionString);

		auto query = gcnew System::String("SELECT * FROM SalesLT.Address");
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
	}
}