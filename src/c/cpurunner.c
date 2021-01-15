#include "../h/decode.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include <math.h>

unsigned char memory[0x10000];
unsigned char pc = 0;
unsigned char grlRegister[0x20];
unsigned short *xregister = (unsigned short *)(grlRegister+0x1A);
unsigned short *yregister = (unsigned short *)(grlRegister+0x1C);
unsigned short *zregister = (unsigned short *)(grlRegister+0x1E);

extern unsigned short m, w;
extern char buffer[80];

void testGetter1();
void testGetter2();
void testGetter3();
void testGetter4();
void testGetter5();
void testGetter6();
void testGetter7();
void testGetter8();
void testGetter9();
void testGetter10();
void testRunner();

char* testInput[] = {
    "NOP",         "0000 0000 0000 0000",
    "MOVW Rd, Rr",        "0000 0001 dddd rrrr", // d = destination register pair (0,2,..30) r = source register pair (0,2,..30)
    "MULS Re, Rt",        "0000 0010 eeee tttt", // e = multiplicand 1 (16..31) t = multiplicand 2 (16..31)
    "MULSU Re, Rt",       "0000 0011 0eee 0ttt", // e = signed multiplicand (16..32) t = unsigned multiplicand (16..32)
    "FMUL Re, Rt",        "0000 0011 0eee 1ttt", // e = multiplicand register (16..23) t = multiplicand register (16..23)
    "FMULS Re, Rt",       "0000 0011 1eee 0ttt", // e = multiplicand register (16..23) t = multiplicand register (16..23)
    "FMULSU Re, Rt",      "0000 0011 1eee 1ttt", // e = signed multiplicand register (16..23) t = unsigned multiplicand register (16..23)
    "CPC Rd, Rr",         "0000 01rd dddd rrrr", // d = register A to be compared thru carry (0..31) r = register B to be compared thru carry (0..31)
    "SBC Rd, Rr",         "0000 10rd dddd rrrr", // d = destination register (0..31) r = source register (0..31)
    "ADD Rd, Rr",         "0000 11rd dddd rrrr", // d = destination register (0..31) r = source register (0..31)
    "CPSE Rd, Rr",        "0001 00rd dddd rrrr", // d = register A to be compared (0..31) r = register B to be compared (0..31)
    "CP Rd, Rr",          "0001 01rd dddd rrrr", // d = register A to be compared (0..31) r = register B to be compared (0..31)
    "SUB Rd, Rr",         "0001 10rd dddd rrrr", // d = destination register (0..31) r = source register (0..31)
    "ADC Rd, Rr",         "0001 11rd dddd rrrr", // d = destination register (0..31) r = source register (0..31)
    "AND Rd, Rr",         "0010 00rd dddd rrrr", // d = destination register (0..31) r = source register (0..31)
    "EOR Rd, Rr",         "0010 01rd dddd rrrr", // d = destination register (0..31) r = source register (0..31)
    "OR Rd, Rr",          "0010 10rd dddd rrrr", // d = destination register (0..31) r = source register (0..31)
    "MOV Rd, Rr",         "0010 11rd dddd rrrr", // d = destination register (0..31) r = source register (0..31)
    "CPI Re, k",         "0011 kkkk eeee kkkk", // e = register to be compared (16..31) K = constant to be compared (0..255)
    "SBCI Re, k",        "0100 kkkk eeee kkkk", // e = destination register (16..31) K = immediate constant (0..255)
    "SUBI Re, k",        "0101 kkkk eeee kkkk", // e = destination register (16..31) K = immediate constant (0..255)
    "ORI Re, k",         "0110 kkkk eeee kkkk", // e = destination register (16..31) K = immediate constant (0..255)
    "ANDI Re, k",        "0111 kkkk eeee kkkk", // e = destination register (16..31) K = constant (0..255)
    "LDD Rd, Z+q", "10q0 qq0d dddd 0qqq", // d = destination register (0..31) q = offset (0..63)
    "LDD Rd, Y+q", "10q0 qq0d dddd 1qqq", // d = destination register (0..31) q = offset (0..63)
    "STD Rd, Z+q", "10q0 qq1r rrrr 0qqq", // r = source register (0..31) q = offset (0..31), p = pointer (Z or Y)
    "STD Rd, Y+q", "10q0 qq1r rrrr 1qqq", // r = source register (0..31) q = offset (0..31), p = pointer (Z or Y)
    "LDS Rd, k",         "1001 000d dddd 0000 kkkk kkkk kkkk kkkk", // d = destination register (0..31), k = address to fetch (0..65535)
    "LPM Rd, Z",   "1001 000d dddd 0100", // d = destination register (0..31)
    "LPM Rd, Z+",  "1001 000d dddd 0101", // d = destination register (0..31)
    "ELPM Rd, Z",  "1001 000d dddd 0110", // d = destination register (0..31)
    "ELPM Rd, Z+", "1001 000d dddd 0111", // d = destination register (0..31)
    "LD Rd, X",    "1001 000d dddd 1100", // d = destination register (0..31)
    "LD Rd, Z+",   "1001 000d dddd 0001", // d = destination register (0..31)
    "LD Rd, -Z",   "1001 000d dddd 0010", // d = destination register (0..31)
    "LD Rd, Y+",   "1001 000d dddd 1001", // d = destination register (0..31)
    "LD Rd, -Y",   "1001 000d dddd 1010", // d = destination register (0..31)
    "LD Rd, X+",   "1001 000d dddd 1101", // d = destination register (0..31)
    "LD Rd, -X",   "1001 000d dddd 1110", // d = destination register (0..31)
    "POP Rd",         "1001 000d dddd 1111", // d = destination register (0..31)
    "STS k, Rd",         "1001 001d dddd 0000 kkkk kkkk kkkk kkkk", // d = source register (0..31) k = address to store (0..65535)
    "ST X, Rr",    "1001 001r rrrr 1100", // r = source register (0..31)
    "ST Z+, Rr",   "1001 001r rrrr 0001", // r = source register (0..31)
    "ST -Z, Rr",   "1001 001r rrrr 0010", // r = source register (0..31)
    "ST Y+, Rr",   "1001 001r rrrr 1001", // r = source register (0..31)
    "ST -Y, Rr",   "1001 001r rrrr 1010", // r = source register (0..31)
    "ST X+, Rr",   "1001 001r rrrr 1101", // r = source register (0..31)
    "ST -X, Rr",   "1001 001r rrrr 1110", // r = source register (0..31)
    "PUSH Rd",        "1001 001d dddd 1111", // d = destination register (0..31)
    "COM Rd",         "1001 010d dddd 0000", // d = register to be 1's complemented (0..31)
    "SWAP Rd",        "1001 010d dddd 0010", // d = register to swap nibbles in (0..31)
    "NEG Rd",         "1001 010d dddd 0001", // d = register to be 2's complemented (0..31)
    "INC Rd",         "1001 010d dddd 0011", // d = destination register (0..31)
    "ASR Rd",         "1001 010d dddd 0101", // d = destination register (0..31)
    "LSR Rd",         "1001 010d dddd 0110", // d = destination register (0..31)
    "ROR Rd",         "1001 010d dddd 0111", // d = destination register (0..31)
    "BSET s",        "1001 0100 0sss 1000", // s = bit in SREG to set (0..7)
    "IJMP",        "1001 0100 0000 1001",
    "EIJMP",       "1001 0100 0001 1001",
    "DEC Rd",         "1001 010d dddd 1010", // d = destination register (0..31)
    "BCLR s",         "1001 0100 1sss 1000", // s = bit in SREG to clear (0..7)
    "JMP k",         "1001 010k kkkk 110k kkkk kkkk kkkk kkkk", // k = absolute address to jump to (0..4,194,304)
    "CALL k",        "1001 010k kkkk 111k kkkk kkkk kkkk kkkk", // k = absolute address to jump to (0..4,194,304)
    "RET",         "1001 0101 0000 1000",
    "ICALL",       "1001 0101 0000 1001",
    "RETI",        "1001 0101 0001 1000",
    "EICALL",      "1001 0101 0001 1001",
    "SLEEP",       "1001 0101 1000 1000",
    "BREAK",       "1001 0101 1001 1000",
    "WDR",         "1001 0101 1010 1000",
    "LPM",         "1001 0101 1100 1000",
    "ELPM",        "1001 0101 1101 1000",
    "SPM",         "1001 0101 1110 1000",
    "SPM Z+",      "1001 0101 1111 1000",
    "ADIW Rj, k",  "1001 0110 kkjj kkkk", // j = destination register pair (24:25, 26:27, 28:29, 30:31) K = constant (0..63)
    "SBIW Rj, k",  "1001 0111 kkjj kkkk", // j   = destination register pair (24:25, 26:27, 28:29, 30:31) K = constant (0..63)
    "CBI a, b",         "1001 1000 aaaa abbb", // a = destination I/O register (0..31) b = bit in I/O register to clear (0..7)
    "SBIC a, b",        "1001 1001 aaaa abbb", // a = I/O register to inspect (0..31) b = bit in I/O register to test to determine branch
    "SBI a, b",         "1001 1010 aaaa abbb", // a = destination I/O register (0..31) b = bit in I/O register to set (0..7)
    "SBIS a, b",        "1001 1011 aaaa abbb", // a = I/O register to inspect (0..31) b = bit in I/O register to test to determine branch
    "MUL Rd, Rr",         "1001 11rd dddd rrrr", // d = multiplicand 1 (0..31) r = multiplicand 2 (0..31)
    "IN Rd, a",          "1011 0aad dddd aaaa", // d = destination register (0..31) A = source I/O port (0..63)
    "OUT Rd, a",         "1011 1aar rrrr aaaa", // r = source register (0..31) A = destination I/O port (0..63)
    "RJMP l",        "1100 llll llll llll", // k = offset to jump to (-2048 to +2047)
    "RCALL l",       "1101 llll llll llll", // k = offset to jump to (-2048 to +2047)
    "LDI Rd, k",         "1110 kkkk dddd kkkk", // d = destination register (0..31) K = immediate constant (0..255)
    "BRBS s, k",        "1111 00kk kkkk ksss", // s = bit in SREG to test (0..7) k = offset to jump by if bit is set
    "BRBC s, k",        "1111 01kk kkkk ksss", // s = bit in SREG to test (0..7) k = offset to jump by if bit is clear (-63..64)
    "BST Rd, b",         "1111 101d dddd 0bbb", // d = source register (0..31) b = bit in source register to copy into the T bit (0..7)
    "BLD Rd, b",         "1111 100d dddd 0bbb", // d = destination register (0..31) b = bit in destination register to transfer T bit into (0..7)
    "SBRC Rr, b",        "1111 110r rrrr 0bbb", // r = register to inspect (0..31) b = bit in register to test to determine branch (0..7)
    "SBRS Rr, b",        "1111 111r rrrr 0bbb", // r = register to inspect (0..31) b = bit in register to test to determine branch (0..7)
    "@Fin"
};


int findVar(char* p, char* lineVar );

void binaryStrToMem(char* pChar, char line[], unsigned char size[], int counter[]){
    int total = 0;
    unsigned char memPos = 0;
    unsigned char count = 0;

    int tempCounter[3];
    int exponent[3];
    for (unsigned char i = 0; i < 3; ++i){
        if (size[i] != 0) {
            exponent[i] = 0x1 << (size[i] - 1);
            tempCounter[i] = counter[i];
        } else {
            tempCounter[i] = 0;
            exponent[i] = 0;
        }
    }

    while (*pChar) {
        if (*pChar != ' ' ) {
            total *= 2;
            ++count;
            if (*pChar == '1') ++total;
            else {
                int pos = findVar(pChar, line);
                if (pos != -1) {
                    if (tempCounter[pos] >= exponent[pos]) {
                        ++total;
                        tempCounter[pos] -= exponent[pos];
                    }
                    exponent[pos] >>= 1;
                }
            }
        }
        ++pChar;
        if (count == 16 || *pChar == '\0') {
            memory[memPos] = (unsigned char)(total & 0xFF);
            memory[memPos + 1] = (unsigned char)(total / 0x100) & 0xFF;
            memPos += 2;
            total = 0;
            count = 0;
        }
    }
}

int main() {
    grlRegister[0x1A] = 1;
    grlRegister[0x1B] = 2;
    grlRegister[0x1C] = 3;
    grlRegister[0x1D] = 4;
    grlRegister[0x1E] = 5;
    grlRegister[0x1F] = 6;

    printf("xregister: %xh\n", *xregister);
    printf("yregister: %xh\n", *yregister);
    printf("zregister: %xh\n", *zregister);

    testGetter1();
    testGetter2();
    testGetter3();
    testGetter4();
    testGetter5();
    testGetter6();
    testGetter7();
    testGetter8();
    testGetter9();
    testGetter10();
    testRunner();
    return 0;
}

void testGetter1() {
    m = 0xFFFF;
    unsigned char rrrr;
    get3210(&rrrr);
    if (rrrr == 0xF) printf("get3210() check ok.\n");
    else { printf("get3210() check fail.\n"); };
}
void testGetter2() {
    m = 0xFFFF;
    unsigned char dddd;
    get7654(&dddd);
    if (dddd == 0xF) printf("get7654() check ok.\n");
    else printf("get7654() check fail.\n");
}
void testGetter3() {
    m = 0xFFFF;
    unsigned char ddddd;
    get87654(&ddddd);
    if (ddddd == 0x1F) printf("get87654() check ok.\n");
    else printf("get87654() check fail.\n");
}
void testGetter4() {
    m = 0xFFFF;
    unsigned char rrrrr;
    get93210(&rrrrr);
    if (rrrrr == 0x1F) printf("get93210() check ok.\n");
    else printf("get93210() check fail.\n");
}
void testGetter5() {
    unsigned char ddd;
    get654(&ddd) ;
    if (ddd == 0x7) printf("get654() check ok.\n");
    else printf("get654() check fail.\n");
}
void testGetter6() {
    unsigned char ddd;
    get210(&ddd);
    if (ddd == 0x7) printf("get210() check ok.\n");
    else printf("get210() check fail.\n");
}
void testGetter7() {
    unsigned char ddd;
    getBA983210(&ddd);
    if (ddd == 0xFF) printf("getBA983210() check ok.\n");
    else printf("get210() check fail.\n");
}
void testGetter8() {
    unsigned char p;
    get3(&p);
    if (p == 0x1) printf("get3() check ok.\n");
    else printf("get3() check fail.\n");
}
void testGetter9() {
    unsigned char k;
    getBA210(&k);
    if (k == 0x1F) printf("getBA210() check ok.\n");
    else printf("getBA210() check fail.\n");
}
void testGetter10() {
    unsigned char bit;
    get0(&bit);
    if (bit == 0x1) printf("get0() check ok.\n");
    else printf("get0() check fail.\n");
}


int findVar(char* p, char* lineVar ) {
    if (*p == lineVar[0]) return 0;
    if (*p == lineVar[1]) return 1;
    if (*p == lineVar[2]) return 2;
    return -1;
}

void testRunner() {
    int proofPos = 0;
    int proofNumber = 0;
    char* buffer1 = malloc(100);

    while (strcmp(testInput[proofPos], "@Fin")) {
        char* line = testInput[proofPos]; proofPos++;

        char lineVar[3] = { 0x0, 0x0, 0x0}; int pos = 0;
        unsigned char sizeVar[3] = { 0x0, 0x0, 0x0};
        int counterVar[3] = { 0x0, 0x0, 0x0};
        bool repeat = true;
        char* pointer = line;
        while(*pointer != '\0') {
            if (islower(*pointer)) {
                lineVar[pos] = *pointer;
                ++pos;
            }
            ++pointer;
        }

        char* codeStr = testInput[proofPos]; proofPos++;

        pointer = codeStr;
        while(*pointer != '\0') {
            ++sizeVar[findVar(pointer, lineVar)];
            ++pointer;
        }
        counterVar[0] = pow(2, sizeVar[0]) - 1;
        counterVar[1] = pow(2, sizeVar[1]) - 1;
        counterVar[2] = pow(2, sizeVar[2]) - 1;

        printf("Proof number: %x. Input: %s -> %s. \n",proofNumber, codeStr, line);
        while(repeat) {
            char* dest = buffer1;
            pointer = line;
            while (*pointer != 0x0) {
                if (!islower(*pointer)) {
                    *dest = *pointer;
                    ++dest;
                } else {
                    int value = counterVar[findVar(pointer, lineVar)];
                    if (*pointer == 'p') {
                        if (value == 0x0) dest += sprintf(dest, "Z");
                        else if (value == 0x1) dest += sprintf(dest, "Y");
                    } else if (*pointer == 'e' || *pointer == 't') {
                        dest += sprintf(dest, "%u", 16 + value);
                    } else if (*pointer == 'j') {
                        dest += sprintf(dest, "%u", 24 + value * 2);
                    } else if (*pointer == 'l') {
                        dest += sprintf(dest, "%d", value > 2047 ? -(4096 - value): value);
                    } else {
                        dest += sprintf(dest, "%u", value);
                    }
                }
                ++pointer;
            }
            *dest = 0x0;
            ++dest;

            binaryStrToMem(codeStr, lineVar, sizeVar, counterVar);
            pc = 0;

            decode();

            if (strcmp(buffer, buffer1) == 0) {
//                printf("Proof number: %x. Input: %s -> %s. ",proofNumber, codeStr, buffer1);
//                printf("Correct.\n");
            } else {
                printf("Proof number: %x. Input: %s -> %s. ",proofNumber, codeStr, buffer1);
                printf("Fail.\n");
                printf("Output: %s\n", buffer);
                printf("Memory[0] = %x; Memory[1] = %x\n", memory[0], memory[1]);
                printf("Memory[2] = %x; Memory[3] = %x\n\n", memory[2], memory[3]);
            }
            ++proofNumber;

            if (counterVar[0] == 0) {
                if (counterVar[1] == 0) {
                    if (counterVar[2] == 0) {
                        repeat = false;
                    } else {
                        --counterVar[2];
                    }
                    counterVar[1] = pow(2, sizeVar[0]) - 1;
                } else {
                    --counterVar[1];
                }
                counterVar[0] = pow(2, sizeVar[0]) - 1;
            } else {
                --counterVar[0];
            }
        }

    }
    free(buffer1);
}
