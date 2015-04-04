#include "core.h"

Core::Core(){
    
}

Core::~Core(){

}

void Core::load(const char *iimagename, const char *dimagename){
    // Load iimage
    Header iimage_header;
    imem.load(iimagename, &iimage_header, -1);
    pc = bbtow(iimage_header.fields);
    text_len = bbtow(iimage_header.fields + 4);

#ifdef DEBUG
    printf("PC = %d ; text_len = %d\n",pc, text_len);
#endif
    
    // Load dimage
    Header dimage_header;
    dmem.load(dimagename, &dimage_header, 0);
    reg.write(SP, bbtow(dimage_header.fields));
    data_len = bbtow(dimage_header.fields + 4);

#ifdef DEBUG
    printf("SP = %d ; data_len = %d\n",reg.read(SP), data_len);
#endif

}

bool Core::isNumberOverflow(Word vd, Word vs, Word vt){
    if(std::signbit(vs) == std::signbit(vt)){
        bool flag = std::signbit(vd) == std::signbit(vs);
        if(flag)
            error(NUMBER_OVERFLOW);
        return (flag) ? false : true;
    }

    return false;
}

void Core::op_add(int rd, int rs, int rt){
#ifdef DEBUG
    printf("add $%d, $%d, $%d\n",rd, rs, rt);
#endif
    
    Word vs = reg.read(rs);
    Word vt = reg.read(rt);
    Word vd = reg.read(rs) + reg.read(rt);

    isNumberOverflow(vd, vs, vt);
    
    reg.write(rd, vd);
    
    //reg[rd] = reg[rs] + reg[rt];
}

void Core::op_sub(int rd, int rs, int rt){
#ifdef DEBUG
    printf("sub $%d, $%d, $%d\n",rd, rs, rt);
#endif

    Word vs = reg.read(rs);
    Word vt = reg.read(rt);
    Word vd = reg.read(rs) + reg.read(rt);

    isNumberOverflow(vd, vs, vt);

    reg.write(rd, vd);
    //reg[rd] = reg[rs] - reg[rt];
}

void Core::op_and(int rd, int rs, int rt){
#ifdef DEBUG
    printf("and $%d, $%d, $%d\n",rd, rs, rt);
#endif
    reg.write(rd, reg.read(rs) & reg.read(rt));
    //reg[rd] = reg[rs] & reg[rt];
}

void Core::op_or(int rd, int rs, int rt){
#ifdef DEBUG
    printf("or $%d, $%d, $%d\n",rd, rs, rt);
#endif
    reg.write(rd, reg.read(rs) | reg.read(rt));
    //reg[rd] = reg[rs] | reg[rt];
}

void Core::op_xor(int rd, int rs, int rt){
#ifdef DEBUG
    printf("xor $%d, $%d, $%d\n",rd, rs, rt);
#endif
    reg.write(rd, reg.read(rs) ^ reg.read(rt));
    //reg[rd] = reg[rs] ^ reg[rt];
}

void Core::op_nor(int rd, int rs, int rt){
#ifdef DEBUG
    printf("nor $%d, $%d, $%d\n",rd, rs, rt);
#endif
    reg.write(rd, ~(reg.read(rs) | reg.read(rt)));
    //reg[rd] = ~(reg[rs] | reg[rt]);
}

void Core::op_nand(int rd, int rs, int rt){
#ifdef DEBUG
    printf("nand $%d, $%d, $%d\n",rd, rs, rt);
#endif
    reg.write(rd, ~(reg.read(rs) & reg.read(rt)));
    //reg[rd] = ~(reg[rs] & reg[rt]);
}

void Core::op_slt(int rd, int rs, int rt){
#ifdef DEBUG
    printf("slt $%d, $%d, $%d\n",rd, rs, rt);
#endif
    reg.write(rd, reg.read(rs) < reg.read(rt));
    //reg[rd] = reg[rs] < reg[rt];
}

void Core::op_sll(int rd, int rt, int shamt){
#ifdef DEBUG
    printf("sll $%d, $%d, $%d\n",rd, rt, shamt);
#endif
    reg.write(rd, reg.read(rt) << shamt);
    //reg[rd] = reg[rt] << shamt;
}

void Core::op_srl(int rd, int rt, int shamt){
#ifdef DEBUG
    printf("srl $%d, $%d, $%d\n",rd, rt, shamt);
#endif
    reg.write(rd, (UWord)reg.read(rt) >> shamt);
    //reg[rd] = (UWord)reg[rt] >> shamt;
}

void Core::op_sra(int rd, int rt, int shamt){
#ifdef DEBUG
    printf("sra $%d, $%d, $%d\n",rd, rt, shamt);
#endif
    reg.write(rd, reg.read(rt) >> shamt);
    //reg[rd] = reg[rt] >> shamt;
}

void Core::op_jr(int rs){
#ifdef DEBUG
    printf("jr $%d\n",rs);
#endif
    pc = reg.read(rs);
    //pc = reg[rs];
}

void Core::op_addi(int rt, int rs, HWord c){
#ifdef DEBUG
    printf("addi $%d, $%d, %d\n",rt, rs, c);
#endif
    Word vs = reg.read(rs);
    Word vt = vs + c;

    isNumberOverflow(vt, vs, c);

    reg.write(rt, reg.read(rs) + c);
    //reg[rt] = reg[rs] + c;
}

void Core::op_addiu(int rt, int rs, HUWord c){
#ifdef DEBUG
    printf("addiu $%d, $%d, %d\n",rt, rs, c);
#endif
    reg.write(rt, (UWord)reg.read(rs) + c);
    //reg[rt] = (UWord)reg[rs] + c;
}

void Core::op_lw(int rt, int rs, short immediate){
#ifdef DEBUG
    printf("lw $%d, %d($%d)\n",rt, immediate, rs);
#endif
    reg.write(rt, dmem.readw(reg.read(rs) + immediate));
    //reg[rt] = dmem.readw(reg[rs] + immediate);
}

void Core::op_lh(int rt, int rs, short immediate){
#ifdef DEBUG
    printf("lh $%d, %d($%d)\n",rt, immediate, rs);
#endif
    reg.write(rt, (dmem.readhw(reg.read(rs) + immediate)));
    //reg.write(rt, (dmem.readw(reg.read(rs) + immediate)) >> 16);
    //reg[rt] = (dmem.readw(reg[rs] + immediate)) >> 16;
}

void Core::op_lhu(int rt, int rs, short immediate){
#ifdef DEBUG
    printf("lhu $%d, %d($%d)\n",rt, immediate, rs);
#endif
    reg.write(rt, (UWord)(dmem.readhuw(reg.read(rs) + immediate)));
    //reg.write(rt, (UWord)(dmem.readw(reg.read(rs) + immediate)) >> 16);
    //reg[rt] = ((UWord)(dmem.readw(reg[rs] + immediate)) >> 16) ;
}

void Core::op_lb(int rt, int rs, short immediate){
#ifdef DEBUG
    printf("lb $%d, %d($%d)\n",rt, immediate, rs);
#endif
    reg.write(rt, (dmem[reg.read(rs) + immediate]) | 0xffffff00);
    //reg[rt] = (dmem[reg[rs] + immediate]) | 0xffffff00;
}

void Core::op_lbu(int rt, int rs, short immediate){
#ifdef DEBUG
    printf("lbu $%d, %d($%d)\n",rt, immediate, rs);
#endif
    reg.write(rt, (UWord)(dmem[reg.read(rs) + immediate]));
    //reg[rt] = (UWord)(dmem[reg[rs] + immediate]);
}

void Core::op_sw(int rt, int rs, short immediate){
#ifdef DEBUG
    printf("sw $%d, %d($%d)\n",rt, immediate, rs);
#endif
    dmem.writew(reg.read(rs) + immediate, reg.read(rt));
}

void Core::op_sh(int rt, int rs, short immediate){
#ifdef DEBUG
    printf("sh $%d, %d($%d)\n",rt, immediate, rs);
#endif
    dmem.writehw(reg.read(rs) + immediate, (HWord)(reg.read(rt) & 0x0000FFFF));
}

void Core::op_sb(int rt, int rs, short immediate){
#ifdef DEBUG
    printf("sb $%d, %d($%d)\n",rt, immediate, rs);
#endif
    dmem[reg.read(rs) + immediate] = (Byte)(reg.read(rt) & 0x000000FF);
}

void Core::op_lui(int rt, short immediate){
#ifdef DEBUG
    printf("lui $%d, %d\n",rt, immediate);
#endif
    reg.write(rt, immediate << 16); 
    //reg[rt] = immediate << 16;
}

void Core::op_andi(int rt, int rs, short immediate){
#ifdef DEBUG
    printf("andi $%d, $%d, %d\n",rt, rs, immediate);
#endif
    reg.write(rt, reg.read(rs) & immediate);
    //reg[rt] = reg[rs] & immediate;
}

void Core::op_ori(int rt, int rs, short immediate){
#ifdef DEBUG
    printf("ori $%d, $%d, %d\n",rt, rs, immediate);
#endif
    reg.write(rt, reg.read(rs) | immediate);        
    //reg[rt] = reg[rs] | immediate;
}

void Core::op_nori(int rt, int rs, short immediate){
#ifdef DEBUG
    printf("nori $%d, $%d, %d\n",rt, rs, immediate);
#endif
    reg.write(rt, ~(reg.read(rs) | immediate));
    //reg[rt] = ~(reg[rs] | immediate);
}

void Core::op_slti(int rt, int rs, short immediate){
#ifdef DEBUG
    printf("slti $%d, $%d, %d\n",rt, rs, immediate);
#endif
    reg.write(rt, reg.read(rs) < immediate);
    //reg[rt] = (reg[rs] < immediate);
}

void Core::op_beq(int rt, int rs, short immediate){
#ifdef DEBUG
    printf("beq $%d, $%d, %d\n",rs, rt, immediate);
#endif
    pc = (reg.read(rs) == reg.read(rt)) ? pc + immediate * 4 + 4 : pc + 4;
}

void Core::op_bne(int rt, int rs, short immediate){
#ifdef DEBUG
    printf("bne $%d, $%d, %d\n",rs, rt, immediate);
#endif
    pc = (reg.read(rs) != reg.read(rt)) ? pc + immediate * 4 + 4 : pc + 4;
}

void Core::op_j(int addr){
    pc = fetch(pc, 28, 31) | (addr << 2);
#ifdef DEBUG
    printf("j %d(%d)\n",addr, pc);
#endif
}

void Core::op_jal(int addr){
    reg.write(RA, pc + 4);
    //reg[RA] = pc + 4;
    pc = fetch(pc, 28, 31) | (addr << 2);
#ifdef DEBUG
    printf("jal %d(ra = %d \t new_pc = %d)\n",addr, reg.read(RA), pc);
#endif
}

void Core::op_halt(){
    STATE = INTERRUPT;
#ifdef DEBUG
    printf("halt\n");
#endif
}

void Core::cycle(){

    //Fetch opcode
    unsigned int opcode = imem.readw(pc);

    //Parse opcode
    unsigned int op = fetch(opcode, 26, 31);
    unsigned int rs = fetch(opcode, 21, 25);
    unsigned int rt = fetch(opcode, 16, 20);
    unsigned int rd = fetch(opcode, 11, 15);
    int shamt = fetch(opcode, 6, 10);
    unsigned int funct = fetch(opcode, 0, 5);
    HWord immediate = fetch(opcode, 0, 15);
    HUWord addr = fetch(opcode, 0, 25);

    switch(op){
        //R-type:
        case 0x00:{
            switch(funct){
                case 0x20:
                    op_add(rd, rs, rt); pc += 4;
                    break;
                case 0x22:
                    op_sub(rd, rs, rt); pc += 4;
                    break;
                case 0x24:
                    op_and(rd, rs, rt); pc += 4;
                    break;
                case 0x25:
                    op_or(rd, rs, rt); pc += 4;
                    break;
                case 0x26:
                    op_xor(rd, rs, rt); pc += 4;
                    break;
                case 0x27:
                    op_nor(rd, rs, rt); pc += 4;
                    break;
                case 0x28:
                    op_nand(rd, rs, rt); pc += 4;
                    break;
                case 0x2A:
                    op_slt(rd, rs, rt); pc += 4;
                    break;
                case 0x00:
                    op_sll(rd, rt, shamt); pc += 4;
                    break;
                case 0x02:
                    op_srl(rd, rt, shamt); pc += 4;
                    break;
                case 0x03:
                    op_sra(rd, rt, shamt); pc += 4;
                    break;
                case 0x08:
                    op_jr(rs);
                    break;
                default:
                    break;
            }
        }
        break;

        // I-type
        case 0x08:
            op_addi(rt, rs, immediate); pc += 4;
            break;
        case 0x23:
            op_lw(rt, rs, immediate); pc += 4;
            break;
        case 0x21:
            op_lh(rt, rs, immediate); pc += 4;
            break;
        case 0x25:
            op_lhu(rt, rs, immediate); pc += 4;
            break;
        case 0x20:
            op_lb(rt, rs, immediate); pc += 4;
            break;
        case 0x24:
            op_lbu(rt, rs, immediate); pc += 4;
            break;
        case 0x2B:
            op_sw(rt, rs, immediate); pc += 4;
            break;
        case 0x29:
            op_sh(rt, rs, immediate); pc += 4;
            break;
        case 0x28:
            op_sb(rt, rs, immediate); pc += 4;
            break;
        case 0x0F:
            op_lui(rt, immediate); pc += 4;
            break;
        case 0x0C:
            op_andi(rt, rs, immediate); pc += 4;
            break;
        case 0x0D:
            op_ori(rt, rs, immediate); pc += 4;
            break;
        case 0x0E:
            op_nori(rt, rs, immediate); pc += 4;
            break;
        case 0x0A:
            op_slti(rt, rs, immediate); pc += 4;
            break;
        case 0x04:
            op_beq(rt, rs, immediate);
            break;
        case 0x05:
            op_bne(rt, rs, immediate);
            break;

        // J-Type
        case 0x02:
            op_j(addr);
            break;
        case 0x03:
            op_jal(addr);
            break;

        // Special
        case 0x3F:
            op_halt(); pc += 4;
            break;
        default:
            break;
    }
    CYCLE++;
}

bool Core::isEnable(){
    return (STATE == ENABLE) ? true : false;
}

void Core::dumpError(){
    print_error();
}

void Core::print(){
    printf("cycle %d\n",CYCLE);
    for(int i = 0; i < REGSIZE; i++){
        printf("$%02d: 0x%08X\n",i,reg.read(i));
    }

#ifdef DEBUG
    printf("PC: %d\n\n\n", pc);
#endif

#ifndef DEBUG
    printf("PC: 0x%08X\n\n\n", pc);
#endif

}
