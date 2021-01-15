#include "../h/decode.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include <math.h>


extern unsigned char memory[0x10000];
extern unsigned char pc;

void fetchMemory(unsigned short *m) {
    *m = *(unsigned short*)(memory + pc);
    pc += 2;
}

void decode() {
    fetchMemory(&m);
    // 0xFFFF
    if (m == 0x0000) { nop(); return; }
    if (m == 0x9409) { ijmp(); return; }
    if (m == 0x9419) { eijmp(); return; }
    if (m == 0x9508) { ret(); return; }
    if (m == 0x9509) { icall(); return; }
    if (m == 0x9518) { reti(); return; }
    if (m == 0x9519) { eicall(); return; }
    if (m == 0x9588) { sleep(); return; }
    if (m == 0x9598) { breakx(); return; }
    if (m == 0x95A8) { wdr(); return; }
    if (m == 0x95C8) { lpm(); return; }
    if (m == 0x95D8) { elpm(); return; }
    if (m == 0x95E8) { spm(); return; }
    if (m == 0x95F8) { spm(); return; }


    unsigned short n = (m & 0xFF00);
    if (n == 0x0100) { movw(); return; }
    if (n == 0x0200) { muls(); return; }
    if (n == 0x0300) {
            unsigned short o = m & 0x0088;
            if (o == 0x0000) { mulsu(); return; }
            if (o == 0x0008) { fmul(); return; }
            if (o == 0x0080) { fmuls(); return; }
            if (o == 0x0088) { fmulsu(); return; }
    }
    n = m & 0xFC00; // 0b1111 11?? ???? ????
    if (n == 0x0400) { cpc(); return; }
    if (n == 0x0800) { sbc(); return; }
    if (n == 0x0C00) { add(); return; }
    if (n == 0x1000) { cpse(); return; }
    if (n == 0x1400) { cp(); return; }
    if (n == 0x1800) { sub(); return; }
    if (n == 0x1C00) { adc(); return; }
    if (n == 0x2000) { and(); return; }
    if (n == 0x2400) { eor(); return; }
    if (n == 0x2800) { or(); return; }
    if (n == 0x2C00) { mov(); return; }
    if (n == 0x9C00) { mul(); return; }
    if (n == 0xF000) { brbs(); return; }
    if (n == 0xF400) { brbc(); return; }


    n = m & 0xF000; // 0b1111 0000 0000 000
    if (n == 0x3000) { cpi(); return; }
    if (n == 0x4000) { sbci(); return; }
    if (n == 0x5000) { subi(); return; }
    if (n == 0x6000) { ori(); return; }
    if (n == 0x7000) { andi(); return; }
    if (n == 0xC000) { rjmp(); return; }
    if (n == 0xD000) { rcall(); return; }
    if (n == 0xE000) { ldi(); return; }

    n = m & 0xFE0F; // 0b1111 1110 0000 1111

    //if (n == 0x8008) { ldy(); return; } //**
    if (n == 0x9000) { lds(); return; }
    if (n == 0x9001) { ld(); return; }
    if (n == 0x9002) { ld(); return; }
    if (n == 0x9003) { reserved(); return; }
    if (n == 0x9004) { lpm(); return; }
    if (n == 0x9005) { lpm(); return; }
    if (n == 0x9006) { elpm(); return; }
    if (n == 0x9007) { elpm(); return; }
    if (n == 0x9008) { reserved(); return; }
    if (n == 0x9009) { ld(); return; }
    if (n == 0x900A) { ld(); return; }
    if (n == 0x900B) { reserved(); return; }
    if (n == 0x900C) { ld(); return; }
    if (n == 0x900D) { ld(); return; }
    if (n == 0x900E) { ld(); return; }
    if (n == 0x900F) { pop(); return; }
    if (n == 0x9200) { sts(); return; }
    if (n == 0x9201) { st(); return; }
    if (n == 0x9202) { st(); return; }
    if (n == 0x9203) { reserved(); return; }
    if (n == 0x9204) { reserved(); return; }
    if (n == 0x9205) { reserved(); return; }
    if (n == 0x9206) { reserved(); return; }
    if (n == 0x9207) { reserved(); return; }
    if (n == 0x9208) { reserved(); return; }
    if (n == 0x9209) { st(); return; }
    if (n == 0x920A) { st(); return; }
    if (n == 0x920B) { reserved(); return; }
    if (n == 0x920C) { st(); return; }
    if (n == 0x920D) { st(); return; }
    if (n == 0x920E) { st(); return; }
    if (n == 0x920F) { push(); return; }
    if (n == 0x9400) { com(); return; }
    if (n == 0x9401) { neg(); return; }
    if (n == 0x9402) { swap(); return; }
    if (n == 0x9403) { inc(); return; }
    if (n == 0x9404) { reserved(); return; }
    if (n == 0x9405) { asr(); return; }
    if (n == 0x9406) { lsr(); return; }
    if (n == 0x9407) { ror(); return; }
    if (n == 0x940A) { dec(); return; }

    n = m & 0xD200; // 0b1101 0010 0000 1000
    if (n == 0x8000) { ldd(); return; }
    if (n == 0x8200) { std(); return; }


    n = m & 0xFF8F;
    if (n == 0x9408) { bset(); return; }
    if (n == 0x9488) { bclr(); return; }


    n = m & 0xFE0E;
    if (n == 0x940C) { jmp(); return; }
    if (n == 0x940E) { call(); return; }


    n = m & 0xFF00;
    if (n == 0x9600) { adiw(); return; }
    if (n == 0x9700) { sbiw(); return; }
    if (n == 0x9800) { cbi(); return; }
    if (n == 0x9900) { sbic(); return; }
    if (n == 0x9A00) { sbi(); return; }
    if (n == 0x9B00) { sbis(); return; }

    n = m & 0xF800;
    if (n == 0xB000) { in(); return; }
    if (n == 0xB800) { out(); return; }

    n = m & 0xFE00;
    if (n == 0xF800) { bld(); return; }
    if (n == 0xFA00) { bst(); return; }
    if (n == 0xFC00) { sbrc(); return; }
    if (n == 0xFE00) { sbrs(); return; }

}


void nop() { // No Operation
    sprintf(buffer, "NOP");
};
void ijmp() { // Indirect Jump
    sprintf(buffer, "IJMP");
};
void eijmp() { // Extended Indirect Jump
    sprintf(buffer, "EIJMP");
};
void ret() {// Return from Subroutine
    sprintf(buffer, "RET");
};
void icall() { // Indirect Call to Subroutine
    sprintf(buffer, "ICALL");
};
void reti() { // Return from Interrupt
    sprintf(buffer, "RETI");
     };
void eicall() { // Extended Indirect Call to Subroutine
    sprintf(buffer, "EICALL");
};
void sleep() { // Sleep
    sprintf(buffer, "SLEEP");
};
void breakx() { // Break
    sprintf(buffer, "BREAK");
};
void wdr() { // Watchdog Reset
    sprintf(buffer, "WDR");
};
void lpm() { // Load register from program memory (from Z)
    if (m == 0x95C8) {
        sprintf(buffer, "LPM");
    } else {
        if ((m & 0xFE0E) == 0x9004) {
            unsigned char d;
            get87654(&d);
            unsigned char bit;
            get0(&bit);
            if (bit == 0) {
                sprintf(buffer, "LPM R%d, Z", d);
            } else { // bit == 1
                sprintf(buffer, "LPM R%d, Z+", d);
            }
        }
    }
};
void elpm() { // Extend load memory program
    if (m == 0x95D8) {
        sprintf(buffer, "ELPM");
    } else {
        if ((m & 0xFE0E) == 0x9006){
            unsigned char d;
            get87654(&d);
            unsigned char bit;
            get0(&bit);
            if (bit == 0) {
                sprintf(buffer, "ELPM R%d, Z", d);
            } else { // bit == 1
                sprintf(buffer, "ELPM R%d, Z+", d);
            }
        }
    }
};
void spm() { // Store Program Memory
    unsigned char bit;
    get4(&bit);
    if (bit) sprintf(buffer, "SPM Z+");
    else sprintf(buffer, "SPM");
};
void movw() { //Copy Register Word
    GET4d4r("MOVW R%u, R%u");
};
void muls() { // Multiple signed
    unsigned char d;
    unsigned char r;
    get7654(&d);
    get3210(&r);
    sprintf(buffer, "MULS R%u, R%u", d + 16, r + 16);
};
void mulsu() { // Multiply signed with unsigned
    unsigned char d;
    unsigned char r;
    get654(&d);
    get210(&r);
    sprintf(buffer, "MULSU R%u, R%u", d + 16, r + 16);
};
void fmul() { // Fractional multiply unsigned
    unsigned char d;
    unsigned char r;
    get654(&d);
    get210(&r);
    sprintf(buffer, "FMUL R%u, R%u", d + 16, r + 16);
};
void fmuls() { // Fractional multiply signed
    unsigned char d;
    unsigned char r;
    get654(&d);
    get210(&r);
    sprintf(buffer, "FMULS R%u, R%u", d + 16, r + 16);
};
void fmulsu() { // Fractional multiply signed with unsigned
    unsigned char d;
    unsigned char r;
    get654(&d);
    get210(&r);
    sprintf(buffer, "FMULSU R%u, R%u", d + 16, r + 16);
    };
void cpc() { // Compare with carry
    GET5d5r("CPC R%u, R%u");
};
void sbc() { // subtract with carry
    GET5d5r("SBC R%u, R%u");
    };
void add() { // add without carry
    GET5d5r("ADD R%u, R%u");
};
void cpse() { // Compare skip if equal
    GET5d5r("CPSE R%u, R%u");
};
void cp() { // Compare
    GET5d5r("CP R%u, R%u");
};
void sub() { // Subtract without carry
    GET5d5r("SUB R%u, R%u");
};
void adc() { // Add with carry
    GET5d5r("ADC R%u, R%u");
};
void and() { // Logical AND
    GET5d5r("AND R%u, R%u");
};
void eor() { // Exclusive OR
    GET5d5r("EOR R%u, R%u");
};
void or() { // Logical OR
    GET5d5r("OR R%u, R%u");
};
void mov() { // Copy register
    GET5d5r("MOV R%u, R%u");
};
void mul() { // Multiply Unsigned
    GET5d5r("MUL R%u, R%u");
};
void brbs() { // Branch if Bit in SREG is Set
    unsigned char k;
    unsigned char s;
    get9876543(&k);
    get210(&s);
    sprintf(buffer, "BRBS %u, %u", s, k);
};
void brbc() { // Branch if Bit in SREG is Clear
    unsigned char k;
    unsigned char s;
    get9876543(&k);
    get210(&s);
    sprintf(buffer, "BRBC %u, %u", s, k);
};
void cpi() {  // Compare with immediate
    GET4d8k("CPI R%u, %u");
};
void sbci() { // Subtract immediate with carry SBI
    GET4d8k("SBCI R%u, %u");
};
void subi() { // Substract immediate
    GET4d8k("SUBI R%u, %u");
};
void ori() { // Logical OR with immediate
    GET4d8k("ORI R%u, %u");
};
void andi() { // Logical AND with immediate
    GET4d8k("ANDI R%u, %u");
};
void rjmp() { // Relative Jump
    unsigned short k;
    getBA987654321(&k);
    unsigned char b;
    getB(&b);
    sprintf(buffer, "RJMP %d", b?k-4096:k);
};
void rcall() { // Relative Call to Subroutine
    unsigned short k;
    getBA987654321(&k);
    unsigned char b;
    getB(&b);
    sprintf(buffer, "RCALL %d", b?k-4096:k);
};
void ldi() { // Load Immediate
    unsigned char d;
    unsigned char k;
    get7654(&d);
    getBA983210(&k);
    sprintf(buffer, "LDI R%u, %u", d, k);
};
void ldd() { // Load register indirect from data space with displacement
    unsigned char d;
    get87654(&d);
    unsigned char k;
    getDBA210(&k);
    unsigned char y;
    get3(&y);
    sprintf(buffer, "LDD R%d, %c+%d", d, y==0?'Z':'Y', k);
};
void ld() { // Load Indirect from Data Space to Register
    unsigned char d, letterCode, op;
    char letter;
    get87654(&d);
    get32(&letterCode);
    get10(&op);

    switch(letterCode) {
        case 0x0:
            letter = 'Z';
            break;
        case 0x2:
            letter = 'Y';
            break;
        case 0x3:
            letter = 'X';
    }
    switch (op) {
    case 0x00:
        sprintf(buffer, "LD R%d, %c", d, letter);
        break;
    case 0x01:
        sprintf(buffer, "LD R%d, %c+", d, letter);
        break;
    case 0x2:
        sprintf(buffer, "LD R%d, -%c", d, letter);
    }
};
void lds() { // Load register direct from data space
    unsigned char d;
    get87654(&d);
    fetchMemory(&w);
    sprintf(buffer, "LDS R%d, %d", d, w);
    };
void reserved() { sprintf(buffer, "*RESERVED*"); };
void pop() { // Pop Register from Stack
    unsigned char d;
    get87654(&d);
    sprintf(buffer, "POP R%u", d);
};
void sts() { // Store Direct to Data Space
    unsigned char d;
    get87654(&d);
    fetchMemory(&w);
    sprintf(buffer, "STS %d, R%d", w, d);
};
void st() { // Store Indirect From Register to Data Space
    unsigned char d, letterCode, op;
    char letter;
    get87654(&d);
    get32(&letterCode);
    get10(&op);

    switch(letterCode) {
        case 0x0:
            letter = 'Z';
            break;
        case 0x2:
            letter = 'Y';
            break;
        case 0x3:
            letter = 'X';
    }
    switch (op) {
    case 0x00:
        sprintf(buffer, "ST %c, R%d", letter, d);
        break;
    case 0x01:
        sprintf(buffer, "ST %c+, R%d", letter, d);
        break;
    case 0x2:
        sprintf(buffer, "ST -%c, R%d", letter, d);
    }
};
void push() { // Push Register on Stack
    unsigned char d;
    get87654(&d);
    sprintf(buffer, "PUSH R%u", d);
};
void com() { // One’s Complement
    unsigned char d;
    get87654(&d);
    sprintf(buffer, "COM R%u", d);
};
void neg() { // Two’s Complement
    unsigned char d;
    get87654(&d);
    sprintf(buffer, "NEG R%u", d);
};
void swap() { // Swap Nibbles
    unsigned char d;
    get87654(&d);
    sprintf(buffer, "SWAP R%u", d);
};
void inc() { // Increment
    unsigned char d;
    get87654(&d);
    sprintf(buffer, "INC R%u", d);
};
void asr() { // Arithmetic Shift Right
    unsigned char d;
    get87654(&d);
    sprintf(buffer, "ASR R%u", d);
};
void lsr() { // Logical Shift Right
    unsigned char d;
    get87654(&d);
    sprintf(buffer, "LSR R%u", d);
};
void ror() { // Rotate Right through Carry
    unsigned char d;
    get87654(&d);
    sprintf(buffer, "ROR R%d", d);
};
void dec() { // Decrement
    unsigned char d;
    get87654(&d);
    sprintf(buffer, "DEC R%u", d);
};
void std() { // Store Indirect From Register to Data Space
    unsigned char d;
    get87654(&d);
    unsigned char k;
    getDBA210(&k);
    unsigned char y;
    get3(&y);
    sprintf(buffer, "STD R%d, %c+%d", d, y==0?'Z':'Y', k);
    };
void bset() { // Bit Set in SREG
    unsigned char s;
    get654(&s);
    sprintf(buffer, "BSET %u", s);
};
void bclr() { // Bit Clear in SREG
    unsigned char s;
    get654(&s);
    sprintf(buffer, "BCLR %u", s);
};
void jmp() { // Jump
    unsigned char k;
    unsigned int t;
    get876540(&k);
    fetchMemory(&w);
    t = ((unsigned int)k << 16) + w;
    sprintf(buffer, "JMP %u", t); };
void call() { // Long Call to a Subroutine
    unsigned char k;
    unsigned int t;
    get876540(&k);
    fetchMemory(&w);
    t = (k << 16) + w;
    sprintf(buffer, "CALL %u", t);
};
void adiw() { // Add Immediate to Word
    unsigned char d;
    unsigned char k;
    unsigned char reg;
    get54(&d);
    switch(d) {
    case 0x0:
        reg = 24;
        break;
    case 0x1:
        reg = 26;
        break;
    case 0x2:
        reg = 28;
        break;
    case 0x3:
        reg = 30;
    }
    get763210(&k);
    sprintf(buffer, "ADIW R%u, %u", reg, k);
    };
void sbiw() { // Subtract Immediate from Word
    unsigned char d;
    unsigned char k;
    unsigned char reg;
    get54(&d);
    switch(d) {
    case 0x0:
        reg = 24;
        break;
    case 0x1:
        reg = 26;
        break;
    case 0x2:
        reg = 28;
        break;
    case 0x3:
        reg = 30;
    }
    get763210(&k);
    sprintf(buffer, "SBIW R%u, %u", reg, k);
};
void cbi() { // Clear Bit in I/O Register
    unsigned char a;
    unsigned char b;
    get76543(&a);
    get210(&b);
    sprintf(buffer, "CBI %u, %u", a, b);
};
void sbic() { // Skip if Bit in I/O Register is Cleared
    unsigned char a;
    unsigned char b;
    get76543(&a);
    get210(&b);
    sprintf(buffer, "SBIC %u, %u", a, b);
};
void sbi() { // Set Bit in I/O Register
    unsigned char a;
    unsigned char b;
    get76543(&a);
    get210(&b);
    sprintf(buffer, "SBI %u, %u", a, b);
};
void sbis() { // Skip if Bit in I/O Register is Set
    unsigned char a;
    unsigned char b;
    get76543(&a);
    get210(&b);
    sprintf(buffer, "SBIS %u, %u", a, b);
};
void in() { // Load an I/O Location to Register
    unsigned char d;
    unsigned char a;
    get87654(&d);
    getA93210(&a);
    sprintf(buffer, "IN R%u, %u", d, a);
};
void out() { // Store Register to I/O Location
    unsigned char d;
    unsigned char a;
    get87654(&d);
    getA93210(&a);
    sprintf(buffer, "OUT R%u, %u", d, a);
};
void bld() { // Bit Load from the T Flag in SREG to a Bit in Register
    unsigned char d;
    unsigned char b;
    get87654(&d);
    get210(&b);
    sprintf(buffer, "BLD R%u, %u", d, b);
    };
void bst() { //  Bit Store from Bit in Register to T Flag in SREG
    unsigned char d;
    unsigned char b;
    get87654(&d);
    get210(&b);
    sprintf(buffer, "BST R%u, %u", d, b);
};
void sbrc() { // Skip if Bit in Register is Cleared
    unsigned char r;
    unsigned char b;
    get87654(&r);
    get210(&b);
    sprintf(buffer, "SBRC R%u, %u", r, b);
};
void sbrs() { // Skip if Bit in Register is Set
    unsigned char r;
    unsigned char b;
    get87654(&r);
    get210(&b);
    sprintf(buffer, "SBRS R%u, %u", r, b);
};


void get0(unsigned char *b) {
    *b = m & 0x1;
}
void get10(unsigned char *b) {
    *b = m & 0x3;
}
void get654(unsigned char *b) {
    *b = (m & 0x70) >> 4;
}
void get210(unsigned char *b) {
    *b = m & 0x7;
}
void get3210(unsigned char *b) {
    *b = m & 0xF;
}
void get7654(unsigned char *b) {
    *b = (m & 0xF0) >> 4;
}
void get87654(unsigned char *b) {
    *b = (m & 0x01F0) >> 4;
}
void get93210(unsigned char *b) {
    *b = ((m & 0x200) >> 5) + (m & 0xF);
}
void getBA983210(unsigned char *b) {
    *b = ((m & 0xF00) >> 4) + (m & 0xF);
}
void get4(unsigned char *b) {
    *b = (m & 0x10) > 4;
}
void get3(unsigned char *b) {
    *b = (m & 0x8) >> 3;
}
void getBA210(unsigned char *b) {
    *b = ((m & 0xC00) >> 7) + (m & 7);
}
void get32(unsigned char *b) {
    *b = (m & 0xC) >> 2;
}
void get54(unsigned char *d) {
    *d = (m & 0x30) >> 4;
}
void get763210(unsigned char *k) {
    *k = ((m & 0xC0) >> 2) + (m & 0xF);
}
void get876540(unsigned char *k) {
    *k = ((m & 0x1F0) >> 3) + (m & 0x1);
}
void get76543(unsigned char *a) {
    *a = (m & 0xF8) >> 3;
}
void getA93210(unsigned char *a) {
    *a = ((m & 0x600) >> 5) + (m & 0xF);
}
void getBA987654321(unsigned short *k) {
    *k = m & 0xFFF;
}
void get9876543(unsigned char *k) {
    *k = (m & 0x3F8) >> 3;
}
void getDBA210(unsigned char *k){
    *k = ((m & 0x2000) >> 8) + ((m & 0xC00) >> 7) + (m & 7);
}
void getB(unsigned char *b) {
    *b = (m & 0x800) >> 10;
}
