<?php

  // Connect to the Database
  $start = 1;
  $vrun = 20; 
  $total = 7000;

  $includes = "";
  $instantiation = "";  
  $function_interior = "";
  $declaration = "";
  for ($file = 1, $y = $start; $y < $total; $y+=$vrun, $file++) {

    $filetag = "db" . $file;
    $classtag = "Db" . $file;
    $includes .= "#include \"db" . $file . ".h\"\n";
    $declaration .= "$classtag *$filetag" . ";\n";
    $instantiation .= "$filetag = new $classtag" . "();\n";
    for ($m = $y; $m < $y+$vrun; $m++) {
      $function_interior .= "\t" . "if (x == " . $m . ") { return db" . $file . "->table_" . $m . "; };\n";
    }
  }


//  echo $includes . "\n\n";
//  echo $declaration;
//  echo "\n\n\n";
//  echo $instantiation;
//  echo "\n\n\n";
//  echo $function_interior;

?>

#ifndef COMPILED_DATABASE_H
#define COMPILED_DATABASE_H

#include <string>

<?php echo $includes; ?>

class Compiled_Database {

	public:

	Compiled_Database();
	~Compiled_Database();

	int search_index_gb2312(std::string x);
	int search_index_utf8s(std::string x);
	void * return_table(int x);


<?php echo $declaration; ?>

};

#endif
