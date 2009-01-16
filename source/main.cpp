#include <iostream>
#include <string>
#include <cstdlib>
#include <cstring>
#include <vector>
#include <fstream>


#include "unit.h"
#include "text.h"
#include "code.h"
#include "adso.h"
#include "feedback.h"
#include "encoding.h"
#include "memory.h"
#include "polisher.h"
#include "parser.h"
#include "ontology.h"

#define USE_MYSQL 1
//#define USE_COMPILED 1
//#define USE_SQLITE 1

int run_code = 0;
int translate = 0;
int chinese = 0;
int pinyin = 0;
int popup = 0;
int jyutpin = 0;
int debug = 0;
int rcode = 0;
int rscript = 0;
int inlinetext = 0;
int conjugate = 0;
int g1 = 1;
int g2 = 0;
int html_entities = 0;
int freq_count = 0;
int freq_reset = 0;
int segcn = 0;
int vocab = 0;
int trad_vocab = 0;
int parse_textbook_markup = 0;
int editable = 0;
int editable_five_fields = 0;
int unknown_popup = 0;
int tonalize_pinyin = 0;
int full_definitions = 0;
int update_markup = 0;

int skip_stage_pre_unify = 0;
int skip_stage_unify = 0;
int skip_stage_post_unify = 0;
int skip_stage_adjust_confidence = 0;
int skip_stage_combine1 = 0;
int skip_stage_combine2 = 0;
int skip_stage_advanced = 0;

int switch_script = 0;

std::string ontology_name = "";
std::string ontology_filename = "";

std::string inline_text = "";
std::string inline_text_existing = "";
std::string inline_text_new = "";
std::string extra_code = "";
std::string extra_code_non_recursive = "";
std::vector<std::string> grammar_code;

std::string dbusername = "adso";
std::string dbpassword = "adso";
std::string dbdatabase = "expanded";

void help();
void copyright();
int process_grammar_file(std::string filename, Code *mycode);
std::string open_file(std::string filename);
std::string process(std::string x, Text *t, Ontology *ont);
void compare_and_update(Text *original, Text *newtext);




int process_grammar_file(std::string grammar_file, Code *mycode) {

	try {
		std::string line = "";
		std::ifstream file2parse(grammar_file.c_str());  
		while (!std::getline(file2parse, line).eof() && file2parse.fail() == 0) { 
			if (line.length() > 0) {
				if (line[0] == '@') {
					process_grammar_file(line.substr(1), mycode);
				} else {
					if (line[0] != '#') {
						if (line.find("DEFINE_COMPOUND") != std::string::npos) {
							void *x;
							mycode->define_compound((Text *)x,line,0,0,0);
						} else {
							grammar_code.push_back(line);
						}
					}
				}
			}
		};
	} catch (...) {	std::cout << "Error reading grammar file: " << grammar_file << std::endl; exit(1); }

	return 1;
}


int main(int argc, char **argv) {



	// Look for Database Connectio nInfo 
	for (int z = 1; z < argc; z++) {

		if (strcmp(argv[z], "--db-user") == 0) { if (argc-1 > z) { dbusername = argv[z+1]; z++; } else { help(); exit(0); } }
		if (strcmp(argv[z], "--db-pass") == 0) { if (argc-1 > z) { dbpassword = argv[z+1]; z++; } else { help(); exit(0); } }
		if (strcmp(argv[z], "--db") == 0) { if (argc-1 > z) { dbdatabase = argv[z+1]; z++; } else { help(); exit(0); } }

	}




	// Initialize Variables
	Adso *adso = new Adso(dbusername, dbpassword, dbdatabase);
	Code *code = new Code();
	Encoding *encoding = new Encoding();
	Feedback *feedback = new Feedback();
	Memory *memory = new Memory();
	Ontology *ontology = new Ontology();
	Parser *parser = new Parser();
	Polisher *polisher = new Polisher();


	Text *text = new Text(adso, code, encoding, feedback, memory, ontology, parser, polisher);

	std::string infile = "";


	// Command Line Arguments
	for (int z = 1; z < argc; z++) {

		/* Help */
		if (strcmp(argv[z], "--help") == 0) { help(); exit(0); }

		/* Copyright */
		if (strcmp(argv[z], "--copyright") == 0) { copyright(); exit(0); }
		if (strcmp(argv[z], "-c") == 0) { copyright(); exit(0); }
		if (strcmp(argv[z], "--version") == 0) { copyright(); exit(0); }
		if (strcmp(argv[z], "--license") == 0) { copyright(); exit(0); }


		/* Stage Skipping */
		if (strcmp(argv[z], "--skip-stage-pre-unify") == 0) { skip_stage_pre_unify = 1; }
		if (strcmp(argv[z], "--skip-stage-unify") == 0) { skip_stage_unify = 1; }
		if (strcmp(argv[z], "--skip-stage-post-unify") == 0) { skip_stage_post_unify = 1; }
		if (strcmp(argv[z], "--skip-stage-adjust-confidence") == 0) { skip_stage_adjust_confidence = 1; }
		if (strcmp(argv[z], "--skip-stage-combine1") == 0) { skip_stage_combine1 = 1; }
		if (strcmp(argv[z], "--skip-stage-combine2") == 0) { skip_stage_combine2 = 1; }
		if (strcmp(argv[z], "--skip-stage-advanced") == 0) { skip_stage_advanced = 1; }
		if (strcmp(argv[z], "--skip-basic") == 0)  { skip_stage_pre_unify = 1; skip_stage_unify = 1; skip_stage_post_unify = 1; }
		if (strcmp(argv[z], "--skip-advanced") == 0)  { skip_stage_adjust_confidence = 1; skip_stage_combine1 = 1; skip_stage_combine2 = 1; skip_stage_advanced = 1; }

		if (strcmp(argv[z], "-v") == 0) { memory->verb_conjugation = 1; }
		if (strcmp(argv[z], "--ucp") == 0) { text->asciify_punctuation = 1; }
		if (strcmp(argv[z], "--conjugation") == 0) { memory->verb_conjugation = 1; }
		if (strcmp(argv[z], "--html-entities") == 0) { html_entities = 1; }
		if (strcmp(argv[z], "--switch-script") == 0) { switch_script = 1; }

		/* Input File */
		if (strcmp(argv[z], "-f") == 0) { if (argc-1 > z) { infile = argv[z+1]; z++; } else { help(); exit(0); } }

		/* Ontologies */
		if (strcmp(argv[z], "--ontology") == 0) { if (argc-1 > z+1) { ontology_name = argv[z+1]; ontology_filename = argv[z+2]; z+=2; int c = ontology->add_ontology(ontology_name, ontology_filename); } else { help(); exit(0); } }

                /* Stopwords */
                if (strcmp(argv[z], "--stoplist") == 0) { if (argc > z+1) { ontology_name = "STOPWORD"; ontology_filename = argv[z+1]; int c = ontology->add_ontology(ontology_name, ontology_filename); extra_code = "<REDUCE><IF><NOTCLASS STOPWORD></IF><THEN><PRINT chinese_utf8s><PRINT  ></THEN>";} else { help(); exit(0); } }


		/* Inline */
		if (strcmp(argv[z], "-i") == 0) { if (argc-1 > z) { inlinetext = 1; inline_text = argv[z+1]; z++; } else { help(); exit(0); } }

		/* Compare and Update */
		if (strcmp(argv[z], "--merge") == 0) { if (argc-1 > z) { update_markup = 1; inline_text_existing = argv[z+1]; inline_text_new= argv[z+2]; z+=2; } else { help(); exit(0); } }

		/* Run Code */
		if (strcmp(argv[z], "--code") == 0) { run_code = 1; }

		/* Segment Chinese Only */
		if (strcmp(argv[z], "--segcn") == 0) { segcn = 1; }

		/* Segment Chinese Only */
		if (strcmp(argv[z], "--tonalize") == 0) { tonalize_pinyin = 1; }

                /* Split ASCII on punctuation */
                if (strcmp(argv[z], "--split-ascii-punctuation") == 0) { text->split_nonchinese_on_punctuation = 1; }

		/* Vocab */
		if (strcmp(argv[z], "--vocab") == 0) { vocab = 1; }
		if (strcmp(argv[z], "--trad-vocab") == 0) { trad_vocab = 1; }

		/* Vocab */
		if (strcmp(argv[z], "--textbook-markup") == 0) { parse_textbook_markup = 1; }

		/* Frequency Count */
		if (strcmp(argv[z], "--frequency") == 0) { freq_count = 1; }

		/* All Definitions */
		if (strcmp(argv[z], "--full") == 0) { full_definitions = 1; text->full_definitions = 1; }

		/* Frequency Reset */
		if (strcmp(argv[z], "--frequency-reset") == 0) { freq_reset = 1; }

		/* No Phrases */
		if (strcmp(argv[z], "--no-phrases") == 0) { adso->no_phrases = 1; parser->no_phrases = 1; }

		/* Grammar */
		if (strcmp(argv[z], "-g") == 0 || strcmp(argv[z], "-g1") == 0 || strcmp(argv[z], "-g2") == 0) { 
			if (strcmp(argv[z], "-g2") == 0) { g1 = 0; g2 = 1; }
			if (strcmp(argv[z], "-g") == 0) { g1 = 1; }
			if (strcmp(argv[z], "-g1") == 0) { g1 = 1; }
			if (argc-1 > z) { 
				std::string grammar_file = argv[z+1];
				process_grammar_file(grammar_file, code);
			}
			std::string line = "";
		}


		/* Run Extra Code */
		if (strcmp(argv[z], "--extra-code") == 0) { if (argc-1 > z) { extra_code = argv[z+1]; z++; } else { help(); exit(0); } }

		/* Run Extra Code */
		if (strcmp(argv[z], "--extra-code-non-recursive") == 0) { if (argc-1 > z) { extra_code_non_recursive = argv[z+1]; z++; } else { help(); exit(0); } }

		/* Basic Output Options */
		if (strcmp(argv[z], "-t") == 0) { translate = 1; }
		if (strcmp(argv[z], "-cn") == 0) { chinese = 1; }
		if (strcmp(argv[z], "-y") == 0) { pinyin = 1; }
		if (strcmp(argv[z], "-j") == 0) { jyutpin = 1; }
		if (strcmp(argv[z], "--pinyin") == 0) { pinyin = 1; }
		if (strcmp(argv[z], "--jyutpin") == 0) { jyutpin = 1; }
		if (strcmp(argv[z], "--unknown-popup") == 0) { unknown_popup = 1; }
		if (strcmp(argv[z], "--popup") == 0) { popup = 1; encoding->output_encoding = 2; }
		if (strcmp(argv[z], "--editable-five-fields") == 0) { editable_five_fields = 1; encoding->input_encoding = 2; encoding->output_encoding = 2; }
		if (strcmp(argv[z], "--editable") == 0) { editable = 1; encoding->output_encoding = 2; }
		if (strcmp(argv[z], "--textbook") == 0) { popup = 1; encoding->output_encoding = 2; }
		if (strcmp(argv[z], "-d") == 0) { debug = 1; }
		if (strcmp(argv[z], "--debug") == 0) { debug = 1; }
		if (strcmp(argv[z], "--rscript") == 0) { rscript = 1; }
		if (strcmp(argv[z], "--rcode") == 0) { rcode = 1; }





                /* Input/Output Encodings and Scripts */
                if (strcmp(argv[z], "-ie") == 0) {
                        if (argc-1 > z) {
                                if (strcmp(argv[z+1], "gb2312") ==0) { encoding->input_encoding = 1; encoding->input_script = 1; encoding->output_encoding = 1; if (encoding->output_script == 0) { encoding->output_script = 1; }  };
                                if (strcmp(argv[z+1], "utf8") ==0) { encoding->input_encoding = 2; encoding->input_script = 1; encoding->output_encoding = 2; if (encoding->output_encoding == 0) { encoding->output_script = 1; }; };
                                if (strcmp(argv[z+1], "markup") ==0) { parse_textbook_markup = 1; };
                                if (strcmp(argv[z+1], "js") ==0) { parse_textbook_markup = 1; };
                                z++;
                        } else { help(); exit(0); }
                }
                if (strcmp(argv[z], "-oe") == 0) {
                        if (argc-1 > z) {
                                if (strcmp(argv[z+1], "gb2312") ==0) { encoding->output_encoding = 1; if (encoding->output_script == 0) { encoding->output_script = 1; }; };
                                if (strcmp(argv[z+1], "utf8") ==0) { encoding->output_encoding = 2; if (encoding->output_script == 0) { encoding->output_script = 1; }; };
                                z++;
                        } else { help(); exit(0); }
                }
                if (strcmp(argv[z], "-is") == 0) {
                        if (argc-1 > z) {
                                if (strcmp(argv[z+1], "simplified") ==0) { encoding->input_script = 1; encoding->output_script = 1; };
                                if (strcmp(argv[z+1], "traditional") ==0) { encoding->input_script = 2; encoding->output_script = 2; };
                                if (strcmp(argv[z+1], "complex") ==0) { encoding->input_script = 2; encoding->output_script = 2; };
                                z++;
                        } else { help(); exit(0); }
                }
                if (strcmp(argv[z], "-os") == 0) {
                        if (argc-1 > z) {
                                if (strcmp(argv[z+1], "simplified") ==0) { encoding->output_script = 1; };
                                if (strcmp(argv[z+1], "traditional") ==0) { encoding->output_script = 2; };
                                if (strcmp(argv[z+1], "complex") ==0) { encoding->output_script = 2; };
                                z++;
                        } else { help(); exit(0); }
                }
        }




	// Connect to the Database
        #ifdef USE_MYSQL
  	  adso->connect();
	  adso->query_string("set names latin1");
//	  adso->connect_verbs();
        #endif
        #ifdef USE_SQLITE
  	  adso->connect();
	  adso->query_string("set names latin1");
	  adso->connect_verbs();
        #endif



	// Handle User Input
	try {
		std::string str = "";
		if (infile != "") {

			str = process(open_file(infile), text, ontology);		
			str = polisher->return_polished_english(str);
			if (tonalize_pinyin == 1) {
				str = polisher->convert_pinyin(str);
			}
			
			if (str != "") { std::cout << str << std::endl; }
		} else {

			/* Compare and Update Existing Markup */
			if (update_markup == 1) {

				Text *text2 = new Text(adso, code, encoding, feedback, memory, ontology, parser, polisher);
				void *xx;			

         		       	text->init_markup(inline_text_existing);

                		text2->init_text(inline_text_new);
				text2->pre_unify((Text *) xx);
				text2->unify((Text *) xx);
				text2->post_unify((Text *) xx);
	
				compare_and_update(text,text2);
				
				std::cout << text->return_popup_for_editing_five_fields(1) << std::endl;

				delete text2;

			} else {

				if (inlinetext == 1) {
					str = process(inline_text, text, ontology);
					str = polisher->return_polished_english(str);
					if (tonalize_pinyin == 1) {
						str = polisher->convert_pinyin(str);
					}
					if (str != "") { std::cout << str << std::endl; }
				} else {
					std::cout << "Welcome to Adso. Enter Chinese text and it will be processed as per your command-line options. If you are unsure of what to do, type \"quit\" and then type \"./adso --help\" at the command prompt for instructions on using the software\n>";
					std::cout << ">";
					while (std::cin >> str) {
						if (str == "EXIT" || str == "exit" || str == "q" || str == "Q" || str == "quit" || str == "QUIT" || str == "bye" || str == "BYE") { break; }
						str = process(str, text, ontology);
						str = polisher->return_polished_english(str);
						if (tonalize_pinyin == 1) {
							str = polisher->convert_pinyin(str);
						}
						if (str != "") { std::cout << str << std::endl; }
						std::cout << ">";
					}
				}
			} // comparison if
		}
	} 
	catch (char *x) { std::cout << "Error: " << x; }
	catch (std::string x) { std::cout << "Error: " << x; }
	catch (...) { std::cout << "Unknown Error Caught!\n"; }


	// Frequency Reset as Needed
	if (freq_reset == 1) { text->frequency_reset(text, adso); }

	// Frequency Count as Needed
	if (freq_count == 1) { text->frequency_count(text, adso); }




	adso->disconnect();
	delete adso;

	delete text;

	delete polisher;
	return 1;
}

void copyright() {

std::cout << " \
\nAdso Chinese Text-Analysis System v5.058: (c) David Lancashire, 2008 \n\
\n\
Chinese translation and text analysis engine. Inquiries welcome: david.lancashire@gmail.com\n";
	return;
}

void help() {

std::cout << " \
\nWelcome to Adso: \n\
\n\
  Basic Commands: \n\
  -f [file]                         input file \n\
  -i [input]                        input text as command-line argument \n\
  -h, --help                        print this reference guide \n\
  -v, --version                     print version \n\
  -c, --copyright                   print copyright \n\
\n\
  Output Methods: \n\
  -cn                               chinese\n\
  -y                                pinyin\n\
  -t                                english\n\
\n\
  Character Encodings: \n\
  -ie [code]                        specify input encoding \n\
  -oe [code]                        specify output encoding \n\
                                    (gb2312, utf8) \n\
  -is [script]                      specify input script \n\
                                    (simplified, traditional, complex) \n\
		                    (no traditional in beta) \n\
  -os [script]                      specify output script \n\
                                    (simplified, traditional, complex) \n\
	     	                    (no traditional in beta) \n\
  --ucp                             asciify Chinese punctuation \n\
  --guess-encoding                  guess file encoding \n\
\n\
  Advanced: \n\
  -d                                debugging mode\n\
  -g [file]                         use grammar file\n\
  --rcode                           report document encoding\n\
  --rscript                         report document script (complex, simplified)\n\
  --ontology [ontology] [file]      tags words matching contents of [file] as members \n\
				    of ontology [ontology]. This provides an easy and \n\
                                    dynamic way to tag specific with specific class \n\
				    titles.\n\
  --html-entitites	            convert html entities to class\n\
  --segcn                           space segmented Chinese\n\
  --tonalize                        convert numeric pinyin to tonal UTF8\n\
  --vocab                           tab-delineated vocabulary list\n\
  --trad-vocab                      tab-delineated vocabulary list (traditional)\n\
  --extra_code [code]               run user-submitted code\n\
  --extra_code_non_recursive [code] run user-submitted code on MAIN text\n\
  --frequency                       update database (mysql only) with frequency information\n\
  --frequency-reset                 reset database frequency data\n\
  --db [database]                   specify database name for connection\n\
  --db-user [username]              specify database username for connection\n\
  --db-pass [password]              specify database password for connection\n\
  --split-ascii-punctuation         don't unify nonchinese across punctuation marks\n\
  --skip-stage-pre-unify            skip pre-unify stage\n\
  --skip-stage-unify                skip unify stage\n\
  --skip-stage-post-unify           skip post-unify stage\n\
  --skip-stage-adjust-confidence    skip adjust-confidence stage\n\
  --skip-stage-combine1             skip combine1 stage\n\
  --skip-stage-combine2             skip combine2 stage\n\
  --skip-stage-advanced             skip advanced stage\n\
  \n\
";
}



// Open Input File
std::string open_file(std::string filename) {

	std::string fulltext = "";

	try {

		int buffer_size = 102;
		int length;
		char buffer[buffer_size];
		std::string str;


		// Read Our File
		std::ifstream INPUT(filename.c_str());
		int loop = 0;
		while (std::getline(INPUT, str)) { 
			if (loop != 0) { 
				fulltext += "\n"; 
			} fulltext += str; loop++; 
		}
		INPUT.close();
	}

	catch (...) {
		throw "Error Opening File!/n";
	}
	return fulltext;
}



/* Compares two strings. Updates the annotation with the machine-annotated version FOLLOWING
 * the first text change. Any edits made prior to that change are preserved.
 */
void compare_and_update(Text *originaltext, Text *newtext) {

  std::string original = originaltext->return_chinese_utf8s();
  std::string revised = newtext->return_chinese_utf8s();
  std::string curword = "";
  std::string already_processed = "";
  
  int loopsize = originaltext->elements->at(0)->size();
  int newtext_size = newtext->elements->at(0)->size();

  for (int z = 0; z < newtext_size; z++) {

    curword = newtext->elements->at(0)->at(z)->at(0)->return_chinese_utf8s();

    if (original.substr(0,curword.length()) == curword) {

      already_processed += original.substr(0,curword.length());
      original = original.substr(curword.length());


      // this happens when revised string is shorter than original and there are no earlier changes
      // forcing us to recognize the change this way and just delete the excessive entries from the 
      // originaltext vector.
      //
      // beware of partial matches to these substringsa
      if (z+1 >= newtext_size) {

	for (int gb = 0, me_total_length = 0; gb < originaltext->elements->at(0)->size(); gb++) {
          me_total_length += originaltext->elements->at(0)->at(gb)->at(0)->return_chinese_utf8s().length();
          if (me_total_length == already_processed.length()) {
            if (gb+1 < originaltext->elements->at(0)->size()) { 
	      gb++; 
              for (int yyy = 0; yyy < originaltext->elements->at(0)->at(gb)->size(); yyy++) {
	        delete originaltext->elements->at(0)->at(gb)->at(yyy);
              }
	      originaltext->elements->at(0)->at(gb)->clear();
	      delete originaltext->elements->at(0)->at(gb);
	      originaltext->elements->at(0)->erase(originaltext->elements->at(0)->begin()+gb);
	    }
	    gb = originaltext->elements->at(0)->size()+1;
          }
          if (me_total_length > already_processed.length()) {

            for (int zzz = gb; zzz < originaltext->elements->at(0)->size(); zzz++) {
              for (int yyy = 0; yyy < originaltext->elements->at(0)->at(zzz)->size(); yyy++) {
	        delete originaltext->elements->at(0)->at(zzz)->at(yyy);
              }
	      originaltext->elements->at(0)->at(zzz)->clear();
	      delete originaltext->elements->at(0)->at(zzz);
	      originaltext->elements->at(0)->erase(originaltext->elements->at(0)->begin()+zzz);
	      zzz--;
           }
           
            Text *newunit   = new Unit(newtext);
            newtext->elements->at(0)->at(z)->at(0)->clone_values(newunit);
            originaltext->elements->at(0)->push_back(new std::vector<Text *>);
            originaltext->elements->at(0)->at(originaltext->elements->at(0)->size()-1)->push_back(newunit);
            gb = originaltext->elements->at(0)->size()+2;
          }
        }
      }

    } else {

      std::string temp = already_processed;
      std::string curword2 = "";
      int resegment_position = 0;
      int resegment_length = 0;
      int deleted_stuff = 0;

      // Move to Current Position in Original Text
      for (int j = 0, contloop = 1; j < loopsize && contloop == 1; j++) {

        curword2 = originaltext->elements->at(0)->at(j)->at(0)->return_chinese_utf8s();

        if (temp.substr(0,curword2.length()) == curword2 && temp != "") {
	  contloop = 1;
	  temp = temp.substr(curword2.length());
          if (temp == "") { 

		// If there are any words left at the end, add them now
		for (int gg = z; gg < newtext_size; gg++) {
            		Text *newunit   = new Unit(newtext);
            		newtext->elements->at(0)->at(gg)->at(0)->clone_values(newunit);
            		originaltext->elements->at(0)->push_back(new std::vector<Text *>);
            		originaltext->elements->at(0)->at(originaltext->elements->at(0)->size()-1)->push_back(newunit);
            		already_processed += newunit->return_chinese_utf8s();
		}

	  }
        } else {

	  for (int zzz = j; zzz < loopsize; zzz++) {
	    for (int bbb = 0; bbb < originaltext->elements->at(0)->at(zzz)->size(); bbb++) {
              delete originaltext->elements->at(0)->at(zzz)->at(bbb);
            }
	    originaltext->elements->at(0)->at(zzz)->clear();
	    delete originaltext->elements->at(0)->at(zzz);
	    originaltext->elements->at(0)->erase(originaltext->elements->at(0)->begin()+zzz);
	    zzz--;
            loopsize--;
            deleted_stuff = 1;
	  }

          contloop = 0;
	  resegment_position = j;


          // Now Add the Restof the Sentence
	  for (int mmm = z, nnn = resegment_position; mmm < newtext->elements->at(0)->size(); mmm++, nnn++) {

            Text *newunit   = new Unit(newtext);
            newtext->elements->at(0)->at(mmm)->at(0)->clone_values(newunit);
            originaltext->elements->at(0)->insert(originaltext->elements->at(0)->begin()+nnn, new std::vector<Text *>);
            originaltext->elements->at(0)->at(nnn)->push_back(newunit);

            already_processed += newunit->return_chinese_utf8s();

          }

        }        
      } // end of else
    }
  }

  return;
}



/* Core Logic of Text Analysis */
std::string process(std::string x, Text *text, Ontology *ontology) {

	Polisher *polisher = new Polisher();

	if (x == "") { return ""; }
	std::string results = "";
	
	if (parse_textbook_markup == 1) {
		text->init_markup(x);
	} else {
		text->init_text(x);
	}

	// Switch Script as Necessary
	if (switch_script == 1) {
          if (text->encoding->input_script == 1) { text->encoding->output_script = 2; } 
          else                                   { text->encoding->output_script = 1; } 
        }



	void *xx;

	// The Basics
	if (skip_stage_pre_unify == 0)         { text->pre_unify((Text *) xx);  }
	if (skip_stage_unify == 0)             { text->unify((Text *) xx);      }
	if (skip_stage_post_unify == 0)        { text->post_unify((Text *) xx); }
	if (skip_stage_adjust_confidence == 0) { text->adjust_confidence((Text *) xx); }


	// Various Entities
	if (html_entities == 1) { text->identify_html_entities((Text *) xx); }

	// XML Stored in Database 
	if (run_code == 1) { text->run_code((Text *) xx); }


	// Identifying More Abstract Combinations
	if (skip_stage_combine1 == 0) { text->combine((Text *) xx); }
	if (skip_stage_combine2 == 0) { text->combine2((Text *) xx); }
	if (skip_stage_advanced == 0) { text->advanced((Text *) xx); }
	if (rscript == 1) { results += text->encoding->report_script(); }
	if (rcode == 1) { results += text->encoding->report_encoding(); }


	// XML Stored in Database 
	if (ontology->ontology_names->size() > 0) { text->map_ontology_to_class((Text *) xx, ontology); }

	
        if (grammar_code.size()>0 && g2 == 1) { text->run_extra_code_bulk(text, grammar_code,0,0,0);}
        if (grammar_code.size()>0 && g1 == 1) { for (int a = 0; a < grammar_code.size(); a++) { text->run_extra_code(text, grammar_code.at(a),0,0,0); } }
	if (extra_code != "") { text->run_extra_code(text, extra_code,0,0,0); }
	if (extra_code_non_recursive != "") { text->run_extra_code_non_recursive(text,extra_code_non_recursive,0,0,0); }
	if (segcn == 1) { results += text->return_segmented_chinese(); }
	if (debug == 1) { results += text->debug(); }
	if (vocab == 1) { results += text->return_vocab_list(); }
	if (trad_vocab == 1) { results += text->return_vocab_list_with_traditional(); }
	text->adjust_spacing((Text *) xx);
	if (translate == 1) { results += text->return_english(); }
	if (popup == 1) { results += text->return_popup(); }
	if (unknown_popup == 1) { 
		if (text->encoding->input_encoding == 1) { results += text->return_gb2312_popup(); } 
		else { results += polisher->convert_pinyin(text->return_popup()); }
	}
	if (editable == 1) { results += text->return_popup_for_editing(1); }
	if (editable_five_fields == 1) { results += text->return_popup_for_editing_five_fields(1); }
	if (pinyin == 1) { results += text->return_pinyin(); }
	if (jyutpin == 1) { results += text->return_jyutpin(); }
	if (chinese == 1) { results += text->return_chinese_output_encoding(); }

	return results;
}	





