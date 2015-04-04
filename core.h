#ifndef _CORE_H_
#define _CORE_H_

#define WORDWIDTH 32
#define SP 29
#define RA 31

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <cmath>
#include <climits>
#include "register.h"
#include "memory.h"
#include "util.h"
#include "state.h"

extern int STATE;
extern int CYCLE;

class Core{
public:
    Core();
    ~Core();

    // System control function
    bool isEnable();
    bool isNumberOverflow(Word, Word, Word);
    void load(const char*, const char*);
    void cycle();
    void print();
    void dumpError();

    // R-Type
    void op_add(int, int, int);
    void op_sub(int, int, int);
    void op_and(int, int, int);
    void op_or(int, int, int);
    void op_xor(int, int, int);
    void op_nor(int, int, int);
    void op_nand(int, int, int);
    void op_slt(int, int, int);
    void op_sll(int, int, int);
    void op_srl(int, int, int);
    void op_sra(int, int, int);
    void op_jr(int);

    // I-Type
    void op_addi(int, int, short);
    void op_addiu(int, int, unsigned short);
    void op_lw(int, int, short);
    void op_lh(int, int, short);
    void op_lhu(int, int, short);
    void op_lb(int, int, short);
    void op_lbu(int, int, short);
    void op_sw(int, int, short);
    void op_sh(int, int, short);
    void op_sb(int, int, short);
    void op_lui(int, short);
    void op_andi(int, int, short);
    void op_ori(int, int, short);
    void op_nori(int, int, short);
    void op_slti(int, int, short);
    void op_beq(int, int, short);
    void op_bne(int, int, short);

    // J-Type
    void op_j(int);
    void op_jal(int);

    // Special
    void op_halt();
private:
    int pc;
    int text_len, data_len;
    Register reg;
    Memory imem, dmem;

};

#endif
