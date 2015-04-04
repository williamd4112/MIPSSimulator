#include "util.h"

Word fetch(Word opcode, int lower, int upper){
    return (opcode >> lower) & ~(~0 << (upper - lower + 1));
}

Word btol(Word word){

}

Word bbtow(Byte *base_addr){
	return (*base_addr << 24 | *(base_addr + 1) << 16 | *(base_addr + 2) << 8 | *(base_addr + 3));
}

Word fgetw(std::ifstream& fs){
    Word word;
    fs.read((Byte*)&word, sizeof(Word));
}

