#ifndef _UTIL_H_
#define _UTIL_H_
#include <cstdio>
#include <iostream>
#include <fstream>

typedef int Word;
typedef short HWord;
typedef char Byte;
typedef unsigned int UWord;
typedef unsigned short HUWord;
typedef unsigned char UByte;

Word fetch(Word, int, int);
Word btol(Word);
Word fgetw(std::ifstream&);
Word bbtow(Byte*);

#endif
