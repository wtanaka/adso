<?php

  // Connect to the Database
  $username = "root";
  $password = "";
  $database = "expanded";
  mysql_connect(localhost, $username, $password);
  @mysql_select_db($database) or die ("Unable to select database");
  mysql_query("set names 'latin1'");


  $query = "SELECT * from expanded_unified";
  $result =  mysql_query($query);
  $num = mysql_num_rows($result);


echo '
DROP TABLE IF EXISTS expanded_unified;
CREATE TABLE IF NOT EXISTS expanded_unified (
  pkey INTEGER,
  CHINESE TEXT,
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
     $aa = mysql_result($result,$y,"CHINESE");
     $b = mysql_result($result,$y,"CHINESE_UTF8_S");
     $c = mysql_result($result,$y,"CHINESE_UTF8_C");
     $d = mysql_result($result,$y,"PINYIN");
     $d2 = mysql_result($result,$y,"PINYIN");
     $e = mysql_result($result,$y,"FLAG");
     $f = mysql_result($result,$y,"ENGLISH");

     echo 'INSERT INTO expanded_unified (pkey, CHINESE, CHINESE_UTF8_S, CHINESE_UTF8_C, PINYIN, PINYIN2, FLAG, ENGLISH) VALUES ('.l($a).',"'.l($aa).'","'.l($b).'","'.l($c).'","'.l2($d).'","'.l($d).'","'.l($e).'","'.l($f).'");';
     echo "\n";
  }  


  echo '


  CREATE INDEX simp_i ON expanded_unified( CHINESE_UTF8_S );
  CREATE INDEX trad_i ON expanded_unified( CHINESE_UTF8_C );
  CREATE INDEX pin_i ON expanded_unified( PINYIN );
  CREATE INDEX pin2_i ON expanded_unified( PINYIN2 );
  CREATE INDEX def_i ON expanded_unified( ENGLISH );


  ';



  $query = "SELECT * from character_index";
  $result =  mysql_query($query);
  $num = mysql_num_rows($result);


echo '
DROP TABLE IF EXISTS character_index;
CREATE TABLE IF NOT EXISTS character_index (
  pkey INTEGER,
  NAME TEXT,
  PINYIN TEXT
);
';


  for ($i = 0; $i < $num; $i++) {

    $table_name   = "_" . mysql_result($result,$i,"pkey");
    $pkey         = mysql_result($result,$i,"pkey");
    $name         = mysql_result($result,$i,"NAME");
    $pinyin       = mysql_result($result,$i,"PINYIN");
    echo 'INSERT INTO character_index (pkey, NAME, PINYIN) VALUES ('.l($pkey).',"'.l($name).'","'.l($pinyin).'");' . "\n";


echo '
DROP TABLE IF EXISTS '.$table_name.';
CREATE TABLE IF NOT EXISTS '.$table_name.' (
  pkey INTEGER,
  CHINESE TEXT,
  CHINESE_UTF8_S TEXT,
  CHINESE_UTF8_C TEXT,
  ENGLISH TEXT,
  PINYIN TEXT,
  FLAG TEXT,
  FREQ TEXT,
  SOURCE TEXT,
  CODE TEXT
);
';

    $query2 = "SELECT * from ".$table_name.";";
    $result2 =  mysql_query($query2);
    $num2 = mysql_num_rows($result2);
 
    for ($y = 0; $y < $num2; $y++) {
      
      $chinese                = mysql_result($result2,$y,"CHINESE");
      $chinese_utf8_s         = mysql_result($result2,$y,"CHINESE_UTF8_S");
      $chinese_utf8_c         = mysql_result($result2,$y,"CHINESE_UTF8_C");
      $english                = mysql_result($result2,$y,"ENGLISH");
      $pinyin                 = mysql_result($result2,$y,"PINYIN");
      $flag                   = mysql_result($result2,$y,"FLAG");
      $freq                   = mysql_result($result2,$y,"FREQ");
      $source                 = mysql_result($result2,$y,"SOURCE");
      $code                   = mysql_result($result2,$y,"CODE");

      echo 'INSERT INTO '.$table_name.' (pkey, CHINESE, CHINESE_UTF8_S, CHINESE_UTF8_C, ENGLISH, PINYIN, FLAG, FREQ, SOURCE, CODE) VALUES ('.l($pkey).',"'.l($chinese).'","'.l($chinese_utf8_s).'","'.l($chinese_utf8_c).'","'.l($english).'","'.l($pinyin).'","'.l($flag).'","'.l($freq).'","'.l($source).'","'.l($code).'");' . "\n";

    }


  }



  $query = "SELECT * from utf8s_index";
  $result =  mysql_query($query);
  $num = mysql_num_rows($result);

echo '
DROP TABLE IF EXISTS utf8s_index;
CREATE TABLE IF NOT EXISTS utf8s_index (
  pkey INTEGER,
  name TEXT
);
';
  for ($i = 0; $i < $num; $i++) {

    $pkey         = mysql_result($result,$i,"pkey");
    $name         = mysql_result($result,$i,"name");
    echo 'INSERT INTO utf8s_index (pkey, name) VALUES ('.l($pkey).',"'.l($name).'");' . "\n";

  }





  
  $query = "SELECT * from utf8s_index";
  $result =  mysql_query($query);
  $num = mysql_num_rows($result);

echo '
DROP TABLE IF EXISTS utf8c_index;
CREATE TABLE IF NOT EXISTS utf8c_index (
  pkey INTEGER,
  name TEXT,
  first INTEGER,
  second INTEGER,
  third INTEGER,
  fourth INTEGER
);
';
  for ($i = 0; $i < $num; $i++) {
    $pkey          = mysql_result($result,$i,"pkey");
    $name          = mysql_result($result,$i,"name");
    $first         = mysql_result($result,$i,"first");
    $second        = mysql_result($result,$i,"second");
    $third         = mysql_result($result,$i,"third");
    $fourth        = mysql_result($result,$i,"fourth");
    echo 'INSERT INTO utf8c_index (pkey, name, first, second, third, fourth) VALUES ('.l($pkey).',"'.l($name).'","'.l($first).'","'.l($second).'","'.l($third).'","'.l($fourth).'");' . "\n";
  }
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
