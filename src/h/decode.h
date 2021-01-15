#ifndef DECODE_H_INCLUDED
#define DECODE_H_INCLUDED

char buffer[80];
unsigned short m, w;

void fetchMemory(unsigned short *m);
void decode();

//int findVar(char* p, char* lineVar);

void get654(unsigned char *d);
void get210(unsigned char *d);
void get3210(unsigned char *b);
void get7654(unsigned char *b);
void get87654(unsigned char *b);
void get93210(unsigned char *b);
void getBA983210(unsigned char *b);
void getBA210(unsigned char *b);
void get4(unsigned char *b);
void get3(unsigned char *b);
void get32(unsigned char *b);
void get0(unsigned char *b);
void get10(unsigned char *b);
void get54(unsigned char *d);
void get763210(unsigned char *k);
void get876540(unsigned char *k);
void get76543(unsigned char *a);
void getA93210(unsigned char *a);
void getBA987654321(unsigned short *k);
void get9876543(unsigned char *k);
void getDBA210(unsigned char *k);
void getB(unsigned char *b);

#define GET3d3r( str ) \
    unsigned char d; \
    unsigned char r; \
    get654(&d); \
    get210(&r); \
    sprintf(buffer, str, d, r);

#define GET4d4r( str ) \
    unsigned char d; \
    unsigned char r; \
    get7654(&d); \
    get3210(&r); \
    sprintf(buffer, str, d, r);

#define GET5d5r( str ) \
    unsigned char d; \
    unsigned char r; \
    get87654(&d); \
    get93210(&r); \
    sprintf(buffer, str, d, r);

#define GET4d8k( str ) \
    unsigned char d; \
    unsigned char k; \
    get7654(&d); \
    getBA983210(&k); \
    sprintf(buffer, str, d + 16, k);


void nop(); // No Operation
void ijmp(); // Indirect Jump
void eijmp(); // Extended Indirect Jump
void ret(); // Return from Subroutine
void icall(); // Indirect Call to Subroutine
void reti(); // Return from Interrupt
void eicall(); // Extended Indirect Call to Subroutine
void sleep(); // Sleep
void breakx(); // Break
void wdr(); // Watchdog Reset
void lpm(); // Load register from program memory (from Z)
void elpm(); // Extend load memory program
void spm(); // Store Program Memory
void movw(); //Copy Register Word
void muls(); // Multiple signed
void mulsu(); // Multiply signed with unsigned
void fmul(); // Fractional multiply unsigned
void fmuls(); // Fractional multiply signed
void fmulsu(); // Fractional multiply signed with unsigned
void cpc(); // Compare with carry
void sbc(); // subtract with carry
void add(); // add without carry
void cpse();  // Compare skip if equal
void cp(); // Compare
void sub(); // Subtract without carry
void adc(); // Add with carry
void and(); // Logical AND
void eor(); // Exclusive OR
void or(); // Logical OR
void mov(); // Copy register
void mul(); // Multiply Unsigned
void brbs(); // Branch if Bit in SREG is Set
void brbc(); // Branch if Bit in SREG is Clear
void cpi(); // Compare with immediate
void sbci(); // Subtract immediate with carry SBI
void subi(); // Substract immediate
void ori(); // Logical OR with immediate
void andi(); // Logical AND with immediate
void rjmp(); // Relative Jump
void rcall(); // Relative Call to Subroutine
void ldi(); // Load Immediate
void ldd(); // Load register indirect from data space with displacement
void ld(); // Load Indirect from Data Space to Register
void lds(); // Load register direct from data space
void reserved();
void pop(); // Pop Register from Stack
void sts(); // Store Direct to Data Space
void st(); // Store Indirect From Register to Data Space
void push(); // Push Register on Stack
void com(); // One’s Complement
void neg(); // Two’s Complement
void swap(); // Swap Nibbles
void inc(); // Increment
void asr(); // Arithmetic Shift Right
void lsr(); // Logical Shift Right
void ror(); // Rotate Right through Carry
void dec(); // Decrement
void std(); // Store Indirect From Register to Data Space
void bset(); // Bit Set in SREG
void bclr(); // Bit Clear in SREG
void jmp(); // Jump
void call(); // Long Call to a Subroutine
void adiw(); // Add Immediate to Word
void sbiw(); // Subtract Immediate from Word
void cbi(); // Clear Bit in I/O Register
void sbic(); // Skip if Bit in I/O Register is Cleared
void sbi(); // Set Bit in I/O Register
void sbis(); // Skip if Bit in I/O Register is Set
void in(); // Load an I/O Location to Register
void out(); // Store Register to I/O Location
void bld(); // Bit Load from the T Flag in SREG to a Bit in Register
void bst(); //  Bit Store from Bit in Register to T Flag in SREG
void sbrc(); // Skip if Bit in Register is Cleared
void sbrs(); // Skip if Bit in Register is Set

#endif // DECODE_H_INCLUDED
