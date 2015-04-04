#ifndef _MEMORY_H_
#define _MEMORY_H_

#define MEMSIZE 1024
#define HEADERLEN 8
#define INIT_ADDR_FIELD 0
#define WORD_COUNT_FIELD 1

#include "util.h"
#include "state.h"
#include <cstring>
#include <iostream>
#include <fstream>

typedef struct Header{
	Byte fields[HEADERLEN];
}Header;

class Memory {
public:
    Memory();
    ~Memory();

    // I/O Functions
    Word readw(int);
    HWord readhw(int);
    HUWord readhuw(int);
    void writew(int, Word);
    void writehw(int, HWord);

    void load(const char *filename, Header*, int);

    bool isMisalign(int, int);
    bool isOverflow(int);
    bool valid(int, int);

    UByte& operator [](int addr);
private:
    UByte mem[MEMSIZE];
};

#endif
