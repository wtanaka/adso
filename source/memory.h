#ifndef MEMORY_H
#define MEMORY_H

#include <string>
#include <vector>

class Memory {

	public:
		// single characters unlikely/likely for unification (name, etc.)
		std::vector<std::string> *likely;
		std::vector<std::string> *unlikely;
		std::vector<std::string> *complements;
		std::vector<std::string> *tense;
		std::vector<std::string> *predecessors;
		std::vector<std::string> *names;

		int verb_conjugation;

		Memory();
		~Memory();

};
#endif
