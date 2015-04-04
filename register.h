#ifndef _REGISTER_H_
#define _REGISTER_H_
#define REGSIZE 32

#include <cstdio>
#include <cstring>
#include <cstdlib>
#include "state.h"
#include "util.h"


extern int STATE;
extern int CYCLE;

class Register{
public:
    Register();
    ~Register();

    void write(int addr, Word word);
    Word read(int addr);
    //Word& operator [](int addr);
private:
    Word reg[REGSIZE];
};

#endif
