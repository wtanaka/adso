#ifndef GHOST_DATABASE_H
#define GHOST_DATABASE_H

#include "database.h"
#include <memory>

class Ghost_Database : public Database
{
    public:
        Ghost_Database();
        ~Ghost_Database();
        
        void connect( std::string& name, std::string& password, std::string& data );
        void disconnect();
        void query( std::string& query, std::vector<std::string>& results );
        void command( std::string& query );
    
    private:
        typedef struct Impl;
        std::auto_ptr<Impl> my_impl;
};

#endif

