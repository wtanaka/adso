<?php

  // Connect to the Database
  $username = "adso";
  $password = "adso";
  $database = "expanded";
  mysql_connect(localhost, $username, $password);
  @mysql_select_db($database) or die ("Unable to select database");
  mysql_query("set names 'latin1'");


  $start = 1; // starting character
  $vrun = 20; // number of characters for a single .dat file
  $total = 7000;  // max characters (GB2312 only supports 67000-odd characters)


  $query = "SELECT * from character_index";
  $result =  mysql_query($query);
  $num = mysql_numrows($result);




  for ($file = 1, $y = $start; $y < $total; $y+=$vrun, $file++) {

    $filetag = "db" . $file;
    $classtag = "Db" . $file;
    $definetag = "DB" . $file;
    $datafilename = $filetag . ".dat";
    $headerfilename = $filetag . ".h";
    $headerfilecontent = $filetag . ".h";

    $cppfilename = $filetag . ".cpp";



    if ($y == 1) {
    $cppfilecontent = '
#include "' . $filetag . '.h"


' . $classtag . '::' . $classtag . '() {
  #include "' . $filetag . '.dat"
  #include "indexes.dat"
};
' . $classtag . '::~' . $classtag . '() {};

';
   } else {

    $cppfilecontent = '
#include "' . $filetag . '.h"


' . $classtag . '::' . $classtag . '() {
  #include "' . $filetag . '.dat"
};
' . $classtag . '::~' . $classtag . '() {};

';
   }




//     echo $cppfilecontent;
	$headerfilecontent = '
#ifndef '.$definetag . '_H
#define '.$definetag . '_H

class ' . $classtag . ' {

	public:

		' . $classtag . '();
		~' . $classtag . '();

';

    if ($y ==1 ) {

      $headerfilecontent .= '

        const char * character_index[6862][2];
        const char * utf8s_index[6862][2];

      ';
    }


    $datafilecontent = "";
    for ($i = $y; $i < $y+$vrun && $i < $num; $i++) {

      $table = "table_" . mysql_result($result, $i-1, "pkey");
      $query2 = "SELECT * from _" . mysql_result($result, $i-1, "pkey") . " WHERE CHINESE IS NOT NULL ";
      $result2 =  mysql_query($query2);
      $num2 = mysql_num_rows($result2);

      for ($z = 0; $z < $num2 && $num2 > 0; $z++) {
        $datafilecontent .= "\t" . $table . "[" . $z . "][0] = \"" . mysql_result($result2, $z, "pkey") . "\";\n";
        $datafilecontent .= "\t" . $table . "[" . $z . "][1] = \"" . mysql_result($result2, $z, "CHINESE") . "\";\n";
        $datafilecontent .= "\t" . $table . "[" . $z . "][2] = \"" . mysql_result($result2, $z, "CHINESE_UTF8_S") . "\";\n";
        $datafilecontent .= "\t" . $table . "[" . $z . "][3] = \"" . mysql_result($result2, $z, "CHINESE_UTF8_C") . "\";\n";
        //$datafilecontent .= "\t" . $table . "[" . $z . "][4] = \"" . mysql_result($result2, $z, "CHINESE_BIG5") . "\";\n";
        $datafilecontent .= "\t" . $table . "[" . $z . "][4] = \"\";\n";
        $datafilecontent .= "\t" . $table . "[" . $z . "][5] = \"" . mysql_result($result2, $z, "FLAG") . "\";\n";
        $datafilecontent .= "\t" . $table . "[" . $z . "][6] = \"" . str_replace("\"","\\\"",mysql_result($result2, $z, "ENGLISH")) . "\";\n";
        $datafilecontent .= "\t" . $table . "[" . $z . "][7] = \"" . str_replace("\"","\\\"",mysql_result($result2, $z, "PINYIN")) . "\";\n";
        $datafilecontent .= "\t" . $table . "[" . $z . "][8] = \"" . mysql_result($result2, $z, "CODE") . "\";\n";
        //$datafilecontent .= "\t" . $table . "[" . $z . "][9] = \"" . mysql_result($result2, $z, "SOURCE") . "\";\n";      
        $datafilecontent .= "\t" . $table . "[" . $z . "][9] = \"ADSO\";\n";      
      }
      if ($num2 > 0) {
        $table = "table_" . mysql_result($result, $i-1, "pkey");
        $headerfilecontent .= "\tconst char * " . $table . "[" . ($num2+1) . "][11];\n";
        $datafilecontent .= "\t" . $table . "[" . $num2 . "][0] = \"@\";\n";      
      }
    }

    $headerfilecontent .= '
};
#endif
';

    // Write our Header and C++ Files
    $fh = fopen($cppfilename , 'w');
    fwrite($fh, $cppfilecontent);
    fclose($fh);

    $fh = fopen($headerfilename , 'w');
    fwrite($fh, $headerfilecontent);
    fclose($fh);

    $fh = fopen($datafilename , 'w');
    fwrite($fh, $datafilecontent);
    fclose($fh);

    system("sed -e \"s///g\" $datafilename > temp");
    system("cp -f temp $datafilename");


  }  

  mysql_close();
  exit(0);

?>
