#pragma once

#include <vector>
#include <iostream>
#include <iomanip>
#include <cstdint>
#include <functional>

// registers
#define zero  0   // hardwired zero
#define ra    1   // return address
#define sp    2   // stack pointer
#define gp    3   // global pointer
#define tp    4   // thread pointer
#define t0    5   // temporary register 0
#define t1    6   // temporary register 1
#define t2    7   // temporary register 2
#define s0    8   // saved register 0 / frame pointer
#define fp    8   // saved register 0 / frame pointer
#define s1    9   // saved register 1
#define a0    10  // function argument 0 / return value 0
#define a1    11  // function argument 1 / return value 1
#define a2    12  // function argument 2
#define a3    13  // function argument 3
#define a4    14  // function argument 4
#define a5    15  // function argument 5
#define a6    16  // function argument 6
#define a7    17  // function argument 7
#define s2    18  // saved register 2
#define s3    19  // saved register 3
#define s4    20  // saved register 4
#define s5    21  // saved register 5
#define s6    22  // saved register 6
#define s7    23  // saved register 7
#define s8    24  // saved register 8
#define s9    25  // saved register 9
#define s10   26  // saved register 10
#define s11   27  // saved register 11
#define t3    28  // temporary register 3
#define t4    29  // temporary register 4
#define t5    30  // temporary register 5
#define t6    31  // temporary register 6

// opcodes
#define LUI_OP      0b0110111 // lui
#define AUIPC_OP    0b0010111 // aiupc
#define JAL_OP      0b1101111 // jal
#define JALR_OP     0b1100111 // jalr
#define BRANCH_OP   0b1100011 // beq, bne, blt, bge, bltu, bgeu
#define LOAD_OP     0b0000011 // lb, lh, lw, lbu, lhu
#define STORE_OP    0b0100011 // sb, sh, sw
#define ITYPE_OP    0b0010011 // addi, slti, sltiu, xori, ori, andi, slli, srli, srai, 
#define RTYPE_OP    0b0110011 // add, sub, sll, slt, sltu, xor, srl, sra, or, and
#define FENCE_OP    0b0001111 // fence
#define SYSCALL_OP  0b1110011 // ecall, ebreak

using byte_t = uint8_t;
using hword_t = uint16_t;
using word_t = uint32_t;
using dword_t = uint64_t;
using uop = uint8_t;
