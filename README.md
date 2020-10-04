# Coding-for-just-practice

1. Huffman Coding
   Source codes execute huffman coding with the string you entered. In main.cpp file, you can cahnge the "unit" parameter to vary the length of the symbol. Note that you have to download three of files in that directory to execute. I put a example of it.

Enter a string: Abracadabralalalala
Length of input string: 19
Below is the freq. table of symbols before sorting.
[00]    1 A
[01]    2 b
[02]    2 r
[03]    8 a
[04]    1 c
[05]    1 d
[06]    4 l
Below is the freq. table of symbols after sorting.
[00]    8 a
[01]    4 l
[02]    2 b
[03]    2 r
[04]    1 A
[05]    1 c
[06]    1 d
Code word is assigned.
a->  Frequency:   8, Code word: 0
l->  Frequency:   4, Code word: 10
A->  Frequency:   1, Code word: 1100
d->  Frequency:   1, Code word: 11010
c->  Frequency:   1, Code word: 11011
r->  Frequency:   2, Code word: 1110
b->  Frequency:   2, Code word: 1111
We have a bitstream : 1100111111100110110110100111111100100100100100
Length of bitstream : 46
Decoded string: Abracadabralalalala
