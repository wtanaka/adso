
#include "sqlite_database.h"
#include <sqlite3.h>
#include <iostream>


struct Sqlite_Database::Impl
{
    Impl() : db( 0 ) {}
    sqlite3* db;
};

static int query_callback( void* data, int argc, char** argv, char** colName )
{

    std::vector<std::string>* result = reinterpret_cast<std::vector<std::string>*>( data );

    for ( int i = 0; i < argc; ++i )
    {
        if ( argv[i] )
        {
            result->push_back( argv[i] );    
        }
        else
        {
            result->push_back( "" );
        }
    }    
    
    return 0;
}

Sqlite_Database::Sqlite_Database()
                : my_impl( new Sqlite_Database::Impl() )
{
    
}

Sqlite_Database::~Sqlite_Database()
{
    disconnect();
}


void Sqlite_Database::connect( std::string&, std::string&, std::string& data )
{
    //disconnect from any prior connections if necessary
    disconnect();

    int rc = sqlite3_open("adso.db", &my_impl->db );
    
    if ( rc )
    {
        //sqlite requires that we always close our database, even if opening fails
        disconnect();
        throw "Failed to connect to Sqlite database\n in Sqlite_Database::connect()";
    }
}

void Sqlite_Database::disconnect()
{
    if ( my_impl->db )
    {
        sqlite3_close( my_impl->db );
        my_impl->db = 0;
    }
}

void Sqlite_Database::query( std::string& query, std::vector<std::string>& results )
{

    char *msg = 0;
    int rc = 0;


    // Sqlite has this value if no results are returned
    if (my_impl->db == 0) { return; }

    rc = sqlite3_exec( my_impl->db, query.c_str(), query_callback, &results, &msg );

	// Prevent Inquiries on Non-Existing Databases
	if (query.find("_-1") != std::string::npos) { return; }

    if ( rc != SQLITE_OK )
    {
	// Prevent Error Messages from Popping Out
	msg = "";
	try {
        sqlite3_free( msg );
	} catch (...) {}
        throw "Failed to connect to database or run query: " + query;
    }
    
    if ( msg ) 
    {
        sqlite3_free( msg );
    }
}
void Sqlite_Database::command( std::string& query ) 
{
}
