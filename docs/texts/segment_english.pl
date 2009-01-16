#use locale;
#use POSIX qw( locale_h );
#setlocale( LC_CTYPE, 'iso_8859_1' );
use Text::Sentence qw( split_sentences );
while (<STDIN>) {$text .= $_;}
@sentences = split_sentences($text);
foreach (@sentences) {  print $_ . "\n"; }

