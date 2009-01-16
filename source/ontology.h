#ifndef ONTOLOGY_H
#define ONTOLOGY_H

#include <vector>
#include <string>


class Ontology {

	public:

		Ontology();
		~Ontology();

		std::vector<std::vector<std::string> *> *ontology_contents;
		std::vector<std::string> *ontology_names;

		int add_ontology(std::string name, std::string file);


};

#endif
