#ifndef SQLITE_DATABASE_H
#define SQLITE_DATABASE_H

#include "database.h"
#include <memory>

class Sqlite_Database : public Database
{
    public:
        Sqlite_Database();
        ~Sqlite_Database();
        
        void connect( std::string& name, std::string& password, std::string& data );
        void disconnect();
        void query( std::string& query, std::vector<std::string>& results );
        void command( std::string& query );
    
    private:
        typedef struct Impl;
        std::auto_ptr<Impl> my_impl;
};

#endif

