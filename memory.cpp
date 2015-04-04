#include "memory.h"

Memory::Memory(){
    memset(mem, 0, sizeof(mem));
}

Memory::~Memory(){

}

bool Memory::isMisalign(int addr, int basic_block){
	bool result = (addr % basic_block == 0) ? false : true;
	
	if(result) 
		error(DATA_MISALIGN);
	
	return result;
}

bool Memory::isOverflow(int addr){
	bool result = (addr >= MEMSIZE);

	if(result) 
		error(ADDRESS_OVERFLOW);

	return result;
}

bool Memory::valid(int addr, int basic_block){
	return (!isMisalign(addr, basic_block) && !isOverflow(addr)) ? true : false;
}

Word Memory::readw(int addr){
	
	return (valid(addr, 4)) ? 
		   (mem[addr] << 24 | mem[addr + 1] << 16 | mem[addr + 2] << 8 | mem[addr + 3]) : 0;
}

HWord Memory::readhw(int addr){

	return (valid(addr, 2)) ? mem[addr] << 8 | mem[addr + 1] : 0;
}

HUWord Memory::readhuw(int addr){

	return (valid(addr, 2)) ? (HUWord)(mem[addr] << 8 | mem[addr + 1]) : 0;
}

void Memory::writew(int addr, Word word){
	if(valid(addr, 4)){
    	mem[addr] = fetch(word, 24, 31);
    	mem[addr + 1] = fetch(word, 16, 23);
    	mem[addr + 2] = fetch(word, 8, 15);
    	mem[addr + 3] = fetch(word, 0, 7);
	}
}

void Memory::writehw(int addr, HWord word){
	if(valid(addr, 2)) {
    	mem[addr] = fetch(word, 8, 15);
    	mem[addr + 1] = fetch(word, 0, 7);
	}
}

void Memory::load(const char *filename, Header *header, int pos){
    std::ifstream fs;
    fs.exceptions(std::ifstream::failbit | std::ifstream::badbit);

    try {
    	fs.open(filename, std::ifstream::in | std::ifstream::binary);
    	
    	fs.seekg (0, fs.end);
    	int len = fs.tellg();
    	fs.seekg (0, fs.beg);

    	// Read header
    	fs.read(header->fields, HEADERLEN);
    	int init_addr = (pos < 0) ? bbtow(header->fields) : 0;
    	int word_count = bbtow(header->fields + 4);

        fs.read((Byte*)(mem + init_addr), word_count * 4);

#ifdef DEBUG
    	printf("\nLoad: %s \t Length: %d\n",filename, len);
  		int wc = 0;
    	for(int i = init_addr; i < init_addr + word_count * 4; i +=4){
    		printf("(%d)%d: 0x%02x 0x%02x 0x%02x 0x%02x\n",++wc, i, mem[i], mem[i + 1], mem[i + 2], mem[i + 3]);
    	}
#endif

    } catch (std::ifstream::failure e){
    	std::cerr << "Memory.load: failed to load " << filename << std::endl;
    }

}

UByte& Memory::operator [](int addr){
    	return mem[addr];
}
