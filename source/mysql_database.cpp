
#include "mysql_database.h"
#include <mysql.h>
#include <iostream>


struct MySql_Database::Impl
{
	Impl() : num_fields(0) {}

	MYSQL mysql;
	MYSQL verb_mysql;
	MYSQL_RES *res;
	MYSQL_ROW row, end_row;
	MYSQL_FIELD *field;
	int num_fields;
};

MySql_Database::MySql_Database()
	: my_impl ( new MySql_Database::Impl() )
{
    
}

MySql_Database::~MySql_Database()
{
    disconnect();
}


void MySql_Database::connect( std::string& my_name, std::string& my_pass, std::string& my_data )
{

	try {
		mysql_init(&my_impl->mysql);
		mysql_options(&my_impl->mysql, MYSQL_OPT_COMPRESS, 0);
		mysql_options(&my_impl->mysql, MYSQL_READ_DEFAULT_GROUP, "odbc");
		if (!mysql_real_connect(&my_impl->mysql, "localhost", my_name.c_str(), my_pass.c_str(), my_data.c_str(),0,NULL,0)) {

			std::cout << "Can't connect to MySQL: is the server not running?\n";

		}
	}

	catch (...) {
		throw "Failed to connect to MySQL database\n in MySQL_Database::connect()";
	}
}

void MySql_Database::disconnect()
{
		mysql_close(&my_impl->mysql);
}
void MySql_Database::query( std::string& str, std::vector<std::string>& query_results )
{

	query_results.clear();

	try {

		if (mysql_query(&my_impl->mysql, str.c_str()) != 0) { 
			throw "Failed to connect to database or run query: " + str;
		}

		if (mysql_field_count(&my_impl->mysql) > 0) {
			if (!(my_impl->res = mysql_store_result(&my_impl->mysql))) {
				throw "Data Retrieval Error: " + str;
			}


			my_impl->num_fields = mysql_num_fields(my_impl->res);
			while(my_impl->row = mysql_fetch_row(my_impl->res)) {
	
				for (int i = 0; i < my_impl->num_fields; i++) {
					if (my_impl->row[i] == NULL) {
						query_results.push_back("");
					}
					else {
						query_results.push_back(my_impl->row[i]);
					}
				}
			}
		}

		mysql_free_result(my_impl->res);
	
	} 
	catch (...) { throw "Error Accessing Database"; }

}
void MySql_Database::command( std::string& str )
{

	try {

		if (mysql_query(&my_impl->mysql, str.c_str()) != 0) { 
			throw "Failed to connect to database or run query: " + str;
		}

	} 
	catch (...) { throw "Error Accessing Database"; }

        return;
}

