#include "adso.h"
#include "encoding.h"
#include "text.h"


//#define USE_COMPILED 1
//#define USE_SQLITE 1
#define USE_MYSQL 1

#ifdef USE_COMPILED
  	#include "ghost_database.h"
 	typedef Ghost_Database CurrentDatabase;
#endif
#ifdef USE_SQLITE
  	#include "sqlite_database.h"
 	typedef Sqlite_Database CurrentDatabase;
#endif
#ifdef USE_MYSQL
  	#include "mysql_database.h"
  	typedef MySql_Database CurrentDatabase;
        #include <mysql.h>
#endif


struct Adso::AdsoImpl
{
	AdsoImpl( std::string name, std::string pass, std::string data, std::string verb )
			: my_name( name ), my_pass( pass ), my_data( data ), my_verb( verb ), 
			  my_database( new CurrentDatabase() ), my_verbDatabase( new CurrentDatabase() ), my_ontologyDatabase( new CurrentDatabase() )
	{
		
	}

	std::string my_name;
	std::string my_pass;
	std::string my_data;
	std::string my_verb;
	std::string my_ontology;
	
	std::auto_ptr<Database> my_database;
	std::auto_ptr<Database> my_verbDatabase;
	std::auto_ptr<Database> my_ontologyDatabase;

	
};

Adso::Adso(std::string dbusername, std::string dbpassword, std::string dbdatabase)
: my_impl( new Adso::AdsoImpl( dbusername, dbpassword, dbdatabase, "verbs" ) ) {

	query_results = new std::vector<std::string>;
	query_headers = new std::vector<std::string>;
	no_phrases = 0;
	connected_to_verb_db = 0;
	connected_to_ontology_db = 0;
	sqlite_database_location = "./";
	sqlite_verb_database_location = "./";
};

Adso::~Adso() {

	query_results->clear();
	query_headers->clear();

	delete query_results;
	delete query_headers;

};
void Adso::disconnect() {
	try {
	    my_impl->my_database->disconnect();
	    if (connected_to_verb_db == 1) {
	      my_impl->my_verbDatabase->disconnect();
	    }
	    if (connected_to_ontology_db == 1) {
	      my_impl->my_ontologyDatabase->disconnect();
	    }
	} 
	catch ( const char* str ) { std::cout << str; }
	catch (...) { std::cout << "Cannot disconnect from database?" << std::endl; }	
}

void Adso::connect() {
	#ifdef USE_SQLITE
	try {
			my_impl->my_data = sqlite_database_location;
			my_impl->my_database->connect( my_impl->my_name, my_impl->my_pass, my_impl->my_data );
	}
	#else
	try {
			my_impl->my_database->connect( my_impl->my_name, my_impl->my_pass, my_impl->my_data );
	} 
	#endif
	catch ( const char* str ) { std::cout << str; }
	catch (...) { std::cout << "Cannot connect to database?" << std::endl; }	
}
std::vector<std::string> Adso::select_query(std::string fields, std::string table) {
  if (fields.find("%") != std::string::npos) { query_results->clear(); return *query_results; }
  if (table.find("%") != std::string::npos) { query_results->clear(); return *query_results; }
  if (fields.find("\"") != std::string::npos) { query_results->clear(); return *query_results; }
  if (table.find("\"") != std::string::npos) { query_results->clear(); return *query_results; }
  std::string temp_query = "SELECT " + fields + " FROM " + table;
  return query_string(temp_query);
}
std::vector<std::string> Adso::select_query(std::string fields, std::string table, std::string where1, std::string where2) { 
  std::string temp_query = "";
  #ifdef USE_SQLITE
  if (fields.find("%") != std::string::npos) { query_results->clear(); return *query_results; }
  if (table.find("%") != std::string::npos) { query_results->clear(); return *query_results; }
  if (where1.find("%") != std::string::npos) { query_results->clear(); return *query_results; }
  if (where2.find("%") != std::string::npos) { query_results->clear(); return *query_results; }
  if (fields.find("\"") != std::string::npos) { query_results->clear(); return *query_results; }
  if (table.find("\"") != std::string::npos) { query_results->clear(); return *query_results; }
  if (where1.find("\"") != std::string::npos) { query_results->clear(); return *query_results; }
  if (where2.find("\"") != std::string::npos) { query_results->clear(); return *query_results; }
  temp_query = "SELECT " + fields + " FROM " + table + " WHERE " + where1 + " = \"" + where2 + "\"";
  #else
  temp_query = "SELECT " + fields + " FROM " + table + " WHERE " + where1 + " LIKE BINARY \"" + where2 + "\"";
  #endif
  return query_string(temp_query);
}
std::vector<std::string> Adso::select_query_wildcard(std::string fields, std::string table, std::string where1, std::string where2) { 
  std::string temp_query = "";
  #ifdef USE_SQLITE
  if (fields.find("%") != std::string::npos) { query_results->clear(); return *query_results; }
  if (table.find("%") != std::string::npos) { query_results->clear(); return *query_results; }
  if (where1.find("%") != std::string::npos) { query_results->clear(); return *query_results; }
  if (where2.find("%") != std::string::npos) { query_results->clear(); return *query_results; }
  if (fields.find("\"") != std::string::npos) { query_results->clear(); return *query_results; }
  if (table.find("\"") != std::string::npos) { query_results->clear(); return *query_results; }
  if (where1.find("\"") != std::string::npos) { query_results->clear(); return *query_results; }
  if (where2.find("\"") != std::string::npos) { query_results->clear(); return *query_results; }
  temp_query = "SELECT " + fields + " FROM " + table + " WHERE " + where1 + " LIKE \"" + where2 + "%\"";
  #else
  temp_query = "SELECT " + fields + " FROM " + table + " WHERE " + where1 + " LIKE BINARY \"" + where2 + "%\"";
  #endif
  if (no_phrases == 1) { if (table[0] == '_') { temp_query += " AND FLAG NOT REGEXP \"PHRASE\""; } }
  return query_string(temp_query);
}





int Adso::connect_verbs() {

	#ifdef USE_SQLITE
	try {
		my_impl->my_data = sqlite_verb_database_location;
		my_impl->my_database->connect( my_impl->my_name, my_impl->my_pass, my_impl->my_data );
	    	connected_to_verb_db = 1;
	}
	#else
	try {
		my_impl->my_verbDatabase->connect( my_impl->my_name, my_impl->my_pass, my_impl->my_verb );
	    	connected_to_verb_db = 1;
	} 
	#endif
	catch ( const char* str ) { std::cout << str; }
	catch (...) {
		return -1;
	}

	return 1;
}
int Adso::connect_ontology() {

	try {
	    my_impl->my_ontologyDatabase->connect( my_impl->my_name, my_impl->my_pass, my_impl->my_ontology );
	    connected_to_ontology_db = 1;
	} 
	catch ( const char* str ) { std::cout << str; }
	catch (...) {
		return -1;
	}

	return 1;
}
void Adso::command_string(std::string str) {
	query_results->clear();

	try {
	    my_impl->my_database->command( str );
	} 
	catch (...) { 
		throw "Error Accessing Database"; 
	}
	return;
}
std::vector<std::string> Adso::query_string(std::string str) {
	query_results->clear();

	try {
	    my_impl->my_database->query( str, *query_results );
	} 
	catch (...) { 
		throw "Error Accessing Database"; 
	}
	return *query_results;
}
std::vector<std::string> Adso::query_verb(std::string str) {

	query_results->clear();

	try {
	    my_impl->my_verbDatabase->query( str, *query_results );

	} 
	catch (...) { throw "Error Accessing Database"; }
	return *query_results;
}
std::vector<std::string> Adso::query_ontology(std::string str) {

	query_results->clear();

	try {
	    my_impl->my_ontologyDatabase->query( str, *query_results );
	} 
	catch (...) { throw "Error Accessing Database"; }
	return *query_results;
}




std::string Adso::pinyin_soundfile_lookup(std::string str) {

	#ifdef USE_SQLITE
	std::string query = "SELECT file FROM pinyin where pinyin = \"" + str + "\"";
	#else 
	std::string query = "SELECT file FROM pinyin where pinyin LIKE BINARY \"" + str + "\"";
	#endif
	this->query_string(query);
	if (query_results->size()) { return query_results->at(0); }
	return "";

}
std::string Adso::pinyin_lookup(std::string str) {
	return "";
//	return pinyin_lookup_encoding(str, "gb2312");
}
std::string Adso::pinyin_lookup_encoding(std::string str, std::string exco) {
	return "";
}




// No shortcuts for the UTF8 stuff -- str needs to be the actual character
int Adso::UTF8_C_key_lookup(std::string str) {
	try {
	std::string ch = str;
	#ifdef USE_SQLITE
	std::string query = "SELECT first FROM utf8s_index WHERE NAME = \"" + ch + "\"";
	#else 
	std::string query = "SELECT pkey FROM utf8s_index WHERE name LIKE BINARY '" + ch + "'";
	#endif
	this->query_string(query);
	if (query_results->size()) { return string_to_int(query_results->at(0)); }
	} catch (...) { return -1; }

	return -1;
}
std::string Adso::UTF8_C_keystr_lookup(std::string str) {
	try {
	std::string ch = str;
	#ifdef USE_SQLITE
	std::string query = "SELECT first FROM utf8c_index WHERE name = \"" + ch + "\"";
	#else
	std::string query = "SELECT pkey FROM utf8c_index WHERE name LIKE BINARY '" + ch + "'";
	#endif
	this->query_string(query);
	if (query_results->size()) { 
		return query_results->at(0); 
	}
	} catch (...) { return "-1"; }
	return "-1";
}
int Adso::UTF8_C_word_lookup(std::string str) {
	try {
	std::string pkey = this->UTF8_C_keystr_lookup(str);
	if (strcmp(pkey.c_str(), "-1") == 0) { return -1; }
	std::string query = "SELECT pkey FROM _" + pkey + " WHERE CHINESE_UTF8_C = '" + str + "'";
	this->query_string(query);
	if (query_results->size()) { return string_to_int(query_results->at(0)); }
	} catch (...) { return -1; }
	return -1;
}
// No shortcuts for the UTF8 stuff -- str needs to be the actual character
int Adso::UTF8_S_key_lookup(std::string str) {
	try {
	std::string ch = str;
	#ifdef USE_SQLITE
	std::string query = "SELECT pkey FROM utf8s_index WHERE name = \"" + ch + "\"";
	#else 
	std::string query = "SELECT pkey FROM utf8s_index WHERE name LIKE BINARY '" + ch + "'";
	#endif
	this->query_string(query);
	if (query_results->size()) { return string_to_int(query_results->at(0)); }
	} catch (...) { return -1; }
	return -1;
}
std::string Adso::UTF8_S_keystr_lookup(std::string str) {
	try {
	std::string ch = str;
	#ifdef USE_SQLITE
	std::string query = "SELECT pkey FROM utf8s_index WHERE name = \"" + ch + "\"";
	#else
	std::string query = "SELECT pkey FROM utf8s_index WHERE name LIKE BINARY '" + ch + "'";
	#endif
	this->query_string(query);
	if (query_results->size()) { 
		return query_results->at(0); 
	}
	} catch (...) { return "-1"; }
	return "-1";
}

int Adso::UTF8_S_word_lookup(std::string str) {
	try {
	std::string pkey = this->UTF8_S_keystr_lookup(str);
	if (strcmp(pkey.c_str(), "-1") == 0) { return -1; }
	std::string query = "SELECT pkey FROM _" + pkey + " WHERE CHINESE_UTF8_S = '" + str + "'";
	this->query_string(query);
	if (query_results->size()) { return string_to_int(query_results->at(0)); }
	} catch (...) { return -1; }
	return -1;
}





int Adso::key_lookup(std::string str) {
	try {
	if (str.length() < 2) { return -1; }
	std::string ch = str.substr(0,2);
	#ifdef USE_SQLITE
	std::string query = "SELECT pkey FROM character_index WHERE name = \"" + ch + "\"";
	#else 
	std::string query = "SELECT pkey FROM character_index WHERE name LIKE BINARY '" + ch + "'";
	#endif
	this->query_string(query);
	if (query_results->size()) { return string_to_int(query_results->at(0)); }
	} catch (...) { return -1; }
	return -1;
}
std::string Adso::keystr_lookup(std::string str) {

	try {
	if (str.length() < 2) { return "-1"; }
	std::string ch = str.substr(0,2);
	#ifdef USE_SQLITE
	std::string query = "SELECT pkey FROM character_index WHERE name = \"" + ch + "\"";
	#else
	std::string query = "SELECT pkey FROM character_index WHERE name LIKE BINARY '" + ch + "'";
	#endif
	query_results->clear();
	this->query_string(query);
	if (query_results->size()) { 
		return query_results->at(0); 
	}
	} catch (...) { return "-1"; }
	return "-1";
}

int Adso::word_lookup(std::string str) {

	try {
	std::string pkey = this->keystr_lookup(str);
	if (strcmp(pkey.c_str(), "-1") == 0) { return -1; }
	std::string query = "SELECT pkey FROM _" + pkey + " WHERE CHINESE = '" + str + "'";
	this->query_string(query);

	if (query_results->size()) { 
return string_to_int(query_results->at(0)); }
	} catch (...) { return -1; }
	return -1;
}	


std::string Adso::wordstr_lookup(std::string str) {
	try {
	std::string pkey = this->keystr_lookup(str);
	if (strcmp(pkey.c_str(), "-1") == 0) { return "-1"; }
	std::string query = "SELECT pkey FROM _" + pkey + " WHERE CHINESE = '" + str + "'";
	this->query_string(query);
	if (query_results->size()) { return query_results->at(0); }
	} catch (...) { return "-1"; }
	return "-1";
}	
int Adso::word_lookup(std::string str, std::string pkey) {
	try {
	std::string query = "SELECT pkey FROM _" + pkey + " WHERE CHINESE = '" + str + "'";
	this->query_string(query);
	if (query_results->size()) { return string_to_int(query_results->at(0)); }
	} catch (...) {}
	return -1;
}	


std::string Adso::wordstr_lookup(std::string str, std::string pkey) {
	try {
	std::string query = "SELECT pkey FROM _" + pkey + " WHERE CHINESE = '" + str + "'";
	this->query_string(query);
	if (query_results->size()) { return query_results->at(0); }
	} catch (...) { return "-1"; }
	return "-1";
}	



void Adso::print_info() {
	std::cout << "Printing information about Adso.cpp" << std::endl;
}


void Adso::set_my_name(std::string x) { my_impl->my_name = x; }
void Adso::set_my_pass(std::string x) { my_impl->my_pass = x; }
void Adso::set_my_data(std::string x) { my_impl->my_data = x; }
void Adso::set_my_ontology(std::string x) { my_impl->my_ontology = x; }



// Returns 1 if category definition defined in database
int Adso::database_defined(std::string str) {

	if (str == "Noun") { return 1; }
	if (str == "Verb") { return 1; }
	if (str == "Adjective") { return 1; }
	if (str == "Auxiliary") { return 1; }
	if (str == "Adverb") { return 1; }
	if (str == "Other") { return 1; }

	return 0;
}



// Converts a string into a positive integer, also converts "-1" to -1
int Adso::string_to_int(std::string str) {

	int y = 0;
	for (unsigned int i = 0; i < str.length(); i++) {
		y += str[i] - 48;
		if (i+1 != str.length()) {
			y *= 10;
		}
	}

	return y;
}
