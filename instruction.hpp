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

// RV32I
#define uop_lui     0x01
#define uop_auipc   0x02
#define uop_jal     0x03
#define uop_jalr    0x04
#define uop_beq     0x05
#define uop_bne     0x06
#define uop_blt     0x07
#define uop_bge     0x08
#define uop_bltu    0x09
#define uop_bgeu    0x0a
#define uop_lb      0x0b
#define uop_lh      0x0c
#define uop_lw      0x0d
#define uop_lbu     0x0e
#define uop_lhu     0x0f
#define uop_sb      0x10
#define uop_sh      0x11
#define uop_sw      0x12
#define uop_addi    0x13
#define uop_slti    0x14
#define uop_sltiu   0x15
#define uop_xori    0x16
#define uop_ori     0x17
#define uop_andi    0x18
#define uop_slli    0x19
#define uop_srli    0x1a
#define uop_srai    0x1b
#define uop_add     0x1c
#define uop_sub     0x1d
#define uop_sll     0x1e
#define uop_slt     0x1f
#define uop_sltu    0x20
#define uop_xor     0x21
#define uop_srl     0x22
#define uop_sra     0x23
#define uop_or      0x24
#define uop_and     0x25
#define uop_fence   0x26
#define uop_ecall   0x27
#define uop_ebreak  0x28

// RV64I
#define uop_lwu     0x29 
#define uop_ld      0x30 
#define uop_sd      0x3a
// #define uop_slli    0x3b
// #define uop_srli    0x3c
// #define uop_srai    0x3d
#define uop_addiw   0x3e
#define uop_slliw   0x3f
#define uop_srliw   0x40
#define uop_sraiw   0x40
#define uop_addw    0x41
#define uop_subw    0x42
#define uop_sllw    0x43
#define uop_srlw    0x44
#define uop_sraw    0x45

// uint32_t add = [](uint32_t lhs, uint32_t rhs) {
//   // x[i.rd] = x[i.rs1] + x[i.rs2];
// }