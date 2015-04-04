#ifndef _STATE_H_
#define _STATE_H_

#include <cstdio>
#include <queue>

#define WRITE_REGZERO 0x0001
#define NUMBER_OVERFLOW 0x0002
#define ADDRESS_OVERFLOW 0X0004
#define DATA_MISALIGN 0X0008

#define ENABLE 1
#define DISABLE 0
#define INTERRUPT -1

void error(int);
void print_error();

#endif