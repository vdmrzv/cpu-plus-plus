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
#define LUI   0x37 // 0b0110111 (I-type)
#define ADDI  0x13 // 0b0010011 (I-type)
#define ADD   0x33 // 0b0110011 (R-type)
#define SUB   0x33 // 0b0110011 (R-type)

#define opcode_mask       0x7f        // 0b1111111       << 0

#define itype_rd_mask     0xf80       // 0b11111         << 7
#define itype_funct3_mask 0x7000      // 0b111           << 12
#define itype_rs1_mask    0xf8000     // 0b11111         << 15
#define itype_imm_mask    0xfff00000  // 0b111111111111  << 20

#define rtype_rd_mask     0b11111         << 7
#define rtype_funct3_mask 0b111           << 12
#define rtype_rs1_mask    0b11111         << 15
#define rtype_rs2_mask    0b11111         << 20
#define rtype_funct7_mask 0b1111111       << 25


using byte_t = uint8_t;
using hword_t = uint16_t;
using word_t = uint32_t;
using dword_t = uint64_t;

// I-type instruction
typedef struct {
  uint8_t opcode;  // : 7 bits
  uint8_t rd;      // : 5 bits
  uint8_t funct3;  // : 3 bits
  uint8_t rs1;     // : 5 bits
  uint16_t imm;    // : 12 bits
} instr_t;

enum InstructionType {
  R, I, S, B, U, J  
};

struct Instruction {
  // std::string name;
  InstructionType type;
  uint8_t opcode;
  uint8_t rd;
  uint8_t funct3;
  uint8_t rs1;
  uint8_t rs2;
  uint8_t funct7;
  uint16_t imm;

  void print();
  // std::function<void(Cpu&, word_t)> exec;
};

struct TypeR {
  uint8_t rd;      // : 5 bits
  uint8_t funct3;  // : 3 bits
  uint8_t rs1;     // : 5 bits
  uint8_t rs2;     // : 5 bits
  uint16_t funct7; // : 7 bits
};

struct TypeI {
  uint8_t rd;      // : 5 bits
  uint8_t funct3;  // : 3 bits
  uint8_t rs1;     // : 5 bits
  uint16_t imm;    // : 12 bits
};


std::map<int, InstructionType> SUPPORTED_INSTRUCTIONS = {
  { ADDI, InstructionType::I },
  { ADD,  InstructionType::R },
  { SUB,  InstructionType::R }
};

void Instruction::print() {
  std::cout << std::setw(8) << "opcode: " << std::bitset<7>(opcode) << std::endl;
  std::cout << std::setw(8) << "rd: "     << std::bitset<5>(rd)     << std::endl;
  std::cout << std::setw(8) << "funct3: " << std::bitset<3>(funct3) << std::endl;
  std::cout << std::setw(8) << "rs1: "    << std::bitset<5>(rs1)    << std::endl;
  std::cout << std::setw(8) << "rs2: "    << std::bitset<5>(rs2)    << std::endl;
  std::cout << std::setw(8) << "imm: "    << std::bitset<12>(imm)   << std::endl;
  std::cout << std::setw(8) << "funct7: " << std::bitset<7>(funct7) << std::endl;
}

void parse_rtype(Instruction& instr, word_t w) {
  instr.rd =     (w & rtype_rd_mask)      >> 7;
  instr.funct3 = (w & rtype_funct3_mask)  >> 12;
  instr.rs1 =    (w & rtype_rs1_mask)     >> 15;
  instr.rs2 =    (w & rtype_rs2_mask)     >> 20;
  instr.funct7 = (w & rtype_funct7_mask)  >> 25;
}

void parse_itype(Instruction& instr, word_t w) {
  instr.rd =     (w & itype_rd_mask)      >> 7;
  instr.funct3 = (w & itype_funct3_mask)  >> 12;
  instr.rs1 =    (w & itype_rs1_mask)     >> 15;
  instr.imm =    (w & itype_imm_mask)     >> 20;
}

// void parse_stype(instr_t& ins,  word_t data) {
// }

// void parse_btype(instr_t& ins,  word_t data) {
// }

// void parse_utype(instr_t& ins,  word_t data) {
// }

// void parse_jtype(instr_t& ins,  word_t data) {
// }

