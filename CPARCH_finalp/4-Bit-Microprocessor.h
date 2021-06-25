#ifndef _4241_H
#define _4241_H

// 4241 4-bit Microprocessor
//
// Registers: r0 r1
//
// 1-byte Instructions
// 0 = Halt
// 1 = Add (r0 = r0 + r1)
// 2 = Subtract (r0 = r0 - r1)
// 3 = Increment r0 
// 4 = Increment r1
// 5 = Decrement r0
// 6 = Decrement r1
// 7 = Swap registers and ring bell.
// 
// 2-byte Instructions; Next byte interpreted as <data>
// 8  = Print <data> (as a number)
// 9  = Load value at address <data> into r0
// 10 = Load value at address <data> into r1
// 11 = Store r0 into address <data>
// 12 = Store r1 into address <data>
// 13 = Jump to address <data>
// 14 = Jump to address <data> if r0 == 0
// 15 = Jump to address <data> if r0 != 0

typedef unsigned char byte;

typedef struct {
    byte r0;
    byte r1;
    byte mem[16];
} processor;

typedef struct {
    byte cur;
    byte halt;
} program_state_t;

program_state_t instruction(processor * p, program_state_t state);

processor * run(byte memory[]);

#endif