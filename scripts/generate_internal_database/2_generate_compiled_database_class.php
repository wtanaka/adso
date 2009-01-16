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
      // escaped with the shift to a new auto-generated database structure - problems should be addressed in the database itself
      // 4966 is empty for some reason, so we skip it to avoid returning an empty table in the program
      //if ($m != 4966) {
        if ($m < 6841) { // our highest character
          $function_interior .= "\t" . "if (x == " . $m . ") { return db" . $file . "->table_" . $m . "; };\n";
        }
      //}
    }
  }


//  echo $includes . "\n\n";
//  echo $declaration;
//  echo "\n\n\n";
//  echo $instantiation;
//  echo "\n\n\n";
//  echo $function_interior;

?>

#include "compiled_database.h"
#include <iostream>
<?php echo $includes; ?>

Compiled_Database::Compiled_Database() {

<?php echo $instantiation ?>

}
Compiled_Database::~Compiled_Database() {}

int Compiled_Database::search_index_gb2312(std::string x) {
  std::string temp = "";
  for (int i = 0;;i++) {
    temp = db1->character_index[i][0];
    if (temp.find("@") != std::string::npos) { break; }
    if (x.compare(db1->character_index[i][1]) == 0) { return atoi(db1->character_index[i][0]); }
  }
  return -1;
}


int Compiled_Database::search_index_utf8s(std::string x) {
  std::string temp = "";
  for (int i = 0;;i++) {
    temp = db1->utf8s_index[i][0];
    if (temp.find("@") != std::string::npos) { break; }
    if (x.compare(db1->utf8s_index[i][1]) == 0) { return atoi(db1->utf8s_index[i][0]); }
  }
  return -1;
}

void * Compiled_Database::return_table(int x) {

<?php echo $function_interior; ?>

	int *z;
        return z;

}











