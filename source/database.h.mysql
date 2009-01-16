#ifndef DATABASE_H
#define DATABASE_H

#include <string>
#include <vector>
#include <mysql.h>

class Database
{
    public:
        Database() {}
        virtual ~Database() {};
        
        virtual void connect( std::string& name, std::string& password, std::string& data ) = 0;
        virtual void disconnect() = 0;
        virtual void query( std::string& query, std::vector<std::string>& results ) = 0;
        virtual void command( std::string& query) = 0;
};

#endif

