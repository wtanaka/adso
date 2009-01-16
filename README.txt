David Lancashire
david.lancashire@gmail.com
http://www.adsotrans.com
--------------------------

Adso is a semantic analysis engine for Chinese text. It provides:

* intelligent word segmentation
* intelligent hanzi to pinyin conversion
* Chinese-English gist translation
* document preprocessing for search/clustering/etc.
* semantic REGEXP

Adso is designed so that additional rules can be provided to the engine through external rulesets. The software comes with a default set of grammar rules: if you spot an error or missegmentation, please email us so that we can fix it. Missing entries can be added through our dictionary interface (http://www.adsotrans.com or http://dict.chinesepod.com) as well. We require contributors to provide us with joint copyright over contributions to our database, but respect the rights of major contributors to release materials under alternate licenses if desired (contact us for details). All contributions and edits are reviewed more or less monthly for quality control purposes.

If you see a general grammatical rule Adso does not support, or a word that is routinely translated incorrectly in a very specific context, we can fix it. Please provide:

* a description of the unsupported grammatical rule
* at least one sample sentence illustrating the rule (UTF-8 or GB2312) 

The remainder of this document is a basic introduction to getting Adso up-and-running. It is not a full tutorial, but should be enough to get you started. If you are interested in text pre-processing for use with GIZA++ or Moses, see our guidelines for integrating Adso with SMT software packages in the docs directory of this distribution. For help using the system, or to get involved with our project or dictionary development, contact David Lancashire at david.lancashire@gmail.com.




COMPILATION:

Adso can be compiled with an internal database, or it can connect to MySQL for its data. The advantages of compiling the dictionary explicitly into the software are that the binary operates quite quickly once it has been loaded into memory (it is slow the first time). The disadvantage is that it is impossible to make changes to the database. If you are a developer you should probably compile the software to connect to MySQL. Under Linux, you can switch between these two compile methods by running the script

./prepare_internal

or

./prepare_mysql

These scripts will prepare the source code for compilation. Once done simply type "make". This will create the binary "adso". If you are running the standalone version you are done. If you are running the version that compiles against MySQL, you will need to install the database. Create a MySQL database named "expanded" and install the database file located in the database directory in it. Make sure the user "adso" has access using the password "adso". Instructions are available in the database directory in the file INSTALL.txt

Under Windows: Microsoft does not make it easy to distribute free software. We distribute a pre-compiled version of the binary as we find time to generate it. Our windows distributions are also quite slow as the easiest way to produce this software is to compile under Cygwin rather than VC++. As this requires us to use the stand-alone version of the software, the code is also slow the first time it is run.




BASICS COMMANDS:

Adso is a command-line program. There is no graphical user interface as of yet. To ensure the program works go to the directory where you unpacked the program and run this from the command line.

./adso --help

Adso should print out a list of basic commands which should be enough to get you started. Here are some examples of how to string them together depending on what sort of output you need:

Echo Input:
./adso -f test.gb2312 -cn

Hanzi-to-Pinyin Conversion:
./adso -f test.gb2312 -y

Encoding Analysis:
./adso -f test.gb2312 --rcode --rscript

Encoding Conversion:
./adso -f test.gb2312 -ie gb2312 -oe utf8 -cn

Encoding and Script Conversion:
./adso -f test.gb2312 -ie gb2312 -oe utf8 -is simplified -os traditional -cn

Note: Unless the input encoding is specified manually, Adso tries to guess it. If the input file is in UTF-8, Adso will also analyse the text to determine if it is in simplified or traditional Chinese. If you run into encoding issues analysing small chunks of texts of documents that contain mostly ASCII, you should be able to fix any problems by specifying your encoding/script manually on the command line.



ADVANCED COMMANDS:

Want to build a machine translation system? Adso can also output English text. It's default performance looks like this:

./adso -f test.gb2312 -t

Not terribly impressive, although it's worth noting that the engine has correctly identified and translated the names, dates and numbers in the document. This default performance is deliberately conservative: for better output we have to feed Adso a ruleset that specifies what transformations to perform on the text. These rules are written in XML. They can either be stored in the collective database, or put in a separate file. To see the XML in action, run the following:

./adso -f test.gb2312 -g grammar/translate.grammar --code -t

The results are much better. The "--code" flag tells the system use the rulesets defined in the Adso database. Adding "-g grammar/translate.grammar" adds any rulesets defined in the file "translate.grammar" in our subdirectory for storing common rulesets. You can open that file and edit it anytime you want. In addition to the flexibility this approach gives us in developing new rules for machine translation, we store the rulesets outside the source code to make Adso faster and more flexible. If you have a need for relatively simple text-analysis, like content extraction or document classification, you probably don't need the overhead of a robust translation engine. In some cases, you might just need a single XML command. The following command identifies and prints all of the proper names in the supplied document:

./adso -f [document] --extra-code "<IF><CLASS ProperNoun></IF><THEN><PRINT chinese><PRINT newline></THEN>"

XML commands can be combined for more sophisticated parsing:

./adso -f [document] --extra-code "<IF><CLASS ProperNoun> AND <CLASS 2 Comma></IF><THEN></THEN>"

Control the logic of execution by adding parentheses:

./adso -f [document] --extra-code "<IF>(<CLASS ProperNoun> AND <CLASS 2 Comma>) NOT (<BEGINNING me 1>)</IF><THEN></THEN>"

Or pipe commands for fancy "action-at-a-distance" processing. This will tag all dates found after proper nouns with the Tag provided. You can see that the entries was properly tagged by running Adso with the debug "-d" flag set:

./adso -f [document] --extra-code "<IF><CLASS ProperNoun> AND <NEXTLOOP me 1>Date</NEXTLOOP></IF><THEN><TAG I-was-found-somewhere-after-a-proper-noun> | <NEXTLOOP me 1>Date</LASTLOOP></THEN>"

Two things worth noting. First of all, if you don't use <IF></IF><THEN></THEN> tags, all XML commands will be executed for every word. Secondly, if you are developing XML rulesets the debug flag ("-d") is your best friend. This will print out the text as Adso understands it along with the various class tags associated with each definition. The power of Adso lies in its ability to create and manipulate these arbitrary tags:




A BRIEF INTRODUCTION to the Adso-Markup Language:

Adso works by segmenting text into sentences and words. Words can have multiple parts of speech, and each part of speech can have multiple translations. Our XML commands provide a way to interact with words and help influence which is chosen. Generally, there are three major classes of commands:

  (1) Descriptive - tests whether a condition is true or false.
  (2) Confidence-Building - adjusts our confidence in the selection of a particular entry based on the truth of the XML statement.
  (3) Action - prints results, manipulates definitions, takes action!

All XML commands are executed by all of the potential entries in a text. If the condition they assert is correct they return the location of the unit queries. They return "-1" otherwise. Combined with boolean logic and conditional execution, this provides the basis for the creation of complex rules for text manipulation, as well as funky XML-piping.

Please note that all of these commands are works in progress. We're working on building more complex rulesets that handle mainstream text analysis. The best way to get involved is to start analysing Chinese text and look for patterns that are consistently mis-translated (or which can be improved upon). Identifying missing words or phrases and adding them to the dictionary is another critical way to improve system performance (just be sure to tag phrases with the part-of-speech PHRASE). 



Descriptive:

These XML commands do alter the document:

<CLASS [relative_location] Class>
- is there class "Class" at location "relative_location". The [relative_location] here is an integer which refers to the position of the word relative to the work executing the XML. 1 references the following word, while -1 references the previous word. 0 would be the current word. <CLASS Noun> is the same as <CLASS 0 Noun>.

<NOTCLASS [relative_location] Class>
- The opposite of CLASS.

<CHINESE [relative_location] Class>
- The same as CLASS, except that we're searching for a particular Chinese word instead of a semantic or grammatical class. The word must be supplied in the GB2312 encoding.

<LENGTH gt [number]>
<LENGTH ls [number]>
<LENGTH is [number]>
- is the value of the number at this location "greater than", "less than" or "is" the [number] provided.



Confidence-Building:

These XML commands have the potential to affect the "confidence" value assigned to any particular entry. The engine will process elements and adjust their confidence value by the amount of the "benefit" specified if the XML condition holds true. 

<BEGINNING [category] benefit>
- Adjusts the benefit to the stated category if this entry is at the beginning of a sentence. You can write "me" instead of the category name if you only want the benefit to apply to one particular entry (such as a specific translation).

<ENDING [category] benefit>
- Adjusts the benefit to the stated category if this entry is at the end of a sentence. You can write "me" instead of the category name if you only want the benefit to apply to one particular entry (such as a specific translation).

<SUBCLAUSE [category] benefit>
- Adjusts the benefit to the stated category if this entry is in a subclause or complex sentence. You can write "me" instead of the category name if you only want the benefit to apply to one particular entry (such as a specific translation).

<NEXT [category] [relative_location] [benefit]>Noun Verb Xing ProperNoun</NEXT>
- applies [benefit] to [category] at this location if any of the part-of-speech classes are found at relative location [relative-location]

<NEXTWORD [category] [relative_location] [benefit]>....</NEXTWORD>
- applies [benefit] to [category] at this location if any of the chinese words (GB2312) specified within the two tags are found at relative location [relative-location]

<NEXTLOOP [category] [benefit]>Noun Verb Xing ProperNoun</NEXTLOOP>
- the same as NEXT, except loops forward to the end of the sentence checking all of the possible entries

<NEXTWORDLOOP [category] [benefit]>....</NEXTWORDLOOP>
- the same as NEXTWORD, except loops forward to the end of the sentence checking all of the possible entries

<NEXTWORDEXACT [category] [benefit]>....</NEXTWORDEXACT>
- the same as NEXTWORD, except that a partial match will not return positive.

<LAST...></LAST>
<LASTWORD...></LAST>
<LASTWORDLOOP...></LAST>
<LASTLOOP...></LAST>
<LASTWORDEXACT...></LAST>
- these entries mirror NEXT in format and function, except that they search backwards.


<MATCH [category] [benefit]>Chinese words go here space segmented</MATCH>
- if any of the words provided (GB2312) are found in the sentence, [category] is assigned [benefit]

<TEXTMATCH [category] [benefit]>Chinese words go here space segmented</TEXTMATCH>
- like MATCH, except that the entire document submitted for analysis is searched, not just the current sentence.

<BONUS [category] [relative_location] [benefit]>
- adds a bonus of [benefit] to the entry [category] at the relative location of [relative_location].

<BOOST [category] [relative_location] [benefit]>
- same as bonus. here for legacy support.


Note: all of these commands return 1 if successful. This means that the command <CLASS 1 Noun> and the command <NEXT Noun 1 0> are identical. Both will return 1 if the entry that follows is a Noun.



Action:

<POSTTEXT [category] [location]>car</POSTTEXT>
- adds the english text supplied after all entries [catgory] at relative location [location]. You can use "all" and "me" for category names.

<PRETEXT [category] [location]>car</PRETEXT>
- adds the english text supplied before all entries [catgory] at relative location [location] You can use "all" and "me" for category names.

<TAG [location] [new_category]>
- add the new class tag [new_class] to all entries at relative_location [location]

<PRINT [x]>
- prints [x]. You get expected results by replacing [x] with "chinese", "chinese_utf8s", "chinese_utf8c", "pinyin", "english", "newline"


RESEGMENT:
 There are two forms for this command. The first can be used in IF/THEN commands. The second has built-in conditional support:
  (1) <RESEGMENT [char]>
	- resegments the current word after character number [char].
  (1) <RESEGMENT [char]>... XML code ...</RESEGMENT>
	- resegments the current word after character number [char] ONLY if the nested XML code returns positive. An example;
		- <RESEGMENT 1><NEXT me 1>Measure</NEXT></RESEGMENT>
		- resegments the current word after the first character if the next word is a Measure Word


MAKE_ONLY:
 There are two forms for this command. The first can be used in IF/THEN commands. The second has built-in conditional support:
  (1) <MAKE_ONLY [location] [category>
	- reduces all entries at the relative location of [location] to the provided category. If the category is "me", all other entries are deleted. The LAST entry will not be deleted unless the category is "all", in which case the word is fully stripped.
  (1) <MAKE_ONLY [category]>... XML code ...</MAKE_ONLY>
	- works the same as above, but only resegments if the nested XML code returns positive. An example;
		- <MAKE_ONLY 1 Adverb><NEXT 2 1>Verb</NEXT></MAKE_ONLY>
		- makes the next entry an Adverb if the second next entry is a verb.

<DELETE [category] [location]> 
  -- deletes [category] at relative location [location]. Will not delete EVERYTHING at any location unless "all" is provided as the "category". This is to prevent accidentally deleting the only definition for a word that exists. <DELETE all> will remove a word completely from the text.


<SWITCH int a, int b> 
- switches the two words, useful for reordering entries for smoother translation


<TENSE int location, int tense>
- sets the tense of verbs at relative location [location]

<SET [location] [category] [field_to_set]>new value</SET>
- sets the value of the fields in entries of class [category] at relative location [location]. ie:
  <SET 1 Measure english>bunch</SET>
  - sets the english of the following measure word to "bunch"


<INSERT [location] [word_run] [new_class]>
- creates a new word and names it [new_class]. The word starts at relative location [location] and runs [word_run] number of words. The chinese, english and pinyin values are all copied over from their existing words. ie:
  <IF><CLASS Person> AND <CLASS 1 Date> AND <BEGINNING me 1></IF><THEN><INSERT 0 3 Unit:SentenceBeginning01></THEN>
- if word_run is zero, Adso will insert a new word into the specified location. This new word can then be manipulated by the standard teags.

<NOTTRANSLATE [relative_location]>
- don't output any english for the word at relative location [relative_location]

<REDUCE>
- picks the most likely translation for any entry and deletes the rest.


SUPPORTED CLASSES/POS:

This is a rough list of the classes/parts-of-speech supported by the software. There were somewhere over 100 classes in the last version of the software and we are slowly implementing them in this version. Run Adso is debugging mode for details on how it classifies any particular text. We will adjust categories or add them to the software as possible. If you know of a grammar class we should/can support, let us know.

Unit:Noun
Unit:ProperNoun
Unit:ProperNoun:Country
Unit:ProperNoun:Person
Unit:ProperNoun:Organization
Unit:Date:Day
Unit:Date:Month
Unit:Date:Year
Unit:Number
Unit:Number:Range
Unit:Adjective 
  - NOTE: this category covers adjectival noun compoud headers 
  (ie. definitions that are commonly paired with nouns in compound
  form). What are conventionally considered "adjectives" in the 
  English language are classified by the system as Xingrongci 
  (ie. Xing). Compound elements containing Xing may be considered 
  Adjectives in terms of their functionally in Chinese grammar. For 
  algorithmic purposes, this category can be considered a low-confidence
  form of Xingrongci.
Unit:Xing
Unit:Auxiliary
Unit:Adverb
Unit:Verb
Unit:Punctuation
Unit:NonChinese
Unit:Special
Unit:Phonetic
Unit:Name

There are more. Run Adso in debugging mode "-d" for details, and don't forget that you can tag entries yourself using the TAG and INSERT commands.

