#ifndef ADSO_H
#define ADSO_H


#include <stdio.h>


#include <string>
#include <iostream>
#include <vector>
#include <memory>


class Parser;
class Encoding;
class Text;

class Adso {

	private:
	        typedef struct AdsoImpl;
		std::auto_ptr<AdsoImpl> my_impl;
		Parser *parser;

	public:

		Encoding *encoding;	
		Text *text;

		int no_phrases;
		int connected_to_verb_db;
		int connected_to_ontology_db;

		Adso(std::string dbusername, std::string dbpassword, std::string dbdatabase);
		~Adso();


		std::vector<std::string> select_query(std::string fields, std::string table); 
		std::vector<std::string> select_query(std::string fields, std::string table, std::string where1, std::string where2); 
		std::vector<std::string> select_query_wildcard(std::string fields, std::string table, std::string where1, std::string where2); 

		std::vector<std::string> *query_results;
		std::vector<std::string> *query_headers;

		std::string sqlite_database_location;
		std::string sqlite_verb_database_location;

		void set_my_name(std::string x);
		void set_my_pass(std::string x);
		void set_my_data(std::string x);
		void set_my_ontology(std::string x);

		void print_info();
		void disconnect();			// disconnect from the main database
		void connect();				// connect to the main database
		int connect_verbs();			// connect to the verb database (0 = unsuccessful)
		int connect_ontology();			// connect to ontology database

		void command_string(std::string str);
		std::vector<std::string> query_string(std::string str);
		std::vector<std::string> query_verb(std::string str);
		std::vector<std::string> query_ontology(std::string str);

		int UTF8_C_key_lookup(std::string str);
		int UTF8_C_word_lookup(std::string str); // to do
		int UTF8_C_word_lookup(std::string str, std::string pkey); // to do
		std::string UTF8_C_keystr_lookup(std::string str);	// as above
		int UTF8_S_key_lookup(std::string str);
		int UTF8_S_word_lookup(std::string str); // to do
		int UTF8_S_word_lookup(std::string str, std::string pkey); // to do
		std::string UTF8_S_keystr_lookup(std::string str);	// as above
		int key_lookup(std::string str);
		int word_lookup(std::string str); // to do
		int word_lookup(std::string str, std::string pkey); // to do
		std::string keystr_lookup(std::string str);	// as above
		std::string pinyin_soundfile_lookup(std::string str);
		std::string pinyin_lookup(std::string str);
		std::string pinyin_lookup_encoding(std::string str, std::string exco);
		std::string wordstr_lookup(std::string str); // to do
		std::string wordstr_lookup(std::string str, std::string pkey); // to do




		int database_defined(std::string str);	// does category exist in database
		int string_to_int(std::string str);

};



#endif

