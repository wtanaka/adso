<?php

  // Connect to the Database
  $username = "adso";
  $password = "adso";
  $database = "expanded";
  mysql_connect(localhost, $username, $password);
  @mysql_select_db($database) or die ("Unable to select database");


  $query = "SELECT * from character_index";
  $result =  mysql_query($query);
  $num = mysql_numrows($result);


  //echo "\tconst char * character_index[" . $num . "][2];\n";
  for ($i = 0; $i < $num; $i++) {
    echo "\t" . "character_index[" . $i . "][0] = \"" . mysql_result($result, $i, "pkey") . "\";\n";
    echo "\t" . "character_index[" . $i . "][1] = \"" . mysql_result($result, $i, "name") . "\";\n";
  }
  echo "\t" . "character_index[" . $num . "][0] = \"@\";\n";
  echo "\n\n";


  $query3 = "SELECT * from utf8s_index";
  $result3 =  mysql_query($query3);
  $num3 = mysql_numrows($result3);
  //echo "\tconst char * utf8s_index[" . $num3 . "][2];\n";
  for ($b = 0; $b < $num3; $b++) {
    echo "\t" . "utf8s_index[" . $b . "][0] = \"" . mysql_result($result3, $b, "pkey") . "\";\n";
    echo "\t" . "utf8s_index[" . $b . "][1] = \"" . mysql_result($result3, $b, "name") . "\";\n";
  }
  echo "\t" . "utf8s_index[" . $num3 . "][0] = \"@\";\n";
  echo "\n\n";


  mysql_close();

?>
