echo #ifdef song_%1_DEF >> song.inc
echo #include "song_%1.asm" >> song.inc
echo #endif >> song.inc
echo; >> song.inc

echo //son_mac (song_%1) >> song.asm
echo //#define song_%1_DEF>> song.asm
echo; >> song.asm
