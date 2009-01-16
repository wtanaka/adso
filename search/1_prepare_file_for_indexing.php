<?php

  $infile = $argv[1];

  $fh = fopen($infile, 'r');
  $contents = fread($fh,filesize($infile));
  fclose($fh);

  $contents = str_replace("\t"," ",$contents);

  $segmented_utf8s   = `adso -f $infile -oe utf8 -os simplified --segcn --no-phrases`;
  $segmented_utf8c   = `adso -f $infile -oe utf8 -os traditional --segcn --no-phrases`;
  $segmented_english = `adso -f $infile -oe utf8 -os traditional -t --code`;
  $segmented_pinyin  = `adso -f $infile -oe utf8 -os traditional -y`;
  $link = $infile;
  $pubdate = "";

  $segmented_utf8s = str_replace("\n","",$segmented_utf8s);
  $segmented_utf8c = str_replace("\n","",$segmented_utf8c);
  $segmented_english = str_replace("\n","",$segmented_english);
  $segmented_pinyin = str_replace("\n","",$segmented_pinyin);
  $contents = str_replace("\n","",$contents);

  echo $contents;
  echo "\t";
  echo $segmented_utf8s;
  echo "\t";
  echo $segmented_utf8c;
  echo "\t";
  echo $segmented_english;
  echo "\t";
  echo $segmented_pinyin;
  echo "\t";
  echo $link;
  echo "\t";
  echo $pubdate;
  echo "\n";

?>
