
#include "ghost_database.h"


struct Ghost_Database::Impl
{
};

static int query_callback( void* data, int argc, char** argv, char** colName )
{
    return 0;
}

Ghost_Database::Ghost_Database()
                : my_impl( new Ghost_Database::Impl() )
{
    
}

Ghost_Database::~Ghost_Database()
{
}


void Ghost_Database::connect( std::string&, std::string&, std::string& data )
{
}

void Ghost_Database::disconnect()
{
}
void Ghost_Database::query( std::string& query, std::vector<std::string>& results )
{
}
void Ghost_Database::command( std::string& query )
{
}

