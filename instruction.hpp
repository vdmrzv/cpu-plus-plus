#pragma once

#include <cstdint>
#include <bitset>
#include <iostream>
#include <iomanip>

#include "common.hpp"

#define opcode_mask 0x7f  
#define funct3_mask 0x7000
#define funct7_mask 0xfe000000

#define rtype_rd_mask     0xf80   // 0b11111 << 7
#define rtype_funct3_mask 0x7000  // 0b111 << 12
#define rtype_rs1_mask    0xf8000 // 0b11111 << 15
#define rtype_rs2_mask    0b11111   << 20
#define rtype_funct7_mask 0b1111111 << 25

#define itype_rd_mask     0xf80       // 0b11111 << 7
#define itype_funct3_mask 0x7000      // 0b111 << 12
#define itype_rs1_mask    0xf8000     // 0b11111 << 15
#define itype_imm_mask    0xfff00000  // 0b111111111111 << 20

#define stype_imm4_0_mask   0b11111   << 7
#define stype_funct3_mask   0b111     << 12
#define stype_rs1_mask      0b11111   << 15
#define stype_rs2_mask      0b11111   << 20
#define stype_imm11_5_mask  0b1111111 << 25

#define btype_rd_mask     0b11111         << 7
#define btype_funct3_mask 0b111           << 12
#define btype_rs1_mask    0b11111         << 15
#define btype_rs2_mask    0b11111         << 20
#define btype_funct7_mask 0b1111111       << 25

#define utype_rd_mask     0b11111         << 7
#define utype_funct3_mask 0b111           << 12
#define utype_rs1_mask    0b11111         << 15
#define utype_rs2_mask    0b11111         << 20
#define utype_funct7_mask 0b1111111       << 25

#define jtype_rd_mask     0b11111         << 7
#define jtype_funct3_mask 0b111           << 12
#define jtype_rs1_mask    0b11111         << 15
#define jtype_rs2_mask    0b11111         << 20
#define jtype_funct7_mask 0b1111111       << 25

enum InstructionType {
  R, I, S, B, U, J  
};

struct InstructionTypeR {
  uint8_t opcode; // : 7 bits
  uint8_t rd;     // : 5 bits
  uint8_t funct3; // : 3 bits
  uint8_t rs1;    // : 5 bits
  uint8_t rs2;    // : 5 bits
  uint8_t funct7; // : 7 bits
};

struct InstructionTypeI {
  uint8_t opcode; // : 7 bits
  uint8_t rd;     // : 5 bits
  uint8_t funct3; // : 3 bits
  uint8_t rs1;    // : 5 bits
  uint16_t imm;   // : 12 bits
};

struct InstructionTypeS {
  uint8_t opcode;   // : 7 bits
  uint8_t imm4_0;   // : 5 bits
  uint8_t funct3;   // : 3 bits
  uint8_t rs1;      // : 5 bits
  uint8_t rs2;      // : 5 bits
  uint8_t imm11_5;  // : 7 bits
};

struct InstructionTypeB {
  uint8_t opcode;   // : 7 bits
  uint8_t imm4_0;   // : 5 bits
  uint8_t funct3;   // : 3 bits
  uint8_t rs1;      // : 5 bits
  uint8_t rs2;      // : 5 bits
  uint8_t imm11_5;  // : 7 bits
};

InstructionTypeR parse_rtype(word_t word) {
  // return TypeR {
  //   opcode = (word & opcode_mask);
  //   rd =     (word & rtype_rd_mask)      >> 7;
  //   funct3 = (word & rtype_funct3_mask)  >> 12;
  //   rs1 =    (word & rtype_rs1_mask)     >> 15;
  //   rs2 =    (word & rtype_rs2_mask)     >> 20;
  //   funct7 = (word & rtype_funct7_mask)  >> 25;    
  // };
}

InstructionTypeR parse_itype(word_t word) {
  // return InstrTypeI(word_t word): Instruction(word) {
  //   rd =     (word & itype_rd_mask)      >> 7;
  //   funct3 = (word & itype_funct3_mask)  >> 12;
  //   rs1 =    (word & itype_rs1_mask)     >> 15;
  //   imm =    (word & itype_imm_mask)     >> 20;    
  // };
}

void print_rtype() {
  // std::cout
  //   << "funct7: " << std::bitset<7>(funct7) << " "
  //   << "rs2: "    << std::bitset<5>(rs2) << " "
  //   << "rs1: "    << std::bitset<5>(rs1) << " "
  //   << "funct3: " << std::bitset<3>(funct3) << " "
  //   << "rd: "     << std::bitset<5>(rd) << " "
  //   << "opcode: " << std::bitset<7>(opcode) << " "
  //   << std::endl;
}

void print_itype() {
}

void print_stype() {
} 

void print_btype() {
}

void print_utype() {
}

void print_jtype() {
}

// uops 
#define lui     0x01
#define auipc   0x02
#define jal     0x03
#define jalr    0x04
#define beq     0x05
#define bne     0x06
#define blt     0x07
#define bge     0x08
#define bltu    0x09
#define bgeu    0x0a
#define lb      0x0b
#define lh      0x0c
#define lw      0x0d
#define lbu     0x0e
#define lhu     0x0f
#define sb      0x10
#define sh      0x11
#define sw      0x12
#define addi    0x13
#define slti    0x14
#define sltiu   0x15
#define xori    0x16
#define ori     0x17
#define andi    0x18
#define slli    0x19
#define srli    0x1a
#define srai    0x1b
#define add     0x1c
#define sub     0x1d
#define sll     0x1e
#define slt     0x1f
#define sltu    0x20
#define xor     0x21
#define srl     0x22
#define sra     0x23
#define or      0x24
#define and     0x25
#define fence   0x26
#define ecall   0x27
#define ebreak  0x28

// uint32_t add = [](uint32_t lhs, uint32_t rhs) {
//   // x[i.rd] = x[i.rs1] + x[i.rs2];
// }