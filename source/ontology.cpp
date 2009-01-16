#include "ontology.h"
#include <vector>
#include <fstream>
#include <string>


Ontology::Ontology() {

	ontology_contents = new std::vector<std::vector<std::string> *>;
	ontology_names    = new std::vector<std::string>;

}
Ontology::~Ontology() {

	// Clear and Delete Elements in User-Supplied Ontologies
	for (unsigned int i = 0; i < ontology_contents->size(); i++) {
	  ontology_contents->at(i)->clear();
	  delete ontology_contents->at(i);
        } 
	ontology_contents->clear();
	delete ontology_contents;

}

int Ontology::add_ontology(std::string name, std::string file) {

	ontology_contents->push_back(new std::vector<std::string>);
	ontology_names->push_back(name);

	int location = ontology_contents->size()-1;

	try {
		std::string line = "";
		std::ifstream file2parse(file.c_str());  
		while (!std::getline(file2parse, line).eof() && file2parse.fail() == 0) { 
			ontology_contents->at(location)->push_back(line);
		}
	} 
	catch (...) { return -1; }

  return 1;
}


