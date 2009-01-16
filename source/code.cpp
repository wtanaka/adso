#include "code.h"
#include "text.h"
#include <sstream>
#include <string>
#include <vector>
#include "encoding.h"


Code::Code() {
  tokens = new std::vector<std::string>;
  compounds = new std::vector<std::string>;
  compound_xml = new std::vector<std::string>;
  compound_xml_action = new std::vector<std::string>;
}
Code::~Code() {
  tokens->clear();
  compounds->clear();
  compound_xml->clear();
  compound_xml_action->clear();
  delete tokens;
  delete compounds;
  delete compound_xml;
  delete compound_xml_action;
}


std::string Code::itoa(int x) {
	std::stringstream myStream1;
	myStream1 << x;
	return myStream1.str(); 
}

int Code::analyse_code(Text *text, std::string c, int x, int y, int z) {

  if (c.find("<DEFINE_COMPOUND") == 0) { 
	if (c.find("</DEFINE_COMPOUND>") != std::string::npos) {
		std::string defcom = c.substr(0, c.find("</DEFINE_COMPOUND>")+18);
		c = c.substr(0, c.find("</DEFINE_COMPOUND>")+18);
		define_compound(text,defcom,x,y,z);	
	}
  }



  /* Split string into IF/THEN commands */
  if (c.find("</IF><THEN>") != std::string::npos) {

    std::string if_code = "";
    std::string then_code = "";
    std::string pre_match = "";
    std::string post_match = "";

    if_code = c.substr(0, c.find("</IF><THEN>"));
    then_code = c.substr(c.find("</IF><THEN>")+11);
    if (c.find("</THEN>") != std::string::npos) {
      post_match = then_code.substr(then_code.find("</THEN>")+7);
    }


    // clean up those strings
    if (if_code.find("<IF>") != std::string::npos) {
      pre_match = if_code.substr(0, if_code.find("<IF>"));
      if_code = if_code.substr(if_code.find("<IF>")+4);
    }
    if (then_code.find("</THEN>") != std::string::npos) {
      then_code = then_code.substr(0, then_code.find("</THEN>"));
    }

    // Process pre_match and post_match strings if they exist
    if (pre_match != "") { analyse_code(text, pre_match, x,y,z); }


    if (analyse_code(text, if_code, x,y,z) > -1) { 
      analyse_code(text, then_code, x,y,z);
    }

   if (post_match != "") { analyse_code(text, post_match, x,y,z); }

    return 1;
  }
  // Getting here implies no conditional execution, so process directly
  else {

    /* Our return value will depend on whether boolean values hold and
     * also whether the individual XML commands are effective. If there
     * are any problems we return -1. This behavior allows us to use
     * analyse_code as a test function for processing IF/THEN commands
     * in the code above. */
     // handle parentheses
     if (c.find("(") != std::string::npos) {

	std::string pre_match = "";
	std::string our_match = "";
	std::string post_match = "";

	size_t open_pos = c.find("(");
	size_t close_pos = c.find(")");

	while (open_pos != std::string::npos && close_pos != std::string::npos) {

	  std::string temp = c.substr(open_pos+1, close_pos-open_pos-1);
	  if (are_parens_balanced(temp) == 1) {
	    // Parentheses Exist, We Grab our Three Elements
	    pre_match = c.substr(0, open_pos);
	    our_match = temp;
	    post_match = c.substr(close_pos+1);


	    std::string post_boolean = return_opening_boolean(post_match);
	    std::string our_boolean = return_closing_boolean(pre_match);

	    if (our_boolean != "") { 
		if (pre_match.length() >= our_boolean.length()) {
			if (pre_match.substr(pre_match.length()-our_boolean.length()) == our_boolean) {
				pre_match = pre_match.substr(0, pre_match.length()-our_boolean.length());
			}
		}
	    }
	    if (post_boolean != "") { 
		if (post_match.length() >= post_boolean.length()) {
			if (post_match.substr(0, post_boolean.length()) == post_boolean) {
				post_match = post_match.substr(post_boolean.length());
			}
		}
	    }


	    int respre = analyse_code(text, pre_match, x,y,z);
	    int resout = analyse_code(text, our_match, x,y,z);
	    int respst = analyse_code(text, post_match, x,y,z);



	    if (pre_match != "") {
	    if (our_boolean != "") {
	        if (our_boolean == " AND ") { if (respre == -1 || resout == -1) { return -1; } }
	        if (our_boolean == " OR ") { if (respre == -1 && resout == -1) { return -1; } }
	        if (our_boolean == " NOT ") { if (respre == -1 || resout > -1) { return -1; } }
		if (post_match != "") {
	        	if (post_boolean == " AND ") { if (respst <= -1) { return -1; } }
	        	if (post_boolean == " NOT ") { if (respre >= -1) { return -1; } }
		}
	        return 1;
	      } 
            } else {
            if (post_match != "") {
            if (post_boolean != "") {
	      if (post_boolean == " AND ") { if (respst == -1 || resout == -1) { return -1; } }
	      if (post_boolean == " OR ") { if (respst == -1 && resout == -1) { return -1; } }
	      if (post_boolean == " NOT ") { if (respst > -1 || resout == -1) { return -1; } }
	      return 1;
	    }
            } else {
              return resout;
            }
            }
	    return 1;
	  }
	  else {
	    // Parentheses do not balance
	    close_pos = c.find(")", close_pos+1);
	  }
	}
     } // handle parentheses
     else {
       /* There are no parenthese in the text, so we handle any boolean
	* commands. Returning -1 if the boolean logic does not hold and
	* 1 if the boolean logic does hold. This lets us use the return 
	* value from this function to test whether to run conditional 
	* code higher up in the section processing IF/THEN commands. */
	// Handle the Boolean And

	if (c.find(" | ") != std::string::npos) {
	  std::string  pre_and = c.substr(0, c.find(" | "));
	  std::string  pst_and = c.substr(c.find(" | ")+3);
          int respst = analyse_code(text, pst_and, x,y,z);
	  if (respst > -1) {
	    if (text->elements->at(x)->size() > respst) {
  	      try {
		text->elements->at(x)->at(respst)->at(0)->run_extra_code(text,pre_and.c_str(),x,respst,0);
      	      } catch (...) {} 
            }
          }
	  return 1;
	} else {
	if (c.find(" AND ") != std::string::npos) {
	  std::string  pre_and = c.substr(0, c.find(" AND "));
	  std::string  pst_and = c.substr(c.find(" AND ")+5);
	  int respre = analyse_code(text, pre_and, x,y,z);
	  int respst = analyse_code(text, pst_and, x,y,z);
	  if ((respre == -1 && pre_and != "") || (respst == -1 && pst_and != "")) { return -1; }
	  return 1;
	} else {
	  // Handle the Boolean Or
	  if (c.find(" OR ") != std::string::npos) {
	    std::string pre_not = c.substr(0, c.find(" OR "));
	    std::string pst_not = c.substr(c.find(" OR ")+4);
	    int respre = analyse_code(text, pre_not, x,y,z);
	    int respst = analyse_code(text, pst_not, x,y,z);
	    if (respre == -1 && respst == -1) { return -1; }
	    return 1;
	  } else {
	    // Handle the Boolean NOT
	    if (c.find(" NOT ") != std::string::npos) {
		std::string pre_not = c.substr(0, c.find(" NOT "));
		std::string pst_not = c.substr(c.find(" NOT ")+5);
	  	int respre = analyse_code(text, pre_not, x,y,z);
	  	int respst = analyse_code(text, pst_not, x,y,z);
	    	if (respst > -1 || respre == -1) { return -1; }
		return 1;
	    } else {
/*
		// Nothing Boolean Here, Just Process it as Straight XML
		if (c.find("><") != std::string::npos) {
			int rv = -1;
			while (c.find("><") != std::string::npos) {
				rv = process_code(text, c.substr(0,c.find("><")+1),x,y,z);
				c = c.substr(c.find("><")+1);
			}
			rv = process_code(text, c,x,y,z);
			return rv;
		} else {
*/
			return process_code(text, c, x,y,z);
//		}
		
	    }
	  }
	}
        } // found a pipe
     }
     // Process NON-BOOLEAN, NON-PARENTHETICAL XML Code

     return process_code(text, c, x,y,z);
  }
  // we should never get here, so return -1, if we do.
  return -1;
}

int Code::are_parens_balanced(std::string x) {
  int balance = 0;
  for (unsigned int i = 0; i < x.length(); i++) {
    if (x[i] == '(') { balance++; }
    if (x[i] == ')') { balance--; }
  }
  if (balance == 0) { return 1; }
  return -1;
}
void Code::tokenize(std::string x) {
  std::stringstream ss;
  std::string buf;
  ss << x;
  tokens->clear();
  while (ss>>buf) {tokens->push_back(buf);}
  return;
}
std::string Code::return_closing_boolean(std::string x) {
  if (x.length() > 5) { if (x.substr(x.length()-5, 5) == " AND ") { return " AND "; } }
  if (x.length() > 5) { if (x.substr(x.length()-5, 5) == " NOT ") { return " NOT "; } }
  if (x.length() > 4) { if (x.substr(x.length()-4, 4) == " OR ") { return " OR "; } }
  if (x.length() > 3) { if (x.substr(x.length()-3, 3) == " | ") { return " | "; } }
  return " AND "; // default
}
std::string Code::return_opening_boolean(std::string x) {
  if (x.length() > 5) { if (x.substr(0, 5) == " AND ") { return " AND "; } }
  if (x.length() > 5) { if (x.substr(0, 5) == " NOT ") { return " NOT "; } }
  if (x.length() > 4) { if (x.substr(0, 4) == " OR ") { return " OR "; } }
  if (x.length() > 3) { if (x.substr(0, 3) == " | ") { return " | "; } }
  return " AND "; // default
}












int Code::process_code(Text *text, std::string c, int x, int y, int z) {

  if (c == "") { return -1; }

  int rv = -1; // return value

  try {
    if (c.find("<POSSESSIVE") != std::string::npos) { rv = possessive(text, c, x,y,z); if (rv == -1) { return -1; } }
    if (c.find("<DEFINE_COMPOUND") != std::string::npos) { rv = define_compound(text, c, x,y,z); if (rv == -1) { return -1; } }
    // These have the potential to delete units, and return -2 if deletion occurs
    if (c.find("<DELETE") != std::string::npos) { rv = delete_entry(text, c, x,y,z); if (rv > -1) { return -2; } }
    if (c.find("<MAKE_ONLY") != std::string::npos) { rv = make_only_entry(text, c, x,y,z); if (rv > -1) { return -2; } }
    if (c.find("<RESEGMENT") != std::string::npos) { rv = resegment(text, c, x,y,z); if (rv > -1) { return -2; } }
    if (c.find("<TRANSFORM_01 ") != std::string::npos) { rv = transform_01(text, c, x,y,z); if (rv > -1) { return -2; } }
    if (c.find("<TENSE ") != std::string::npos) { rv = tense(text, c, x,y,z); if (rv > -1) { return -2; } }
    if (c.find("<REDUCE") != std::string::npos) { rv = reduce(text, c, x,y,z); if (rv > -1) { return -2; } }
    if (c.find("<SMT") != std::string::npos) { rv = statistical_machine_translation(text, c, x,y,z); if (rv > -1) { return -2; } }

    // These won't delete anything
    if (c.find("<POSTTEXT") != std::string::npos) { rv = add_post_text(text, c, x,y,z); if (rv == -1) { return -1; } }
    if (c.find("<PRETEXT") != std::string::npos) { rv = add_pre_text(text, c, x,y,z); if (rv == -1) { return -1; } }
    if (c.find("<PRINT") != std::string::npos) { rv = print(text, c, x,y,z); if (rv == -1) { return -1; } }
    if (c.find("<CLASS ") != std::string::npos) { rv = is_class(text, c, x,y,z); if (rv == -1) { return -1; } }
    if (c.find("<CLASS2 ") != std::string::npos) { rv = is_class2(text, c, x,y,z); if (rv == -1) { return -1; } }
    if (c.find("<CHINESE ") != std::string::npos) { rv = is_chinese(text, c, x,y,z); if (rv == -1) { return -1; } }
    if (c.find("<CHINESE2 ") != std::string::npos) { rv = is_chinese2(text, c, x,y,z); if (rv == -1) { return -1; } }
    if (c.find("<NOTCHINESE ") != std::string::npos) { rv = not_chinese(text, c, x,y,z); if (rv == -1) { return -1; } }
    if (c.find("<NOTCLASS ") != std::string::npos) { rv = not_class(text, c, x,y,z); if (rv == -1) { return -1; } }
    if (c.find("<NOTTRANSLATE") != std::string::npos) { rv = not_translate(text, c, x,y,z); if (rv == -1) { return -1; } }
    if (c.find("<TAG ") != std::string::npos) { rv = tag(text, c, x,y,z); if (rv == -1) { return -1; } }
    if (c.find("<SUBCLAUSE") != std::string::npos) { rv = subclause(text, c, x,y,z); if (rv == -1) { return -1; } }
    if (c.find("<BEGINNING") != std::string::npos) { rv = beginning(text, c, x,y,z); if (rv == -1) { return -1; } }
    if (c.find("<ENDING") != std::string::npos) { rv = ending(text, c, x,y,z); if (rv == -1) { return -1; } }
    if (c.find("<LASTWORDEXACT ") != std::string::npos) { rv = lastwordexact(text, c, x,y,z); if (rv == -1) { return -1; } }
    if (c.find("<LASTWORDLOOP ") != std::string::npos) { rv = lastwordloop(text, c, x,y,z); if (rv == -1) { return -1; } }
    if (c.find("<LASTWORD ") != std::string::npos) { rv = lastword(text, c, x,y,z); if (rv == -1) { return -1; } }
    if (c.find("<LASTLOOP ") != std::string::npos) { rv = lastloop(text, c, x,y,z); if (rv == -1) { return -1; } }
    if (c.find("<LAST ") != std::string::npos) { rv =last(text, c, x,y,z); if (rv == -1) { return -1; } }
    if (c.find("<NEXTWORDEXACT ") != std::string::npos) { rv = nextwordexact(text, c, x,y,z); if (rv == -1) { return -1; } }
    if (c.find("<NEXTWORDLOOP ") != std::string::npos) { rv = nextwordloop(text, c, x,y,z); if (rv == -1) { return -1; } }
    if (c.find("<NEXTWORD ") != std::string::npos) { rv = nextword(text, c, x,y,z); if (rv == -1) { return -1; } }
    if (c.find("<NEXTLOOP ") != std::string::npos) { rv = nextloop(text, c, x,y,z); if (rv == -1) { return -1; } }
    if (c.find("<NEXT ") != std::string::npos) { rv =next(text, c, x,y,z); if (rv == -1) { return -1; } }
    if (c.find("<CONTAINS ") != std::string::npos) { rv = contains(text, c, x,y,z); if (rv == -1) { return -1; } }
    if (c.find("<MATCH ") != std::string::npos) { rv = match(text, c, x,y,z); if (rv == -1) { return -1; } }
    if (c.find("<TEXTMATCH ") != std::string::npos) { rv = textmatch(text, c, x,y,z); if (rv == -1) { return -1; } }
    if (c.find("<BONUS ") != std::string::npos) { rv = bonus(text, c, x,y,z); if (rv == -1) { return -1; } }
    if (c.find("<BONUS2 ") != std::string::npos) { rv = bonus2(text, c, x,y,z); if (rv == -1) { return -1; } }
    if (c.find("<COMPOUND ") != std::string::npos) { rv = is_compound(text, c, x,y,z); if (rv == -1) { return -1; } }
    if (c.find("<COMPOUND2 ") != std::string::npos) { rv = is_compound2(text, c, x,y,z); if (rv == -1) { return -1; } }
    if (c.find("<NOTCOMPOUND ") != std::string::npos) { rv = not_compound(text, c, x,y,z); if (rv == -1) { return -1; } }
    if (c.find("<COMPOUND_BONUS ") != std::string::npos) { rv = compound_bonus(text, c, x,y,z); if (rv == -1) { return -1; } }
    if (c.find("<COMPOUND_BONUS2 ") != std::string::npos) { rv = compound_bonus2(text, c, x,y,z); if (rv == -1) { return -1; } }
    if (c.find("<COMPOUND_EXECUTE ") != std::string::npos) { rv = compound_execute(text, c, x,y,z); if (rv == -1) { return -1; } }
    if (c.find("<COMPOUND_CHAIN_EXECUTE") != std::string::npos) { rv = compound_chain_execute(text, c, x,y,z); if (rv == -1) { return -1; } }
    if (c.find("<COMPOUND_LENGTH ") != std::string::npos) { rv = compound_length(text,c,x,y,z); if (rv == -1) { return -1; } }
    if (c.find("<COMPOUND_LENGTH2 ") != std::string::npos) { rv = compound_length2(text,c,x,y,z); if (rv == -1) { return -1; } }
    if (c.find("<BOOST ") != std::string::npos) { rv = boost(text, c, x,y,z); if (rv == -1) { return -1; } }
    if (c.find("<LENGTH ") != std::string::npos) { rv = length(text, c, x,y,z); if (rv == -1) { return -1; } }
    if (c.find("<NUMBER ") != std::string::npos) { rv = is_number(text, c, x,y,z); if (rv == -1) { return -1; } }
    if (c.find("<INSERT ") != std::string::npos) { rv = insert(text, c, x,y,z); if (rv == -1) { return -1; } }
    if (c.find("<SET ") != std::string::npos) { rv = set(text, c, x,y,z); if (rv == -1) { return -1; } }
    if (c.find("<PLURALIZE") != std::string::npos) { rv = pluralize(text, c, x,y,z); if (rv == -1) { return -1; } }
    if (c.find("<PLURALNEXT") != std::string::npos) { rv = plural_next(text, c, x,y,z); if (rv == -1) { return -1; } }
    if (c.find("<SWITCH ") != std::string::npos) { rv = switch_units(text, c, x,y,z); if (rv == -1) { return -1; } }
  }
  catch (...) {
    throw "malformed code submitted for code analysis: " + c;
  }
  return rv;
}

int Code::statistical_machine_translation(Text *y, std::string h, int a, int b, int c) {
  // SMT lookups and integration
  return -1;
}
int Code::print(Text *y, std::string h, int a, int b, int c) {

	std::string header = "";
	std::string toprint = "";

	while (h.find("<PRINT ") != std::string::npos) {
		header = h.substr(    h.find("<PRINT ")+1,     h.find(">",     h.find("<PRINT "))-h.find("<PRINT ")-1     );
		toprint = header.substr(h.find("<PRINT ")+6);
		h = h.substr(h.find(header)+header.length()+1);
		int pd = 0;
		if (toprint == "chinese") { std::cout << y->elements->at(a)->at(b)->at(c)->return_chinese(); pd = 1;}
		if (toprint == "chinese_utf8s") { std::cout << y->elements->at(a)->at(b)->at(c)->return_chinese_utf8s(); pd = 1; }
		if (toprint == "chinese_utf8c") { std::cout << y->elements->at(a)->at(b)->at(c)->return_chinese_utf8c(); pd = 1; }
		if (toprint == "english") { std::cout << y->elements->at(a)->at(b)->at(c)->return_english_no_spacing(); pd = 1; }
		if (toprint == "pinyin") { std::cout << y->elements->at(a)->at(b)->at(c)->return_pinyin_no_spacing(); pd = 1; }
		if (toprint == "myclass") { std::cout << y->elements->at(a)->at(b)->at(c)->myclass; pd = 1; }
		if (toprint == "integer") { std::cout << y->elements->at(a)->at(b)->at(c)->integer_representation << std::endl; pd = 1; }
		if (toprint == "decimal") { std::cout << y->elements->at(a)->at(b)->at(c)->decimal_representation << std::endl; pd = 1; }
		if (toprint == "number") { 
			if (y->elements->at(a)->at(b)->at(c)->decimal_representation != 0) {
				std::cout << y->elements->at(a)->at(b)->at(c)->decimal_representation;
			} else {
				std::cout << y->elements->at(a)->at(b)->at(c)->integer_representation;
			} 
			pd = 1;
		}
		if (toprint == "newline") { std::cout << std::endl; pd = 1; }
		if (toprint == "tab") { std::cout << "\t"; pd = 1; }
		if (pd == 0) { std::cout << toprint; }
	}
	return 1;
}
int Code::is_class(Text *y, std::string h, int a, int b, int c) {

	std::string header = "";
	std::string classtotest = "";
	std::string distance = "";
	int location = b;

	while (h.find("<CLASS ") != std::string::npos) {

		header = h.substr(    h.find("<CLASS ")+1,     h.find(">",     h.find("<CLASS "))-h.find("<CLASS ")-1     );
		h = h.substr(h.find(header)+header.length()+1);

		location = b;

		tokenize(header);
		if (tokens->size() == 2) {
		  	classtotest = tokens->at(1);
		} else {
			if (tokens->size() == 3) {
		  		location += atoi(tokens->at(1).c_str());
		  		classtotest = tokens->at(2);
			} else { return -1; }
		}
		if (classtotest == "") { return -1; }


		// Check that this Class Exists
		if (y->is_category(classtotest, a, location) == 1) {
			return location;
		} 
	}
	return -1;
}
int Code::is_class2(Text *y, std::string h, int a, int b, int c) {

	std::string header = "";
	std::string classtotest = "";
	std::string distance = "";
	int location = 0;

	while (h.find("<CLASS2 ") != std::string::npos) {

		header = h.substr(    h.find("<CLASS2 ")+1,     h.find(">",     h.find("<CLASS2 "))-h.find("<CLASS2 ")-1     );
		h = h.substr(h.find(header)+header.length()+1);

		tokenize(header);
		if (tokens->size() == 3) {
		  	location = atoi(tokens->at(1).c_str());
		  	classtotest = tokens->at(2);
		} else {
			if (tokens->size() == 4) {
		  		location += atoi(tokens->at(1).c_str());
		  		location += atoi(tokens->at(2).c_str());
		  		classtotest = tokens->at(3);
			} else { return -1; }
		}
		if (classtotest == "") { return -1; }


		// Check that this Class Exists
		if (y->is_category(classtotest, a, b+location) == 1) {
			return location;
		} 
	}
	return -1;
}
int Code::not_class(Text *y, std::string h, int a, int b, int c) {

	std::string header = "";
	std::string classtotest= "";
	int location = b;

	while (h.find("<NOTCLASS ") != std::string::npos) {

		header = h.substr(    h.find("<NOTCLASS ")+1,     h.find(">",     h.find("<NOTCLASS "))-h.find("<NOTCLASS ")-1     );
		h = h.substr(h.find(header)+header.length()+1);

		location = b;

		tokenize(header);
		if (tokens->size() == 2) {
		  	classtotest = tokens->at(1);
		} else {
			if (tokens->size() == 3) {
		  		location += atoi(tokens->at(1).c_str());
		  		classtotest = tokens->at(2);
			} else { return -1; }
		}

		// Check that this Class Exists
		if (y->is_category(classtotest, a, location) == 1) {
			return -1;
		} 
	}
	return location;
}
int Code::tag(Text *y, std::string h, int a, int b, int c) {

	std::string header = "";
	std::string tag= "";
	int location = b;

	while (h.find("<TAG ") != std::string::npos) {
		
		location = b;

		header = h.substr(    h.find("<TAG ")+1,     h.find(">",     h.find("<TAG "))-h.find("<TAG ")-1     );
		h = h.substr(h.find(header)+header.length()+1);

		tokenize(header);
		if (tokens->size() == 2) { 
			tag = tokens->at(1);
		} else {
			if (tokens->size() == 3) {
				tag = tokens->at(2);
				location += atoi(tokens->at(1).c_str());				
			} else {return -1;}
		}
		if (tag == "") { return -1; }

		// Add the Tag
		if (location == b) {
			y->elements->at(a)->at(location)->at(c)->myclass += ":" + tag;
		} else {
			for (int i = 0; i < y->elements->at(a)->at(location)->size(); i++) {
				y->elements->at(a)->at(location)->at(i)->myclass += ":" + tag;
			}
		}
	}
	return location;
}
int Code::subclause(Text *y, std::string h, int a, int b, int c) {

	std::string header = "";
	std::string category = "";
	std::string benefit = "";

	while (h.find("<SUBCLAUSE ") != std::string::npos) {
		header = h.substr(    h.find("<SUBCLAUSE ")+1,     h.find(">",     h.find("<SUBCLAUSE "))-h.find("<SUBCLAUSE ")-1     );
		h = h.substr(h.find(header)+header.length()+1);

		tokenize(header);
		if (tokens->size() != 2 && tokens->size() != 3) { return -1; }
		if (tokens->size() == 2) {
			category = "me";
			benefit = tokens->at(1);
		} else {
			category = tokens->at(1);
			benefit = tokens->at(2);
		}

		// Figure out if we are in a subclause
		if (beginning(y,h,a,b,c) == 1) { return -1; }
		if (y->sentence_backward_category_match("Comma", a, b) != -1) { return 1; }
		if (y->sentence_forward_category_match("Comma", a, b) != -1) { return 1; }
	}
	return b;
}
int Code::define_compound(Text *y, std::string h, int a, int b, int c) {

	std::string header = "";
	std::string body = "";
	std::string closer = "";

	int success = -1;

	while (h.find("<DEFINE_COMPOUND ") != std::string::npos) {
		header = h.substr(    h.find("<DEFINE_COMPOUND ")+1,     h.find(">",     h.find("<DEFINE_COMPOUND "))-h.find("<DEFINE_COMPOUND ")-1     );
		h = h.substr(h.find(header)+header.length()+1);

		body = h.substr(0,h.find("</DEFINE_COMPOUND"));
		h = h.substr(h.find(body)+body.length());

		closer = h.substr(0, h.find(">"));
		h = h.substr(h.find(closer)+closer.length()+1);

		std::string remainder = h;
		std::string compound_name = "Unit";

		tokenize(header);
		if (tokens->size() == 2) { compound_name = tokens->at(1); }

		// Check to see if this has already been added
                for (int i = 0; i < compounds->size(); i++) {
			if (compounds->at(i) == compound_name) {
				if (compound_xml->at(i) == body) { return -1; }
			}
                }
		compounds->push_back(compound_name);
		compound_xml->push_back(body);
		compound_xml_action->push_back(remainder);
	}
	if (success > -1) { return success; }
  return 1;
}
int Code::is_compound(Text *y, std::string h, int a, int b, int c) {

	std::string header = "";
	std::string compoundtotest = "";
	int location = b;
	int success = -1;

	while (h.find("<COMPOUND ") != std::string::npos) {

		header = h.substr(    h.find("<COMPOUND ")+1,     h.find(">",     h.find("<COMPOUND "))-h.find("<COMPOUND ")-1     );
		h = h.substr(h.find(header)+header.length()+1);

		tokenize(header);
		if (tokens->size() == 2) {
		  	compoundtotest = tokens->at(1);
			location = 0;
		} else {
			if (tokens->size() == 3) {
		  		location = atoi(tokens->at(1).c_str());
		  		compoundtotest = tokens->at(2);
			} else { return -1; }
		}
		if (compoundtotest == "") { return -1; }


		// Check that this Class Exists
		for (int z = 0; z < compounds->size(); z++) {
			if (compounds->at(z) == compoundtotest) {
				// Analyse the XML
try {

				if (location < 0 || location > y->elements->at(a)->size()) { return -1; }
				success = analyse_code(y,compound_xml->at(z),a,b+location,0);
				if (success != -1) { return location; }
				} catch (...) { 
					std::cout << "Error: " << "trying: " << compound_xml->at(z) << " at " << y->elements->at(a)->at(location)->at(0)->return_chinese() << std::endl;
				}
			}
		}
	}
	if (success != -1) { return success; }
	return -1;
}
int Code::is_compound2(Text *y, std::string h, int a, int b, int c) {

	std::string header = "";
	std::string compoundtotest = "";
	int location = 0;
	int success = -1;

	while (h.find("<COMPOUND2 ") != std::string::npos) {


		header = h.substr(    h.find("<COMPOUND2 ")+1,     h.find(">",     h.find("<COMPOUND2 "))-h.find("<COMPOUND2 ")-1     );
		h = h.substr(h.find(header)+header.length()+1);

		tokenize(header);
		if (tokens->size() == 3) {
		  	compoundtotest = tokens->at(2);
			location = atoi(tokens->at(1).c_str());
		} else {
			if (tokens->size() == 4) {
				location = atoi(tokens->at(1).c_str());
				location += atoi(tokens->at(2).c_str());
		  		compoundtotest = tokens->at(3);
			} else { return -1; }
		}
		if (compoundtotest == "") { return -1; }


		// Check that this Class Exists
		for (int z = 0; z < compounds->size(); z++) {
			if (compounds->at(z) == compoundtotest) {
				// Analyse the XML
try {

				if (b+location < 0 || b+location > y->elements->at(a)->size()) { return -1; }

				std::string new_xml = "<COMPOUND 0 " + compoundtotest + ">";
				success = analyse_code(y,new_xml,a,b+location,0);
				if (success != -1) { return b+location; }
				} catch (...) { 
					std::cout << "Error: " << "trying: " << compound_xml->at(z) << " at " << y->elements->at(a)->at(location)->at(0)->return_chinese() << std::endl;
				}
			}
		}
	}
	if (success != -1) { return success; }
	return -1;
}
int Code::not_compound(Text *y, std::string h, int a, int b, int c) {

	std::string header = "";
	std::string compoundtotest = "";
	int location = b;
	int success = -1;

	while (h.find("<NOTCOMPOUND ") != std::string::npos) {

		header = h.substr(    h.find("<NOTCOMPOUND ")+1,     h.find(">",     h.find("<NOTCOMPOUND "))-h.find("<NOTCOMPOUND ")-1     );
		h = h.substr(h.find(header)+header.length()+1);

		location = b;

		tokenize(header);
		if (tokens->size() == 2) {
		  	compoundtotest = tokens->at(1);
		} else {
			if (tokens->size() == 3) {
		  		location += atoi(tokens->at(1).c_str());
		  		compoundtotest = tokens->at(2);
			} else { return -1; }
		}
		if (compoundtotest == "") { return -1; }


		// Check that this Class Exists
		for (int z = 0; z < compounds->size(); z++) {
			if (compounds->at(z).find(compoundtotest) != std::string::npos) {
				// Analyse the XML
				success = analyse_code(y,compound_xml->at(z),a,location,0);
				if (success != -1) { return -1; }
			}
		}
	}
	return location;
}
int Code::is_chinese2(Text *y, std::string h, int a, int b, int c) {

	std::string header = "";
	std::string classtotest = "";
	std::string distance = "";
	int location = 0;

	while (h.find("<CHINESE2 ") != std::string::npos) {

		location = 0;

		header = h.substr(    h.find("<CHINESE2 ")+1,     h.find(">",     h.find("<CHINESE2 "))-h.find("<CHINESE2 ")-1     );
		h = h.substr(h.find(header)+header.length()+1);

		location = b;

		tokenize(header);
		if (tokens->size() == 3) {
		  	location += atoi(tokens->at(1).c_str());
		  	classtotest = tokens->at(2);
		} else {
			if (tokens->size() == 4) {
		  		location+=atoi(tokens->at(1).c_str());
		  		location+=atoi(tokens->at(2).c_str());
		  		classtotest = tokens->at(3);
			} else { return -1; }
		}
		if (classtotest == "") { return -1; }

		// Check that this Chinese Exists
		if (y->return_chinese(a, b+location) == classtotest) {
			return location;
		} 
	}
	return -1;
}
int Code::is_chinese(Text *y, std::string h, int a, int b, int c) {

	std::string header = "";
	std::string classtotest = "";
	std::string distance = "";
	int location = b;

	while (h.find("<CHINESE ") != std::string::npos) {

		header = h.substr(    h.find("<CHINESE ")+1,     h.find(">",     h.find("<CHINESE "))-h.find("<CHINESE ")-1     );
		h = h.substr(h.find(header)+header.length()+1);

		location = b;

		tokenize(header);
		if (tokens->size() == 2) {
		  	classtotest = tokens->at(1);
		} else {
			if (tokens->size() == 3) {
		  		location += atoi(tokens->at(1).c_str());
		  		classtotest = tokens->at(2);
			} else { return -1; }
		}
		if (classtotest == "") { return -1; }

		// Check that this Chinese Exists
		if (y->return_chinese(a, location) == classtotest) {
			return location;
		} 
	}
	return -1;
}
int Code::not_chinese(Text *y, std::string h, int a, int b, int c) {

	std::string header = "";
	std::string classtotest= "";
	int location = b;

	while (h.find("<NOTCHINESE ") != std::string::npos) {

		location = b;

		header = h.substr(    h.find("<NOTCHINESE ")+1,     h.find(">",     h.find("<NOTCHINESE "))-h.find("<NOTCHINESE ")-1     );
		h = h.substr(h.find(header)+header.length()+1);

		tokenize(header);
		if (tokens->size() == 2) {
		  	classtotest = tokens->at(1);
		} else {
			if (tokens->size() == 3) {
		  		location += atoi(tokens->at(1).c_str());
		  		classtotest = tokens->at(2);
			} else { return -1; }
		}

		// Check that this Class Exists
		if (y->return_chinese(a, location) == classtotest) {
			return -1;
		} 
	}
	return location;
}
int Code::beginning(Text *y, std::string h, int a, int b, int c) {

	std::string header = "";
	std::string category = "";
	std::string benefit = "";

	int success = 0;

	while (h.find("<BEGINNING ") != std::string::npos) {
		header = h.substr(    h.find("<BEGINNING ")+1,     h.find(">",     h.find("<BEGINNING "))-h.find("<BEGINNING ")-1     );
		h = h.substr(h.find(header)+header.length()+1);


		tokenize(header);
		if (tokens->size() != 2 && tokens->size() != 3) { return -1; }
		if (tokens->size() == 2) {
			category = "me";
			benefit = tokens->at(1);
		} else {
			category = tokens->at(1);
			benefit = tokens->at(2);
		}

		// Add the Tag

		if (y->is_category("Terminal",a,b-1) == 1 || b == 0) {
			if (category == "me") { y->add_confidence(category, atof(benefit.c_str()),a,b,c); success = 1;}
			else { y->add_confidence(category, atof(benefit.c_str()), a, b); success = 1;}
		}
	}
        if (success == 1) { return b; }
	return -1;
}
int Code::ending(Text *y, std::string h, int a, int b, int c) {

	std::string header = "";
	std::string category = "";
	std::string benefit = "";

	while (h.find("<ENDING ") != std::string::npos) {
		header = h.substr(    h.find("<ENDING ")+1,     h.find(">",     h.find("<ENDING "))-h.find("<ENDING ")-1     );
		h = h.substr(h.find(header)+header.length()+1);

		tokenize(header);
		if (tokens->size() != 2 && tokens->size() != 3) { return -1; }
		if (tokens->size() == 2) {
			category = "me";
			benefit = tokens->at(1);
		} else {
			category = tokens->at(1);
			benefit = tokens->at(2);
		}

		// Add the Tag
		if (y->is_category("Terminal",a,b+1) == 1) {
			if (category == "me") { y->elements->at(a)->at(b)->at(c)->confidence += atof(benefit.c_str()); }
			else { y->add_confidence(category, atof(benefit.c_str()), a, b); }
			return b;
		} else {
			if (y->elements->at(a)->size() == b+1) { 
				if (category == "me") { y->elements->at(a)->at(b)->at(c)->confidence += atof(benefit.c_str()); }
				else { y->add_confidence(category, atof(benefit.c_str()), a, b); }
				return b;
			}
		}
	}
	return -1;
}
int Code::add_post_text(Text *y, std::string h, int a, int b, int c) {

	std::string header = "";
	std::string closer = "";
	std::string body = "";

	int location = b;
	std::string category = "me";

	int success = 0;

	std::vector<std::string> categories;

	while (h.find("<POSTTEXT") != std::string::npos) {

		location = b;
		category = "me";

		header = h.substr(    h.find("<POSTTEXT")+1,     h.find(">",     h.find("<POSTTEXT"))-h.find("<POSTTEXT")-1     );
		h = h.substr(h.find(header)+header.length()+1);

		body = h.substr(0,h.find("<"));
		h = h.substr(h.find(body)+body.length());

		closer = h.substr(0, h.find(">"));
		h = h.substr(h.find(closer)+closer.length()+1);

		tokenize(header);
		if (tokens->size() == 2) {
			category = tokens->at(1);
			location = b;
		} else {
			if (tokens->size() == 3) {
				category = tokens->at(1);
				location += atoi(tokens->at(2).c_str());
			}
		}


		// Add Confidence 
		if (category == "all") {
			if (y->elements->at(a)->size() > location+1 && location >= 0) {
				for (int i = 0; i < y->elements->at(a)->at(location)->size(); i++) {
					y->elements->at(a)->at(location)->at(i)->add_post_english(body);
				}
			}
		} else {
			if (category == "me") { 
				if (y->elements->at(a)->size() > location+1 && location >= 0) {
					for (int i = 0; i < y->elements->at(a)->at(location)->size(); i++) {
						if (y->elements->at(a)->at(location)->at(i)->myclass.find(y->elements->at(a)->at(b)->at(c)->myclass) != std::string::npos) {
							y->elements->at(a)->at(location)->at(i)->add_post_english(body);
						}
					}
				}
			} else {
				if (y->elements->at(a)->size() > location+1 && location >= 0) {
					for (int i = 0; i < y->elements->at(a)->at(location)->size(); i++) {
						if (y->is_category(category, a, location) == 1) {
							y->elements->at(a)->at(location)->at(i)->add_post_english(body);
						}
					}
				}
			}
		}
	}
	return location;
}
int Code::add_pre_text(Text *y, std::string h, int a, int b, int c) {

	std::string header = "";
	std::string closer = "";
	std::string body = "";

	int location = b;
	std::string category = "me";

	int success = 0;

	std::vector<std::string> categories;

	while (h.find("<PRETEXT") != std::string::npos) {

		location = b;
		category = "me";

		header = h.substr(    h.find("<PRETEXT")+1,     h.find(">",     h.find("<PRETEXT"))-h.find("<PRETEXT")-1     );
		h = h.substr(h.find(header)+header.length()+1);

		body = h.substr(0,h.find("<"));
		h = h.substr(h.find(body)+body.length());

		closer = h.substr(0, h.find(">"));
		h = h.substr(h.find(closer)+closer.length()+1);

		tokenize(header);
		if (tokens->size() == 2) {
			category = tokens->at(1);
			location = b;
		} else {
			if (tokens->size() == 3) {
				category = tokens->at(1);
				location += atoi(tokens->at(2).c_str());
			}
		}

		// Add Confidence 
		if (category == "all") {
			if (y->elements->at(a)->size() > location+1 && location >= 0) {
				for (int i = 0; i < y->elements->at(a)->at(location)->size(); i++) {
					y->elements->at(a)->at(location)->at(i)->add_pre_english(body);
				}
			}
		} else {
			if (category == "me") { 
				if (y->elements->at(a)->size() > location+1 && location >= 0) {
					for (int i = 0; i < y->elements->at(a)->at(location)->size(); i++) {
						if (y->elements->at(a)->at(location)->at(i)->myclass.find(y->elements->at(a)->at(b)->at(c)->myclass) != std::string::npos) {

							y->elements->at(a)->at(location)->at(i)->add_pre_english(body);	
					}
					}
				}
			} else {
				if (y->elements->at(a)->size() > location+1 && location >= 0) {
					for (int i = 0; i < y->elements->at(a)->at(location)->size(); i++) {
						if (y->is_category(category, a, location) == 1) {
							y->elements->at(a)->at(location)->at(i)->add_pre_english(body);
						}
					}
				}
			}
		}
	}
	return location;
}
int Code::next(Text *y, std::string h, int a, int b, int c) {

	std::string header = "";
	std::string closer = "";
	std::string body = "";

	std::string category = "";
	std::string distance = "";
	std::string benefit = "";

	int success = -1;

	std::vector<std::string> categories;

	while (h.find("<NEXT ") != std::string::npos) {
		header = h.substr(    h.find("<NEXT ")+1,     h.find(">",     h.find("<NEXT "))-h.find("<NEXT ")-1     );
		h = h.substr(h.find(header)+header.length()+1);

		body = h.substr(0,h.find("<"));
		h = h.substr(h.find(body)+body.length());

		closer = h.substr(0, h.find(">"));
		h = h.substr(h.find(closer)+closer.length()+1);

		tokenize(header);
		if (tokens->size() < 3 || tokens->size() > 4) { return -1; }
		if (tokens->size() == 3) {
			category = tokens->at(1);
			distance = "1";
			benefit = tokens->at(2);
		} else {
			category = tokens->at(1);
			distance = tokens->at(2);
			benefit = tokens->at(3);
		}
		tokenize(body);
		categories = (*tokens);

		// Add Confidence 
		int location = b+atoi(distance.c_str());
		for (int i = 0; i < categories.size(); i++) {
			if (y->is_category(categories.at(i), a, location) == 1) {

				if (category == "me") { 
					y->elements->at(a)->at(b)->at(c)->confidence += atof(benefit.c_str());
				} else {
					y->add_confidence(category, atof(benefit.c_str()), a, b);
				}
				success = location;

			}
		}
	}
	if (success > -1) { return success; }
	return -1;
}
int Code::nextloop(Text *y, std::string h, int a, int b, int c) {

	std::string header = "";
	std::string closer = "";
	std::string body = "";

	std::string category = "";
	std::string distance = "";
	std::string benefit = "";

	int success = -1;

	std::vector<std::string> categories;

	while (h.find("<NEXTLOOP ") != std::string::npos) {
		header = h.substr(    h.find("<NEXTLOOP ")+1,     h.find(">",     h.find("<NEXTLOOP "))-h.find("<NEXTLOOP ")-1     );
		h = h.substr(h.find(header)+header.length()+1);

		body = h.substr(0,h.find("<"));
		h = h.substr(h.find(body)+body.length());

		closer = h.substr(0, h.find(">"));
		h = h.substr(h.find(closer)+closer.length()+1);

		tokenize(header);
		if (tokens->size() < 3 || tokens->size() > 4) { return -1; }
		if (tokens->size() == 3) {
			category = tokens->at(1);
			distance = "1";
			benefit = tokens->at(2);
		} else {
			category = tokens->at(1);
			distance = tokens->at(2);
			benefit = tokens->at(3);
		}
		tokenize(body);
		categories = (*tokens);

		// Add Confidence 
		int location = 0;
		for (int i = 0; i < categories.size(); i++) {
			for (int z = 0; z < 14; z++) {
				location = b+atoi(distance.c_str()) + z;
				if (y->is_category_non_recursive("Terminal",a,location) == 1) {z =15;}
				if (y->is_category_non_recursive("Comma",a,location) == 1) {z =15;}
				if (y->is_category(categories.at(i),a,location) == 1) { 
					if (category == "me") { 
						y->elements->at(a)->at(b)->at(c)->confidence += atof(benefit.c_str());
					} else {
						y->add_confidence(category, atof(benefit.c_str()), a, b);
					}
					success = location;
				}
			}
		}
	}
	if (success > -1) { return success; }
	return -1;
}
int Code::last(Text *y, std::string h, int a, int b, int c) {

	std::string header = "";
	std::string closer = "";
	std::string body = "";

	std::string category = "";
	std::string distance = "";
	std::string benefit = "";

	int success = -1;

	std::vector<std::string> categories;

	while (h.find("<LAST ") != std::string::npos) {
		header = h.substr(    h.find("<LAST ")+1,     h.find(">",     h.find("<LAST "))-h.find("<LAST ")-1     );
		h = h.substr(h.find(header)+header.length()+1);

		body = h.substr(0,h.find("<"));
		h = h.substr(h.find(body)+body.length());

		closer = h.substr(0, h.find(">"));
		h = h.substr(h.find(closer)+closer.length()+1);

		tokenize(header);
		if (tokens->size() < 3 || tokens->size() > 4) { return -1; }
		if (tokens->size() == 3) {
			category = tokens->at(1);
			distance = "1";
			benefit = tokens->at(2);
		} else {
			category = tokens->at(1);
			distance = tokens->at(2);
			benefit = tokens->at(3);
		}
		tokenize(body);
		categories = (*tokens);

		// Add Confidence 
		int location = b-atoi(distance.c_str());
		for (int i = 0; i < categories.size(); i++) {
			if (y->is_category(categories.at(i), a, location) == 1) {
				if (category == "me") { 
					y->elements->at(a)->at(b)->at(c)->confidence += atof(benefit.c_str());
				} else {
					y->add_confidence(category, atof(benefit.c_str()), a, b);
				}
				success = location;
			}
		}
	}
	if (success > -1) { return success; }
	return -1;
}
int Code::lastloop(Text *y, std::string h, int a, int b, int c) {

	std::string header = "";
	std::string closer = "";
	std::string body = "";

	std::string category = "";
	std::string distance = "";
	std::string benefit = "";

	int success = -1;

	std::vector<std::string> categories;

	while (h.find("<LASTLOOP ") != std::string::npos) {
		header = h.substr(    h.find("<LASTLOOP ")+1,     h.find(">",     h.find("<LASTLOOP "))-h.find("<LASTLOOP ")-1     );
		h = h.substr(h.find(header)+header.length()+1);

		body = h.substr(0,h.find("<"));
		h = h.substr(h.find(body)+body.length());

		closer = h.substr(0, h.find(">"));
		h = h.substr(h.find(closer)+closer.length()+1);


		tokenize(header);
		if (tokens->size() < 3 || tokens->size() > 4) { return -1; }
		if (tokens->size() == 3) {
			category = tokens->at(1);
			distance = "1";
			benefit = tokens->at(2);
		} else {
			category = tokens->at(1);
			distance = tokens->at(2);
			benefit = tokens->at(3);
		}
		tokenize(body);
		categories = (*tokens);

		// Add Confidence 
		int location = 0;
		for (int i = 0; i < categories.size(); i++) {
			for (int z = 0; z < 20; z++) {
				location = b-atoi(distance.c_str())-z;
				if (y->is_category_non_recursive("Terminal",a,location) == 1) {z =20;}
				if (y->is_category_non_recursive("Comma",a,location) == 1) {z =20;}
				if (location >= 0) {
					if (y->is_category(categories.at(i),a,location) == 1) {
						if (category == "me") { 
							y->elements->at(a)->at(b)->at(c)->confidence += atof(benefit.c_str());
						} else {
							y->add_confidence(category, atof(benefit.c_str()), a, b);
						}
						success = location;
						return success;
						z+= 25;
					}
				}
			}
		}
	}
	if (success > -1) { return success; }
	return -1;
}



int Code::nextword(Text *y, std::string h, int a, int b, int c) {

	std::string header = "";
	std::string closer = "";
	std::string body = "";

	std::string category = "";
	std::string distance = "";
	std::string benefit = "";

	std::string nextword = "";

	int success = -1;

	std::vector<std::string> categories;


	while (h.find("<NEXTWORD ") != std::string::npos) {
		header = h.substr(    h.find("<NEXTWORD ")+1,     h.find(">",     h.find("<NEXTWORD "))-h.find("<NEXTWORD ")-1     );
		h = h.substr(h.find(header)+header.length()+1);

		body = h.substr(0,h.find("<"));
		h = h.substr(h.find(body)+body.length());

		closer = h.substr(0, h.find(">"));
		h = h.substr(h.find(closer)+closer.length()+1);

		tokenize(header);

		if (tokens->size() < 3 || tokens->size() > 4) { return -1; }
		if (tokens->size() == 3) {
			category = tokens->at(1);
			distance = "1";
			benefit = tokens->at(2);
		} else {
			if (tokens->size() == 4) {
				category = tokens->at(1);
				distance = tokens->at(2);
				benefit = tokens->at(3);
			} else { return -1; }
		}
		tokenize(body);
		categories = (*tokens);

		// Add Confidence 
		int location = b+atoi(distance.c_str());
		for (unsigned int i = 0; i < categories.size(); i++) {
			nextword = y->return_chinese(a, location);
			if (nextword.length() >= categories.at(i).length()) {
				if (nextword.find(categories.at(i)) == 0) {
					if (category == "me") { 
						y->elements->at(a)->at(b)->at(c)->confidence += atof(benefit.c_str());
					} else {
						y->add_confidence(category, atof(benefit.c_str()), a, b);
					}
					success = location;
					return success;
				}
			}
		}
	}
	if (success > -1) { return success; }
	return -1;
}
int Code::nextwordexact(Text *y, std::string h, int a, int b, int c) {

	std::string header = "";
	std::string closer = "";
	std::string body = "";

	std::string category = "";
	std::string distance = "";
	std::string benefit = "";

	int success = -1;

	std::vector<std::string> categories;

	while (h.find("<NEXTWORDEXACT ") != std::string::npos) {
		header = h.substr(    h.find("<NEXTWORDEXACT ")+1,     h.find(">",     h.find("<NEXTWORDEXACT "))-h.find("<NEXTWORDEXACT ")-1     );
		h = h.substr(h.find(header)+header.length()+1);

		body = h.substr(0,h.find("<"));
		h = h.substr(h.find(body)+body.length());

		closer = h.substr(0, h.find(">"));
		h = h.substr(h.find(closer)+closer.length()+1);

		tokenize(header);
		if (tokens->size() < 3 || tokens->size() > 4) { return -1; }
		if (tokens->size() == 3) {
			category = tokens->at(1);
			distance = "1";
			benefit = tokens->at(2);
		} else {
			category = tokens->at(1);
			distance = tokens->at(2);
			benefit = tokens->at(3);
		}
		tokenize(body);
		categories = (*tokens);

		// Add Confidence 
		int location = b+atoi(distance.c_str());
		for (int i = 0; i < categories.size(); i++) {
			if (y->return_chinese(a, location) == categories.at(i)) {
				if (category == "me") { 
					y->elements->at(a)->at(b)->at(c)->confidence += atof(benefit.c_str());
				} else {
					y->add_confidence(category, atof(benefit.c_str()), a, b);
				}
				success = location;
			}
		}
	}
	if (success > -1) { return success; }
	return -1;
}
int Code::nextwordloop(Text *y, std::string h, int a, int b, int c) {

	std::string header = "";
	std::string closer = "";
	std::string body = "";

	std::string category = "";
	std::string distance = "";
	std::string benefit = "";

	int success = -1;

	std::vector<std::string> categories;

	while (h.find("<NEXTWORDLOOP ") != std::string::npos) {
		header = h.substr(    h.find("<NEXTWORDLOOP ")+1,     h.find(">",     h.find("<NEXTWORDLOOP "))-h.find("<NEXTWORDLOOP ")-1     );
		h = h.substr(h.find(header)+header.length()+1);

		body = h.substr(0,h.find("<"));
		h = h.substr(h.find(body)+body.length());

		closer = h.substr(0, h.find(">"));
		h = h.substr(h.find(closer)+closer.length()+1);

		tokenize(header);
		if (tokens->size() < 3 || tokens->size() > 4) { return -1; }
		if (tokens->size() == 3) {
			category = tokens->at(1);
			distance = "1";
			benefit = tokens->at(2);
		} else {
			category = tokens->at(1);
			distance = tokens->at(2);
			benefit = tokens->at(3);
		}
		tokenize(body);
		categories = (*tokens);

		// Add Confidence 
		int location = 0;
		for (int z = 0; z < 14; z++) {
			location = b+atoi(distance.c_str())+z;
			if (y->is_category_non_recursive("Terminal",a,location) == 1) {z =15;}
			if (y->is_category_non_recursive("Comma",a,location) == 1) {z =15;}
			if (location < y->elements->at(a)->size()) {
				for (int i = 0; i < categories.size(); i++) {
					if (y->return_chinese(a, location).find(categories.at(i)) != std::string::npos) {
				if (category == "me") { 
					y->elements->at(a)->at(b)->at(c)->confidence += atof(benefit.c_str());
				} else {
					y->add_confidence(category, atof(benefit.c_str()), a, b);
				}
				success = location;
				z+=15;
					}
				}
			}
		}
	}
	if (success > -1) { return success; }
	return -1;
}
int Code::lastwordexact(Text *y, std::string h, int a, int b, int c) {

	std::string header = "";
	std::string closer = "";
	std::string body = "";

	std::string category = "";
	std::string distance = "";
	std::string benefit = "";

	int success = -1;

	std::vector<std::string> categories;

	while (h.find("<LASTWORDEXACT ") != std::string::npos) {
		header = h.substr(    h.find("<LASTWORDEXACT ")+1,     h.find(">",     h.find("<LASTWORDEXACT "))-h.find("<LASTWORDEXACT ")-1     );
		h = h.substr(h.find(header)+header.length()+1);

		body = h.substr(0,h.find("<"));
		h = h.substr(h.find(body)+body.length());

		closer = h.substr(0, h.find(">"));
		h = h.substr(h.find(closer)+closer.length()+1);

		tokenize(header);
		if (tokens->size() < 3 || tokens->size() > 4) { return -1; }
		if (tokens->size() == 3) {
			category = tokens->at(1);
			distance = "1";
			benefit = tokens->at(2);
		} else {
			category = tokens->at(1);
			distance = tokens->at(2);
			benefit = tokens->at(3);
		}
		tokenize(body);
		categories = (*tokens);

		// Add Confidence 
		int location = b-atoi(distance.c_str());
		for (int i = 0; i < categories.size(); i++) {
			if (y->return_chinese(a, location) == categories.at(i)) {
				if (category == "me") { 
					y->elements->at(a)->at(b)->at(c)->confidence += atof(benefit.c_str());
				} else {
					y->add_confidence(category, atof(benefit.c_str()), a, b);
				}
				success = location;
			}
		}
	}
	if (success > -1) { return success; }
	return -1;
}
int Code::lastword(Text *y, std::string h, int a, int b, int c) {

	std::string header = "";
	std::string closer = "";
	std::string body = "";

	std::string category = "";
	std::string distance = "";
	std::string benefit = "";

	std::string lastword = "";

	int success = -1;

	std::vector<std::string> categories;

	while (h.find("<LASTWORD ") != std::string::npos) {
		header = h.substr(    h.find("<LASTWORD ")+1,     h.find(">",     h.find("<LASTWORD "))-h.find("<LASTWORD ")-1     );
		h = h.substr(h.find(header)+header.length()+1);

		body = h.substr(0,h.find("<"));
		h = h.substr(h.find(body)+body.length());

		closer = h.substr(0, h.find(">"));
		h = h.substr(h.find(closer)+closer.length()+1);

		tokenize(header);
		if (tokens->size() < 3 || tokens->size() > 4) { return -1; }
		if (tokens->size() == 3) {
			category = tokens->at(1);
			distance = "1";
			benefit = tokens->at(2);
		} else {
			category = tokens->at(1);
			distance = tokens->at(2);
			benefit = tokens->at(3);
		}
		tokenize(body);
		categories = (*tokens);

		// Add Confidence 
		int location = b-atoi(distance.c_str());
		for (int i = 0; i < categories.size(); i++) {
			lastword = y->return_chinese(a, location);
			if (lastword.length() >= categories.at(i).length()) {
				if (lastword.substr(lastword.length()-categories.at(i).length(), categories.at(i).length()) == categories.at(i)) {
				if (category == "me") { 
					y->elements->at(a)->at(b)->at(c)->confidence += atof(benefit.c_str());
				} else {
					y->add_confidence(category, atof(benefit.c_str()), a, b);
				}
					success = location;
				}
			}
		}
	}
	if (success > -1) { return success; }
	return -1;
}
int Code::lastwordloop(Text *y, std::string h, int a, int b, int c) {

	std::string header = "";
	std::string closer = "";
	std::string body = "";

	std::string category = "";
	std::string distance = "";
	std::string benefit = "";

	int success = -1;

	std::vector<std::string> categories;

	while (h.find("<LASTWORDLOOP ") != std::string::npos) {
		header = h.substr(    h.find("<LASTWORDLOOP ")+1,     h.find(">",     h.find("<LASTWORDLOOP "))-h.find("<LASTWORDLOOP ")-1     );
		h = h.substr(h.find(header)+header.length()+1);

		body = h.substr(0,h.find("<"));
		h = h.substr(h.find(body)+body.length());

		closer = h.substr(0, h.find(">"));
		h = h.substr(h.find(closer)+closer.length()+1);

		tokenize(header);
		if (tokens->size() < 3 || tokens->size() > 4) { return -1; }
		if (tokens->size() == 3) {
			category = tokens->at(1);
			distance = "1";
			benefit = tokens->at(2);
		} else {
			category = tokens->at(1);
			distance = tokens->at(2);
			benefit = tokens->at(3);
		}
		tokenize(body);
		categories = (*tokens);

		// Add Confidence 
		int location = 0;;
		for (int z = 0; z < 14; z++) {
			location = b-atoi(distance.c_str())-z;
			if (y->is_category_non_recursive("Terminal",a,location) == 1) {z =15;}
			if (y->is_category_non_recursive("Comma",a,location) == 1) {z =15;}
			if (location >= 0) {
				for (unsigned int i = 0; i < categories.size(); i++) {
					if (y->return_chinese(a, location).find(categories.at(i)) != std::string::npos) {
				if (category == "me") { 
					y->elements->at(a)->at(b)->at(c)->confidence += atof(benefit.c_str());
				} else {
					y->add_confidence(category, atof(benefit.c_str()), a, b);
				}
						success = location;
						z = 25;
					}
				}
			}
		}
	}
	if (success > -1) { return success; }
	return -1;
}
int Code::matchexact(Text *y, std::string h, int a, int b, int c) { return match(y, h, a, b, c); }
int Code::contains(Text *y, std::string h, int a, int b, int c) {

        std::string header = "";
        std::string classtotest = "";
        std::string distance = "";
        int location = b;

        while (h.find("<CONTAINS ") != std::string::npos) {

                header = h.substr(    h.find("<CONTAINS ")+1,     h.find(">",     h.find("<CONTAINS "))-h.find("<CONTAINS ")-1     );
                h = h.substr(h.find(header)+header.length()+1);

                location = b;

                tokenize(header);
                if (tokens->size() == 2) {
                        classtotest = tokens->at(1);
                } else {
                        if (tokens->size() == 3) {
                                location += atoi(tokens->at(1).c_str());
                                classtotest = tokens->at(2);
                        } else { return -1; }
                }

                if (classtotest == "") { return -1; }


                // Check that this Class Exists
                if (y->text(a,location,0)->return_chinese().find(classtotest) != std::string::npos) {
                        return location;
                }
        }

	return -1;
}
int Code::match(Text *y, std::string h, int a, int b, int c) {

	std::string header = "";
	std::string closer = "";
	std::string body = "";

	std::string category = "";
	std::string distance = "";
	std::string benefit = "";

	int success = -1;

	std::vector<std::string> categories;

	while (h.find("<MATCH ") != std::string::npos) {

		header = h.substr(    h.find("<MATCH ")+1,     h.find(">",     h.find("<MATCH "))-h.find("<MATCH ")-1     );
		h = h.substr(h.find(header)+header.length()+1);

		body = h.substr(0,h.find("<"));
		h = h.substr(h.find(body)+body.length());

		closer = h.substr(0, h.find(">"));
		h = h.substr(h.find(closer)+closer.length()+1);

		tokenize(header);
		if (tokens->size() != 3) { return -1; }
		category = tokens->at(1);
		benefit = tokens->at(2);

		tokenize(body);
		categories = (*tokens);

		// Add Confidence 
		for (int i = 0; i < categories.size(); i++) {
			if (y->sentence_forward_word_match(categories.at(i), a, b) > -1) {
				y->elements->at(a)->at(b)->at(c)->add_confidence(atof(benefit.c_str()));
				return b; 
			}
			if (y->sentence_backward_word_match(categories.at(i), a, b) > -1) {
				y->elements->at(a)->at(b)->at(c)->add_confidence(atof(benefit.c_str()));
				return b; 
			}
		}
	}
	return -1;
}
int Code::textmatch(Text *y, std::string h, int a, int b, int c) {

	std::string header = "";
	std::string closer = "";
	std::string body = "";

	std::string category = "";
	std::string distance = "";
	std::string benefit = "";

	int success = -1;

	std::vector<std::string> categories;

	while (h.find("<TEXTMATCH ") != std::string::npos) {
		header = h.substr(    h.find("<TEXTMATCH ")+1,     h.find(">",     h.find("<TEXTMATCH "))-h.find("<TEXTMATCH ")-1     );
		h = h.substr(h.find(header)+header.length()+1);

		body = h.substr(0,h.find("<"));
		h = h.substr(h.find(body)+body.length());

		closer = h.substr(0, h.find(">"));
		h = h.substr(h.find(closer)+closer.length()+1);

		tokenize(header);
		if (tokens->size() != 3) { return -1; }
		category = tokens->at(1);
		benefit = tokens->at(2);

		tokenize(body);
		categories = (*tokens);

		if (y->fulltext_gb2312 == "") { y->fulltext_gb2312 = y->return_chinese(); }


		// Add Confidence 
		for (int i = 0; i < categories.size(); i++) {
			if (y->fulltext_gb2312.find(categories.at(i)) != std::string::npos) {
				y->elements->at(a)->at(b)->at(c)->add_confidence(atof(benefit.c_str()));
				success = b;
			}
		}
	}
	if (success > -1) { return success; }
	return -1;
}
int Code::compound_chain_execute(Text *y, std::string h, int a, int b, int c) {

	std::string header = "";
	std::string body = "";
	std::string compound = "";
	std::string benefit = "";
	int location = b;
	int total_length = 0;
	int temp_int = 0;

	int success = -1;

	while (h.find("<COMPOUND_CHAIN_EXECUTE>") != std::string::npos) {

		success = -1;

		header = h.substr(    h.find("<COMPOUND_CHAIN_EXECUTE")+1,     h.find(">",     h.find("<COMPOUND_CHAIN_EXECUTE"))-h.find("<COMPOUND_CHAIN_EXECUTE")-1     );
		h = h.substr(h.find(header)+header.length()+1);


		body = h.substr(0,h.find("<"));
		h = h.substr(h.find(body)+body.length());

		tokens->clear();
		tokenize(body);

		std::vector<std::string> categories;
		std::vector<int> component_lengths;
		std::vector<int> compound_or_not;
		for (int i = 0; i < tokens->size(); i++) { categories.push_back(tokens->at(i)); }

		int relative_location = b;
		total_length = 0;
		temp_int = 0;
		

		for (int i = 0; i < categories.size(); i++) {
			if (y->is_category(categories.at(i),a,relative_location) == 1 || y->return_chinese(a,relative_location) == categories.at(i)) {
				relative_location++;
				component_lengths.push_back(1);
				compound_or_not.push_back(0);
				total_length++;
				success++;
				temp_int = 1;
			} else {
				int match_found = 0;
				for (int ii = 0; ii < compound_xml->size(); ii++) {
					if (compounds->at(ii) == categories.at(i)) {
						if (analyse_code(y,compound_xml->at(ii),a,relative_location,0) > -1) {
							match_found = 1;
							std::string length_query = "<COMPOUND_LENGTH " + itoa(total_length) + " " + compounds->at(ii) + ">";
							int tempy = analyse_code(y, length_query,a,relative_location,0);
							if (tempy == -1) {
								return -1;
							}
							else {
								relative_location+=tempy;
								total_length+=tempy;
								compound_or_not.push_back(1);
								component_lengths.push_back(tempy);
								ii = compound_xml->size()+2;
								success++;
							}
						}
					}
				}
				if (match_found == 0) { return -1; }
			}
		}
		if (success > -1) { 
			for (int zz = 0, mylocation = 0; zz < component_lengths.size(); zz++) {
				if (compound_or_not.at(zz) == 1) {
					std::string execute_xml = "<COMPOUND_EXECUTE ";
					execute_xml += itoa(mylocation);
					execute_xml += " ";
					execute_xml += categories.at(zz);
					execute_xml += ">";
					//for (int mm = 0; mm < y->elements->at(a)->at(b+mylocation)->size(); mm++) {
						analyse_code(y,execute_xml,a,b+mylocation,0);
					//}
					mylocation += component_lengths.at(zz);
				}

			}; 

			// Now Execute My Own Code Following Code
	
		}
	}
	if (success > 1) { return success; }
	return -1;
}
int Code::compound_execute(Text *y, std::string h, int a, int b, int c) {

	std::string header = "";

	std::string compound = "";
	std::string benefit = "";
	int location = b;

	int success = -1;

	while (h.find("<COMPOUND_EXECUTE ") != std::string::npos) {

		header = h.substr(    h.find("<COMPOUND_EXECUTE ")+1,     h.find(">",     h.find("<COMPOUND_EXECUTE "))-h.find("<COMPOUND_EXECUTE ")-1     );
		h = h.substr(h.find(header)+header.length()+1);

		tokenize(header);
		if (tokens->size() == 2) { 
			location = 0;
			compound = tokens->at(1);
		} else {
			if (tokens->size() == 3) {
				compound = tokens->at(2);
				location = atoi(tokens->at(1).c_str());
			} else { return -1; }
		}



		for (int i = 0; i < compound_xml_action->size(); i++) {
			if (compounds->at(i) == compound) {
				if (analyse_code(y,compound_xml->at(i),a,b+location,0) > -1) {
	//				for (int zzz = 0; zzz < y->elements->at(a)->at(b+location)->size(); zzz++) {
						return analyse_code(y,compound_xml_action->at(i),a,b+location,0);
	//				}
				}
			}
		}
	}
	if (success > -1) { return success; }
	return -1;
}
int Code::compound_length(Text *y, std::string h, int a, int b, int c) {

	std::string header = "";
	std::string compound = "";
	int location = b;

	int success = -1;

	while (h.find("<COMPOUND_LENGTH ") != std::string::npos) {

		header = h.substr(    h.find("<COMPOUND_LENGTH ")+1,     h.find(">",     h.find("<COMPOUND_LENGTH "))-h.find("<COMPOUND_LENGTH")-1     );
		h = h.substr(h.find(header)+header.length()+1);

		tokenize(header);
		if (tokens->size() == 2) { 
			compound = tokens->at(1);
			location = 0;
		} else { 
		  if (tokens->size() == 3) {
			location = atoi(tokens->at(1).c_str());
			compound = tokens->at(2);
		  } else {return -1; }
		}


		// Which Compound?
		for (int i = 0; i < compound_xml->size(); i++) {
			if (compounds->at(i) == compound) {

				std::string temp2 = "<CLASS2 " + itoa(location);
				std::string temp3 = "<CHINESE2 " + itoa(location);
				std::string temp4 = "<COMPOUND2 " + itoa(location);

				std::string temp = compound_xml->at(i);
				while (temp.find("<CLASS ") != std::string::npos) {
					temp.replace(temp.find("<CLASS "), 6, temp2);
				}
				while (temp.find("<CHINESE ") != std::string::npos) {
					temp.replace(temp.find("<CLASS "), 8, temp3);
				}
				while (temp.find("<COMPOUND ") != std::string::npos) {
					temp.replace(temp.find("<COMPOUND "), 9, temp4);
				}

				int testlka = analyse_code(y,temp,a,b,0);

				if (testlka > -1) {

					// CLASS Instances and CHINESE Instances get +1, COMPOUNDS are treated recursively
					int length_to_report = 0;

					std::string cc = compound_xml->at(i);
					while (cc.find("<CLASS") != std::string::npos) {
						length_to_report++;
						cc = cc.substr(cc.find("<CLASS")+6);
					}

					cc = compound_xml->at(i);
					while (cc.find("<CHINESE") != std::string::npos) {
						length_to_report++;
						cc = cc.substr(cc.find("<CHINESE")+8);
					}

					cc = compound_xml->at(i);
					while (cc.find("<COMPOUND") != std::string::npos) {
						cc = cc.substr(cc.find("<COMPOUND")+9);
						std::string tempx = "<COMPOUND_LENGTH2" + cc.substr(0, cc.find(">")) + ">";
						int tempz = analyse_code(y,tempx,a,b,c);
						if (tempz == -1) { return -1; }
						else {
							length_to_report+=tempz;
						}
						cc = cc.substr(cc.find("<COMPOUND")+9);
					}


					return length_to_report;
				}
			}
		}
	}
	if (success > -1) { return success; }
	return -1;
}
int Code::compound_length2(Text *y, std::string h, int a, int b, int c) {

	std::string header = "";
	std::string compound = "";
	int location = b;

	int success = -1;

	while (h.find("<COMPOUND_LENGTH2 ") != std::string::npos) {

		header = h.substr(    h.find("<COMPOUND_LENGTH2 ")+1,     h.find(">",     h.find("<COMPOUND_LENGTH2 "))-h.find("<COMPOUND_LENGTH2")-1     );
		h = h.substr(h.find(header)+header.length()+1);

		tokenize(header);
		if (tokens->size() == 2) { 
			compound = tokens->at(1);
		} else { 
			if (tokens->size() == 3) {
				compound = tokens->at(2);
				location = b+atoi(tokens->at(1).c_str());
			} else { return -1; }
		}



		// Which Compound?
		for (int i = 0; i < compound_xml->size(); i++) {
			if (compounds->at(i) == compound) {
				if (analyse_code(y,compound_xml->at(i),a,location,0) > -1) {
					// CLASS Instances and CHINESE Instances get +1, COMPOUNDS are treated recursively
					int length_to_report = 0;

					std::string cc = compound_xml->at(i);
					while (cc.find("CLASS") != std::string::npos) {
						length_to_report++;
						cc = cc.substr(cc.find("CLASS")+5);
					}

					cc = compound_xml->at(i);
					while (cc.find("CHINESE") != std::string::npos) {
						length_to_report++;
						cc = cc.substr(cc.find("CHINESE")+5);
					}

					cc = compound_xml->at(i);
					while (cc.find("COMPOUND") != std::string::npos) {
						cc = cc.substr(cc.find("<COMPOUND")+9);
						std::string tempx = "<COMPOUND_LENGTH2" + cc.substr(0, cc.find(">")) + ">";
						int tempz = analyse_code(y,tempx,a,b,c);
						if (tempz == -1) { return -1; }
						else {
							length_to_report+=tempz;
						}
						cc = cc.substr(cc.find("<COMPOUND")+9);
					}

					return length_to_report;
				}
			}
		}
	}
	if (success > -1) { return success; }
	return -1;
}
int Code::compound_bonus2(Text *y, std::string h, int a, int b, int c) {

	std::string header = "";

	std::string compound = "";
	std::string benefit = "";
	int location = b;

	int success = -1;

	while (h.find("<COMPOUND_BONUS2 ") != std::string::npos) {

		header = h.substr(    h.find("<COMPOUND_BONUS2 ")+1,     h.find(">",     h.find("<COMPOUND_BONUS2 "))-h.find("<COMPOUND_BONUS2")-1     );
		h = h.substr(h.find(header)+header.length()+1);

		tokenize(header);
		if (tokens->size() == 3) { 
			location = 0;
			compound = tokens->at(1);
			benefit = tokens->at(2);
		} else {
			if (tokens->size() == 4) {
				compound = tokens->at(3);
				location = atoi(tokens->at(2).c_str());
				benefit = tokens->at(1);
			} else { return -1; }
		}




		// Which Compound?
		std::string temp2 = "<BONUS2 " + benefit;
		std::string temp3 = "<COMPOUND_BONUS2 " + benefit;
		for (int i = 0; i < compound_xml->size(); i++) {
			if (compounds->at(i) == compound) {
				if (analyse_code(y,compound_xml->at(i),a,b+location,0) > -1) {

					std::string temp = compound_xml->at(i);
					while (temp.find("<CLASS ") != std::string::npos) {
						temp.replace(temp.find("<CLASS "), 6, temp2);
					}
					while (temp.find("<COMPOUND ") != std::string::npos) {
						temp.replace(temp.find("<COMPOUND_BONUS "), 6, temp3);
					}

					return analyse_code(y,temp,a,b+location,0);
				}
			}
		}
	}
	if (success > -1) { return success; }
	return -1;
}
int Code::compound_bonus(Text *y, std::string h, int a, int b, int c) {

	std::string header = "";

	std::string compound = "";
	std::string benefit = "";
	int location = b;

	int success = -1;

	while (h.find("<COMPOUND_BONUS ") != std::string::npos) {

		header = h.substr(    h.find("<COMPOUND_BONUS ")+1,     h.find(">",     h.find("<COMPOUND_BONUS "))-h.find("<COMPOUND_BONUS ")-1     );
		h = h.substr(h.find(header)+header.length()+1);

		tokenize(header);
		if (tokens->size() == 3) { 
			location = 0;
			compound = tokens->at(1);
			benefit = tokens->at(2);
		} else {
			if (tokens->size() == 4) {
				compound = tokens->at(1);
				location = atoi(tokens->at(2).c_str());
				benefit = tokens->at(3);
			} else { return -1; }
		}




		// Which Compound?
		std::string temp2 = "<BONUS2 " + benefit;
		std::string temp3 = "<COMPOUND_BONUS2 " + benefit;
		for (int i = 0; i < compound_xml->size(); i++) {
			if (compounds->at(i) == compound) {
				if (analyse_code(y,compound_xml->at(i),a,b+location,0) > -1) {

					std::string temp = compound_xml->at(i);
					while (temp.find("<CLASS ") != std::string::npos) {
						temp.replace(temp.find("<CLASS "), 6, temp2);
					}
					while (temp.find("<COMPOUND ") != std::string::npos) {
						temp.replace(temp.find("<COMPOUND_BONUS "), 16, temp3);
					}

						return analyse_code(y,temp,a,b+location,0);

				}
			}
		}
	}
	if (success > -1) { return success; }
	return -1;
}
int Code::bonus2(Text *y, std::string h, int a, int b, int c) {

	std::string header = "";

	std::string category = "";
	std::string distance = "";
	std::string benefit = "";

	int success = -1;

	while (h.find("<BONUS2 ") != std::string::npos) {

		header = h.substr(    h.find("<BONUS2 ")+1,     h.find(">",     h.find("<BONUS2 "))-h.find("<BONUS2 ")-1     );
		h = h.substr(h.find(header)+header.length()+1);

		tokenize(header);
		if (tokens->size() == 3) {
		  category = tokens->at(2);
		  distance = "0";
		  benefit = tokens->at(1);
		} else {
		  if (tokens->size() == 4) {
		    category = tokens->at(3);
		    distance = tokens->at(2);
		    benefit = tokens->at(1);
		  } else { return -1; }
                }

		if (category == "me") { y->elements->at(a)->at(b)->at(c)->add_confidence(atof(benefit.c_str())); success = b;}
		else {

			// Add Confidence 
			int location = b+atoi(distance.c_str());
			// Add Confidence 
			if (y->is_category(category, a, location) == 1) {
				y->add_confidence(category, atof(benefit.c_str()), a, location);
				success = location;
			}
		}
	}
	if (success > -1) { return success; }
	return -1;

}
int Code::bonus(Text *y, std::string h, int a, int b, int c) {

	std::string header = "";

	std::string category = "";
	std::string distance = "";
	std::string benefit = "";

	int success = -1;


	while (h.find("<BONUS ") != std::string::npos) {


		header = h.substr(    h.find("<BONUS ")+1,     h.find(">",     h.find("<BONUS "))-h.find("<BONUS ")-1     );
		h = h.substr(h.find(header)+header.length()+1);

		tokenize(header);
		if (tokens->size() == 3) {
		  category = tokens->at(1);
		  distance = "0";
		  benefit = tokens->at(2);
		} else {
		  if (tokens->size() == 4) {
		    category = tokens->at(1);
		    distance = tokens->at(2);
		    benefit = tokens->at(3);
		  } else { return -1; }
                }
   

		if (category == "me") { y->elements->at(a)->at(b)->at(c)->add_confidence(atof(benefit.c_str())); success = b;}
		else {

			// Add Confidence 
			int location = b+atoi(distance.c_str());

			// Add Confidence 
			if (y->is_category(category, a, location) == 1) {
				y->add_confidence(category, atof(benefit.c_str()), a, location);
				success = location;
			}
		}
	}
	if (success > -1) { return success; }
	return -1;
}
int Code::boost(Text *y, std::string h, int a, int b, int c) {

	std::string header = "";
	std::string closer = "";
	std::string body = "";

	std::string category = "";
	std::string distance = "";
	std::string benefit = "";

	int success = -1;

	std::vector<std::string> categories;

	while (h.find("<BOOST ") != std::string::npos) {


		header = h.substr(    h.find("<BOOST ")+1,     h.find(">",     h.find("<BOOST "))-h.find("<BOOST ")-1     );
		h = h.substr(h.find(header)+header.length()+1);

		tokenize(header);
		if (tokens->size() == 3) {
			category = tokens->at(1);
			distance = "0";
			benefit = tokens->at(2);
		} else {
			if (tokens->size() == 4) {
				category = tokens->at(1);
				distance = tokens->at(2);
				benefit = tokens->at(3);
			} else { return -1; }
		}
		tokenize(body);
		categories = (*tokens);

		// Add Confidence 
		int location = b+atoi(distance.c_str());

		if (category == "me") { 
			y->add_confidence(y->elements->at(a)->at(b)->at(c)->myclass, atof(benefit.c_str()), a, b); 
			success = b;
		} else {
  			if (y->is_category(category, a, location) == 1) {
				y->add_confidence(category, atof(benefit.c_str()), a, location);
				success = location;
			}
		}
	}
	if (success > -1) { return success; }
	return -1;
}
int Code::delete_entry(Text *y, std::string h, int a, int b, int c) {

	std::string header = "";
	std::string closer = "";
	std::string body = "";

	std::string category = "";
	std::string benefit = "";
	int location = b;


	int success = 0;

	std::vector<std::string> categories;

	while (h.find("<DELETE") != std::string::npos) {

		location = b;

		header = h.substr(    h.find("<DELETE")+1,     h.find(">",     h.find("<DELETE"))-h.find("<DELETE")-1     );
		h = h.substr(h.find(header)+header.length()+1);

		tokenize(header);
		if (tokens->size() == 2) { 
			category = tokens->at(1);
		} else { 
		  if (tokens->size() == 3) { 
			category = tokens->at(2);
			location += atoi(tokens->at(1).c_str());
	 	  } else {
		    category = "me";
		  }
		}


		if (location < 0 || location > y->elements->at(a)->size()) { return -1; }
		if (category == "all") {
			if (y->elements->at(a)->at(location)->size() >= 1) {
				for (int i = 0; i < y->elements->at(a)->at(location)->size(); i++) {
					delete y->elements->at(a)->at(location)->at(i);
				}
				y->elements->at(a)->at(location)->clear();
				delete y->elements->at(a)->at(location);
				y->elements->at(a)->erase(y->elements->at(a)->begin()+location);
				return location;
			}
		} else {
		if (category == "me") { 
			if (y->elements->at(a)->at(location)->size() > 1) {
				delete y->elements->at(a)->at(location)->at(c);
				y->elements->at(a)->at(location)->erase(y->elements->at(a)->at(b)->begin()+c);
				return location;
			}
		} else {
			int non_match_found = 0;
			// Check that there will be something left after we delete
			for (int i = 0; i < y->elements->at(a)->at(location)->size(); i++) {
				if (y->elements->at(a)->at(location)->at(i)->myclass.find(category) == std::string::npos) {
					non_match_found = 1;
				}
			}
			if (non_match_found == 1) {
				for (int i = 0; i < y->elements->at(a)->at(location)->size(); i++) {
					if (y->elements->at(a)->at(location)->at(i)->myclass.find(category) != std::string::npos) {
						delete y->elements->at(a)->at(location)->at(i);
						y->elements->at(a)->at(location)->erase(y->elements->at(a)->at(location)->begin()+i);
						i--;
						return location;
					}
				}
			}

		}
		} // all else
	}

	if (success > -1) { return success; }
	return -1;
}
int Code::make_only_entry(Text *y, std::string h, int a, int b, int c) {

	std::string header = "";
	std::string closer = "";
	std::string body = "";

	std::string category = "";
	std::string benefit = "";
	int location = b;

	int success = -1;


	while (h.find("<MAKE_ONLY") != std::string::npos) {
		location = b;
		header = h.substr(    h.find("<MAKE_ONLY")+1,     h.find(">",     h.find("<MAKE_ONLY"))-h.find("<MAKE_ONLY")-1     );
		h = h.substr(h.find(header)+header.length()+1);



		if (h.find("</MAKE_ONLY>") != std::string::npos) {

			std::string z = h.substr(0, h.find("</MAKE_ONLY>"));
			std::string zz = header.substr(10, h.find(">"));
			z = z.substr(0, z.find("</MAKE_ONLY>"));
			h = h.substr(h.find("</MAKE_ONLY>")+12);

			tokenize(header);
			if (tokens->size() == 2) { 
				category = tokens->at(1);
			} else { 
			  if (tokens->size() == 3) { 
				category = tokens->at(1);
				benefit += atoi(tokens->at(2).c_str());
		 	  } else {
			    category = "me";
			  }
			}

			int should_we_make_only = process_code(y, z, a, b, c);

			if (should_we_make_only > -1) {
				if (location < 0 || location > y->elements->at(a)->size()) { return -1; }
				if (category == "me") { 
					for (int i = 0; i < y->elements->at(a)->at(location)->size(); i++) {
						if (y->elements->at(a)->at(location)->at(i)->myclass.find(y->elements->at(a)->at(b)->at(c)->myclass) == std::string::npos) {
							delete y->elements->at(a)->at(location)->at(i);
							y->elements->at(a)->at(location)->erase(y->elements->at(a)->at(location)->begin()+i);
							i--;
							c--; if (c < 0) { c = 0; }
							return location;
						} else {
						}
					}
				} else {

					// Check to see that this category exists, only make-only if it does
					int check = 0;
					for (int i = 0; i < y->elements->at(a)->at(location)->size(); i++) {
						if (y->elements->at(a)->at(location)->at(i)->myclass.find(category) != std::string::npos) {
							check = 1;
						}
					}
					if (check == 1) {
						for (int i = 0; i < y->elements->at(a)->at(location)->size(); i++) {
							if (y->elements->at(a)->at(location)->at(i)->myclass.find(category) == std::string::npos) {
								delete y->elements->at(a)->at(location)->at(i);
								y->elements->at(a)->at(location)->erase(y->elements->at(a)->at(location)->begin()+i);
								i--;
								return location;
							}
						}
					}
				}
			}
		} else {


			tokenize(header);
			if (tokens->size() == 2) { 
				location = b;
				category = tokens->at(1);
			} else { 
			  if (tokens->size() == 3) { 
				location = b+atoi(tokens->at(1).c_str());
				category = tokens->at(2);
		 	  } else {
			    category = "me";
			  }
			}

			if (location < 0 || location > y->elements->at(a)->size()) { return -1; }
			if (category == "me") { 
				for (int i = 0; i < y->elements->at(a)->at(location)->size(); i++) {
					if (y->elements->at(a)->at(location)->at(i)->myclass.find(y->elements->at(a)->at(b)->at(c)->myclass) == std::string::npos) {
						delete y->elements->at(a)->at(location)->at(i);
						y->elements->at(a)->at(location)->erase(y->elements->at(a)->at(location)->begin()+i);
						i--;
						return location;
					}
				}
			} else {

				// Check to see that this category exists, only make-only if it does
				int check = 0;

				for (int i = 0; i < y->elements->at(a)->at(location)->size(); i++) {
					if (y->elements->at(a)->at(location)->at(i)->myclass.find(category) != std::string::npos) {
						check = 1;
					}
				}
				if (check == 1) {
					for (int i = 0; i < y->elements->at(a)->at(location)->size(); i++) {
						if (y->elements->at(a)->at(location)->at(i)->myclass.find(category) == std::string::npos) {
							delete y->elements->at(a)->at(location)->at(i);
							y->elements->at(a)->at(location)->erase(y->elements->at(a)->at(location)->begin()+i);
							i--;
						}
					}
					return location;
				}
			}
		}
	}
	return -1;
}
int Code::resegment(Text *y, std::string h, int a, int b, int c) {

	std::string header = "";
	std::string closer = "";
	std::string body = "";

	std::string category = "";
	int location = 0;
	int distance = 0;

	while (h.find("<RESEGMENT") != std::string::npos) {

		h = h.substr(h.find("<RESEGMENT"));

		header = h.substr(h.find("<RESEGMENT")+1,  h.find(">")-1);
		h = h.substr(h.find(header)+header.length()+1);

		location = b;

		if (h.find("</RESEGMENT") != std::string::npos) {

			std::string z = h.substr(0, h.find("</RESEGMENT>"));
			h = h.substr(h.find("</RESEGMENT>")+12);

			tokenize(header);
			if (tokens->size() == 2) { 
				distance = atoi(tokens->at(1).c_str());
				if (distance == 0) {
					distance = 1;
					category = tokens->at(1);
				}
			} else { 
			  if (tokens->size() == 3) { 
				category = tokens->at(1);
				distance += atoi(tokens->at(2).c_str());
		 	  } else {
			    category = "me";
			    distance = 1;
			  }
			}

			int should_we_resegment = process_code(y, z, a, b, c);
			if (should_we_resegment > -1) {
				if (y->resegment(a, b, distance) > -1) {
					return b;
				}
			}
		} else {

			tokenize(header);
			if (tokens->size() == 1) {
				location = b; distance = 1;
			}
			if (tokens->size() == 2) {
				if (tokens->at(1) == "me") {
					location == b;
					distance = 1;
				}
				else {
					location = b;
					distance = atoi(tokens->at(1).c_str());
				}
			}
			if (tokens->size() == 3) {
				category = tokens->at(1);
				distance = atoi(tokens->at(2).c_str());
			}
			if (y->resegment(a, b, distance) > -1) { return b; }
		}
	}
	return -1;
}

int Code::tense(Text *y, std::string h, int a, int b, int c) {

	std::string header = "";

	int location = b;
	int length = 0;
	std::string category = "";
	int tense = 0;

	int success = -1;

	while (h.find("<TENSE") != std::string::npos) {

		location = b;
		header = h.substr(h.find("<TENSE")+1,  h.find(">")-1);
		h = h.substr(h.find(header)+header.length()+1);

		tokenize(header);
		if (tokens->size() == 3) { 
			location = b+(atoi(tokens->at(1).c_str()));
			tense = atoi(tokens->at(2).c_str());
		} else {
			if (tokens->size() == 4) {
				location += atoi(tokens->at(1).c_str());
				category = tokens->at(2);
				tense = atoi(tokens->at(3).c_str());
			} else { return -1; }
		}
		
		
		if (y->is_category(category, a, location) == 1) {
			for (int i = 0; i < y->elements->at(a)->at(location)->size(); i++) {
				if (y->elements->at(a)->at(location)->at(i)->myclass.find("Verb") != std::string::npos) {
					for (int z = 0; z < y->elements->at(a)->at(location)->size(); z++) {
						if (y->elements->at(a)->at(location)->at(z)->myclass.find("Verb") != std::string::npos) {
							y->elements->at(a)->at(location)->at(z)->vtense = tense;
						}
					}
					y->make_only(a,b,c);
					y->make_only(a,location,"Verb");
					return location;
				}
			}
		}
	}
	if (success > -1) { return success; }
	return -1;
}
int Code::transform_01(Text *y, std::string h, int a, int b, int c) {

	std::string header = "";
	std::string closer = "";
	std::string body = "";

	std::string category = "";
	std::string distance = "";
	std::string benefit = "";

	int success = -1;

	std::vector<std::string> categories;

	while (h.find("<TRANSFORM_01 ") != std::string::npos) {
		header = h.substr(    h.find("<TRANSFORM_01 ")+1,     h.find(">",     h.find("<TRANSFORM_01 "))-h.find("<TRANSFORM_01 ")-1     );
		h = h.substr(h.find(header)+header.length()+1);

		body = h.substr(0,h.find("<"));
		h = h.substr(h.find(body)+body.length());

		closer = h.substr(0, h.find(">"));
		h = h.substr(h.find(closer)+closer.length()+1);

		tokenize(body);
		categories = (*tokens);

		for (unsigned int i = 0; i < categories.size(); i++) {
			for (int z = 1; z < 16; z++) {
				if (y->is_category_non_recursive("Terminal",a,b+z) == 1) { break; }
				if (y->is_category_non_recursive("Comma",a,b+z) == 1) { break; }
				if (y->return_chinese(a, b+z,0) == categories.at(i)) {
					y->text(a,b,c)->myclass += ":Transform_01";
					y->text(a,b,c)->set_english(header.substr(13));	
					y->likely(a,b+z)->set_english(closer.substr(14));
					y->make_only(a,b,y->text(a,b,c));
					y->likely(a,b+z)->myclass += ":Transform_01";
					y->make_only(a,b+z,y->likely(a,b+z));
					return b+z;
				}
			}
		}


	}
	if (success > -1) { return success; }
	return -1;
}
int Code::reduce(Text *y, std::string h, int a, int b, int c) {

	std::string header = "";
	int number = 1;

	std::vector<std::string> categories;

	while (h.find("<REDUCE") != std::string::npos) {
		header = h.substr(    h.find("<REDUCE")+1,     h.find(">",     h.find("<REDUCE"))-h.find("<REDUCE")-1     );
		h = h.substr(h.find(header)+header.length()+1);

		tokenize(header);

		y->make_only(a,b,y->likely(a,b));
		return b;
	}
	return -1;
}







































int Code::is_number(Text *y, std::string h, int a, int b, int c) {

	std::string header = "";

	int location = b;
	int length = 0;
	std::string comparison = "";

	int success = -1;

	while (h.find("<NUMBER") != std::string::npos) {
		location = b;
		header = h.substr(h.find("<NUMBER")+1,  h.find(">")-1);
		h = h.substr(h.find(header)+header.length()+1);

		tokenize(header);
		if (tokens->size() == 3) { 
			comparison = tokens->at(1);
			length = atoi(tokens->at(2).c_str());
		} else {
			if (tokens->size() == 4) {
				location += atoi(tokens->at(1).c_str());
				comparison = tokens->at(2);
				length = atoi(tokens->at(3).c_str());
			} else { return -1; }
		}

		if (y->elements->at(a)->size() > location && location >= 0) {
			if (y->is_category_non_recursive("Number", a, location) == 1) {
				int length_at_location = y->text(a, location, "Number")->integer_representation;
				if (comparison == "is") { if (length_at_location == length) { success = location; }  }
				if (comparison == "gt") { if (length_at_location > length) { success = location; }  }
				if (comparison == "lt") { if (length_at_location < length) { success = location; }  }
				if (comparison == "not") { if (length_at_location != length) { success = location; }  }
			}
		}
	}
	if (success > -1) { return success; }
	return -1;
}
int Code::length(Text *y, std::string h, int a, int b, int c) {

	std::string header = "";

	int location = b;
	int length = 0;
	std::string comparison = "";

	int success = -1;

	while (h.find("<LENGTH") != std::string::npos) {
		location = b;
		header = h.substr(h.find("<LENGTH")+1,  h.find(">")-1);
		h = h.substr(h.find(header)+header.length()+1);

		tokenize(header);
		if (tokens->size() == 3) { 
			comparison = tokens->at(1);
			length = atoi(tokens->at(2).c_str());
		} else {
			if (tokens->size() == 3) {
				location += atoi(tokens->at(1).c_str());
				comparison = tokens->at(2);
				length = atoi(tokens->at(3).c_str());
			} else { return -1; }
		}

		if (y->elements->at(a)->size() > location && location >= 0) {
			std::string temp = y->elements->at(a)->at(location)->at(0)->return_chinese_input_encoding();
			int length_at_location = y->encoding->character_length(temp);
			if (comparison == "is") { if (length_at_location == length) { success = location; }  }
			if (comparison == "gt") { if (length_at_location > length) { success = location; }  }
			if (comparison == "lt") { if (length_at_location < length) { success = location; }  }
			if (comparison == "not") { if (length_at_location != length) { success = location; }  }
		}
	}
	if (success > -1) { return success; }
	return -1;
}
int Code::plural_next(Text *y, std::string h, int a, int b, int c) {

	std::string header = "";
	int location = b;
	int success = -1;

	while (h.find("<PLURALNEXT") != std::string::npos) {
		header = h.substr(h.find("<PLURALNEXT")+1,  h.find(">")-1);
		h = h.substr(h.find(header)+header.length()+1);

		success == y->plural_next_noun(a,b,1);
	}
	if (success != -1) { return success; }
	return -1;
}
int Code::pluralize(Text *y, std::string h, int a, int b, int c) {

	std::string header = "";
	int location = b;
	int success = 0;

	while (h.find("<PLURALIZE") != std::string::npos) {
		location = b;
		header = h.substr(h.find("<PLURALIZE")+1,  h.find(">")-1);
		h = h.substr(h.find(header)+header.length()+1);

		tokenize(header);
		if (tokens->size() == 2) { 
  		  	location += atoi(tokens->at(1).c_str());
		} else {
		  	location = b;
		}

		if (y->return_chinese(a, location) != "") {
			for (unsigned int i = 0; i < y->elements->at(a)->at(location)->size(); i++) {
				y->elements->at(a)->at(location)->at(i)->plural = 1;
			}
		}
	}
	return b;
}
int Code::not_translate(Text *y, std::string h, int a, int b, int c) {

	std::string header = "";
	int location = b;
	int success = 0;

	while (h.find("<NOTTRANSLATE") != std::string::npos) {
		location = b;
		header = h.substr(h.find("<NOTTRANSLATE")+1,  h.find(">")-1);
		h = h.substr(h.find(header)+header.length()+1);

		tokenize(header);
		if (tokens->size() == 2) { 
  		  	location += atoi(tokens->at(1).c_str());
		} else {
		  	location = b;
		}

		if (y->return_chinese(a, location) != "") {
			for (unsigned int i = 0; i < y->elements->at(a)->at(location)->size(); i++) {
				y->elements->at(a)->at(location)->at(i)->should_translate = 0;
			}
		}
	}
	return b;
}
int Code::possessive(Text *y, std::string h, int a, int b, int c) {

	std::string header = "";
	int location = b;
	int success = 0;

	while (h.find("<POSSESSIVE") != std::string::npos) {
		location = b;
		header = h.substr(h.find("<POSSESSIVE")+1,  h.find(">")-1);
		h = h.substr(h.find(header)+header.length()+1);

		tokenize(header);
		if (tokens->size() == 2) { 
  		  	location += atoi(tokens->at(1).c_str());
		} else {
		  	location = b;
		}

		if (y->return_chinese(a, location) != "") {
			for (unsigned int i = 0; i < y->elements->at(a)->at(location)->size(); i++) {
				y->elements->at(a)->at(location)->at(i)->possessive = 1;
			}
		}
	}
	return b;
}
int Code::switch_units(Text *y, std::string h, int a, int b, int c) {

	std::string header = "";

	int location_1 = b;
	int location_2 = b;

	int success = -1;

	while (h.find("<SWITCH ") != std::string::npos) {

		location_1 = b;
		location_2 = b;

		header = h.substr(h.find("<SWITCH ")+1,  h.find(">")-1);
		h = h.substr(h.find(header)+header.length()+1);

		tokenize(header);

		if (tokens->size() == 3) { 
			location_1 += atoi(tokens->at(1).c_str());
			location_2 += atoi(tokens->at(2).c_str());
		} else { return -1; }

		y->switch_units(a, location_1, location_2);
		success = b;
	}
	if (success > -1) { return success; }
	return -1;
}


int Code::insert(Text *y, std::string h, int a, int b, int c) {

	std::string header = "";
	std::string classtocreate = "";

	int location = b;
	int word_run = 1;
	int success = -1;

	while (h.find("<INSERT ") != std::string::npos) {
		location = b;
		header = h.substr(    h.find("<INSERT ")+1,     h.find(">",     h.find("<INSERT "))-h.find("<INSERT ")-1     );
		h = h.substr(h.find(header)+header.length()+1);


		tokenize(header);
		if (tokens->size() == 2) { classtocreate = tokens->at(1);
		} else {
			if (tokens->size() == 3) {
				word_run = atoi(tokens->at(1).c_str());
				classtocreate = tokens->at(2);
			} else { 
				if (tokens->size() == 4) {
					location += atoi(tokens->at(1).c_str());
					word_run = atoi(tokens->at(2).c_str());
					classtocreate = tokens->at(3);
				} else { return -1; }
			} 
		}


		// We know what to call this element, our insertion position, and its length
		Text *n = new Text(y);

		// Rather than REPLACE Text, just insert a new entry
		if (word_run == 0) {
			n->myclass = classtocreate;
			std::vector<Text *> *temp2 = new std::vector<Text *>;
			y->elements->at(a)->insert(y->elements->at(a)->begin()+location,1,temp2);
			y->elements->at(a)->at(location)->push_back(n);
			success = location;
		} else {

			// Clone the Original Text
			if (y->elements->at(a)->size() > location) {
				for (int i = 0; i < word_run; i++) {
					y->elements->at(a)->at(location+i)->at(0)->append_clone_values(n);
				}
				for (int i = 1; i < word_run; i++) {
					y->remove_element(a, location+1);
					y->make_only(a, location, n);
				}
			}
			n->myclass = classtocreate;
			y->elements->at(a)->at(location)->push_back(n);
			success = location;
		}
	}
	if (success > -1) { return success; }
	return -1;
}
int Code::set(Text *y, std::string h, int a, int b, int c) {

	std::string header = "";
	std::string body = "";
	std::string closer = "";

	std::string category = "all";
	std::string field_to_set = "";
	int location = b;


	int success = -1;

	while (h.find("<SET ") != std::string::npos) {
		header = h.substr(    h.find("<SET ")+1,     h.find(">",     h.find("<SET "))-h.find("<SET ")-1     );
		h = h.substr(h.find(header)+header.length()+1);

		body = h.substr(0,h.find("<"));
		h = h.substr(h.find(body)+body.length());

		closer = h.substr(0, h.find(">"));
		h = h.substr(h.find(closer)+closer.length()+1);
		
		location = b;

		tokenize(header);
		if (tokens->size() == 2) { 
			field_to_set = tokens->at(1);
			category = "me";
		} else {
			if (tokens->size() == 3) {
				category = tokens->at(1);
				field_to_set = tokens->at(2);
			} else { 
				if (tokens->size() == 4) {
					location += atoi(tokens->at(1).c_str());
					category = tokens->at(2);
					field_to_set = tokens->at(3);
				} else { return -1; }
			} 
		} 

		if (y->elements->at(a)->size() > location && location >= 0) {
			if (category == "all") {
				for (int i = 0; i < y->elements->at(a)->at(location)->size(); i++) {
					set_helper(y, a, location, i, field_to_set, body); 
					success = location;
				}
			} else {
				if (category == "me") {
					for (int i = 0; i < y->elements->at(a)->at(location)->size(); i++) {
						if (y->elements->at(a)->at(location)->at(i)->myclass.find(y->elements->at(a)->at(b)->at(c)->myclass) != std::string::npos) {
							set_helper(y, a, location, i, field_to_set, body);
							success = location;
						}
					}
				} else {
					for (int i = 0; i < y->elements->at(a)->at(location)->size(); i++) {
						if (y->elements->at(a)->at(location)->at(i)->myclass.find(category) != std::string::npos) {
							set_helper(y, a, location, i, field_to_set, body);
							success = location;
						}
					}

				}
			}
			
		}
	}
	if (success > -1) { return success; }
	return -1;
}
void Code::set_helper(Text *y, int a, int b, int c, std::string field, std::string new_value) {

	if (field == "english") { y->elements->at(a)->at(b)->at(c)->set_english(new_value); }
	if (field == "pinyin") { y->elements->at(a)->at(b)->at(c)->set_pinyin(new_value); }
	if (field == "myclass") { y->elements->at(a)->at(b)->at(c)->set_myclass(new_value); }
	if (field == "chinese") { y->elements->at(a)->at(b)->at(c)->set_chinese(new_value); }
	if (field == "chinese_utf8s") { y->elements->at(a)->at(b)->at(c)->set_chinese_utf8s(new_value); }
	if (field == "chinese_utf8c") { y->elements->at(a)->at(b)->at(c)->set_chinese_utf8c(new_value); }

	return;
}


