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

// InstructionTypeR parse_rtype(word_t word) {
  // return TypeR {
  //   opcode = (word & opcode_mask);
  //   rd =     (word & rtype_rd_mask)      >> 7;
  //   funct3 = (word & rtype_funct3_mask)  >> 12;
  //   rs1 =    (word & rtype_rs1_mask)     >> 15;
  //   rs2 =    (word & rtype_rs2_mask)     >> 20;
  //   funct7 = (word & rtype_funct7_mask)  >> 25;    
  // };
// }

// InstructionTypeR parse_itype(word_t word) {
  // return InstrTypeI(word_t word): Instruction(word) {
  //   rd =     (word & itype_rd_mask)      >> 7;
  //   funct3 = (word & itype_funct3_mask)  >> 12;
  //   rs1 =    (word & itype_rs1_mask)     >> 15;
  //   imm =    (word & itype_imm_mask)     >> 20;    
  // };
// }

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

enum uop {
  // RV32I
  lui,
  auipc,
  jal, jalr,
  beq, bne, blt, bge, bltu, bgeu,
  lb, lh, lw, lbu, lhu,
  sb, sh, sw,
  addi, slti, sltiu, xori, ori, andi, slli, srli, srai,
  add, sub, sll, slt, sltu, xor_uop, srl, sra, or_uop, and_uop,
  fence,
  ecall, ebreak,
  // RV64I
  lwu, ld,
  sd,
  // slli, srli, srai,
  addiw, slliw, srliw, sraiw,
  addw, subw, sllw, srlw, sraw
};

// uint32_t add = [](uint32_t lhs, uint32_t rhs) {
//   // x[i.rd] = x[i.rs1] + x[i.rs2];
// }