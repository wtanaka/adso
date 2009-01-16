<?php

  // Connect to the Database
  $username = "adso";
  $password = "adso";
  $database = "expanded";
  mysql_connect("localhost", $username, $password);
  @mysql_select_db($database) or die ("Unable to select database");


  $query = "SELECT pkey, SUBTABLE, CHINESE_UTF8_S from expanded_unified where PINYIN = \"\";";
  $result =  mysql_query($query);
  $num = mysql_num_rows($result);


  // START XML FILE
  for ($i = 0; $i < $num; $i++) { 

    $simplified      = mysql_result($result, $i, "CHINESE_UTF8_S");
    $subtable        = mysql_result($result, $i, "SUBTABLE");
    $pkey            = mysql_result($result, $i, "pkey");

    $pinyin = `adso -i "$simplified" -y`;

    $pinyin = str_replace("\n","",$pinyin);


    $query = "UPDATE expanded_unified SET PINYIN = \"".$pinyin."\" WHERE pkey = ".$pkey.";";
    mysql_query($query);

    $query = "UPDATE _$subtable SET PINYIN = \"".$pinyin."\" WHERE pkey = ".$pkey.";";
    mysql_query($query);


  }


  mysql_close();



