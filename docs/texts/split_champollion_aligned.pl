
$start = $ARGV[0];
while (<STDIN>) { $text .= $_; }
@lines = split(/\n/,$text);
for ($i = $start; $lines[$i] ne ""; $i+=4) {
  print $lines[$i] . "\n";
}



