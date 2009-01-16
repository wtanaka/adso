<?php

  // Connect to the Database
  $username = "root";
  $password = "";
  $database = "expanded";
  mysql_connect(localhost, $username, $password);
  @mysql_select_db($database) or die ("Unable to select database");


  $query = "SELECT * from expanded_unified";
  $result =  mysql_query($query);
  $num = mysql_num_rows($result);


echo '
DROP TABLE IF EXISTS expanded_unified;
CREATE TABLE IF NOT EXISTS expanded_unified (
  pkey INTEGER,
  CHINESE_UTF8_S TEXT,
  CHINESE_UTF8_C TEXT,
  PINYIN TEXT,
  PINYIN2 TEXT,
  FLAG TEXT,
  ENGLISH TEXT
);
';






  for ($y = 0; $y < $num; $y++) {

     //if (($y % 100) == 1) { echo "At word $y" . "... \n"; } 

     $a = mysql_result($result,$y,"pkey");
     $b = mysql_result($result,$y,"CHINESE_UTF8_S");
     $c = mysql_result($result,$y,"CHINESE_UTF8_C");
     $d = mysql_result($result,$y,"PINYIN");
     $d2 = mysql_result($result,$y,"PINYIN");
     $e = mysql_result($result,$y,"FLAG");
     $f = mysql_result($result,$y,"ENGLISH");

     echo 'INSERT INTO expanded_unified (pkey, CHINESE_UTF8_S, CHINESE_UTF8_C, PINYIN, PINYIN2, FLAG, ENGLISH) VALUES ('.l($a).',"'.l($b).'","'.l($c).'","'.l2($d).'","'.l($d).'","'.l($e).'","'.l($f).'");';
     echo "\n";
  }  


  echo '


  CREATE INDEX simp_i ON expanded_unified( CHINESE_UTF8_S );
  CREATE INDEX trad_i ON expanded_unified( CHINESE_UTF8_C );
  CREATE INDEX pin_i ON expanded_unified( PINYIN );
  CREATE INDEX pin2_i ON expanded_unified( PINYIN2 );
  CREATE INDEX def_i ON expanded_unified( ENGLISH );


  ';

  


  mysql_close();

  function l($x) {
    return str_replace('"','\"',$x);
  }
  function l2($x) {
    $x = str_replace('"','\"',$x);
    $x = str_replace('1','',$x);
    $x = str_replace('2','',$x);
    $x = str_replace('3','',$x);
    $x = str_replace('4','',$x);
    $x = str_replace('5','',$x);
    return $x;
  }

?>
