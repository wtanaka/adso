<?php

  // Connect to the Database
  $username = "adso";
  $password = "adso";
  $database = "expanded";
  mysql_connect(localhost, $username, $password);
  @mysql_select_db($database) or die ("Unable to select database");



  $start = 1;
  $vrun = 20; 
  $total = 7000;
  
  $premake = '
    COMPILER=g++
    CCFLAGS=
    CCLIBS=
  ';
  $makefile1 = "testing: ";
  $makefile2 = "\t\${COMPILER} -o testing main.o ";
  $makefile3 = "";
  for ($file = 1, $y = $start; $y < $total; $y+=$vrun, $file++) {

    $filetag = "db" . $file;
    $classtag = "Db" . $file;
    $definetag = "DB" . $file;
    $datafilename = $filetag . ".dat";
    $headerfilename = $filetag . ".h";
    $headerfilecontent = $filetag . ".h";
    $makefile1 .= $filetag . ".o ";
    $makefile2 .= $filetag . ".o ";
    $makefile3 .= $filetag . ".o: " . $filetag . ".cpp " . $filetag . ".h\n";
    $makefile3 .= "\t\${COMPILER} \${CCFLAGS} -c " . $filetag . ".cpp \n";


  }


  echo $premake . $makefile1 ."\n" . $makefile2 . "\n" . $makefile3;


?>
