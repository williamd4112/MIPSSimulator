#include "register.h"

Register::Register(){
    memset(reg, 0, sizeof(reg));
}

Register::~Register(){

}

void Register::write(int addr, Word word){
	if(STATE != ENABLE) return;
	if(addr == 0 && word != 0)
		error(WRITE_REGZERO);
	else 
		reg[addr] = word;
}

Word Register::read(int addr){
	return reg[addr];
}

/* Deprecated function
Word& Register::operator [](int addr){
    return reg[addr];
}*/
