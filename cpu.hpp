#pragma once

#include <map>
#include <bitset>
#include <iostream>

#include "global.hpp"
#include "memory.hpp"
// #include "mmu.hpp"

class Cpu {
public:
  Cpu();
  ~Cpu();

  word_t pc;

  std::vector<word_t> x; // x registers
  std::vector<word_t> f; // f registers

  word_t fetch(Memory& mem, word_t addr);
  Instruction decode(word_t data);
  void execute(Instruction& ins);
  void tick(Memory& mem);
};

Cpu::Cpu() {
  x.assign(32, 0);
  f.assign(32, 0.0);
  std::fill(x.begin(), x.end(), 0);
  std::fill(f.begin(), f.end(), 0.0);
}

Cpu::~Cpu() {
}


word_t Cpu::fetch(Memory& mem, word_t addr) {
  return mem.read_word(addr);
}

Instruction Cpu::decode(word_t w) {
  Instruction instr = {};
  // instr.name = SUPPORTED_INSTRUCTIONS[instr.opcode].name;
  instr.opcode = w & opcode_mask;

  switch (SUPPORTED_INSTRUCTIONS[instr.opcode]) {
    case InstructionType::R:
      std::cout << "R" << std::endl;
      parse_rtype(instr, w);
      break;
    case InstructionType::I:
      std::cout << "I" << std::endl;
      parse_itype(instr, w);
      break;
    default:
      std::cout << "decode error" << std::endl;
      break;
  }
  return instr;
}

void Cpu::execute(Instruction& i) {
  switch (i.opcode) {
    case ADDI:
      std::cout << "execute ADDI" << std::endl;
      x[i.rd] = x[i.rs1] + i.imm;
      break;
    case 0x33: // ADD, SUB, XOR, OR, AND
      switch (i.funct7) {
        case 0b0000000: // ADD
          std::cout << "execute ADD" << std::endl;
          x[i.rd] = x[i.rs1] + x[i.rs2];
          break;
        case 0b0100000: // SUB
          std::cout << "execute SUB" << std::endl;
          x[i.rd] = x[i.rs1] - x[i.rs2];
          break;
        default:
          std::cout << "illegal instruction" << std::endl;
      }
      break;
    default:
      std::cout << "illegal instruction" << std::endl;
  }
}

void Cpu::tick(Memory& mem) {
  // std::cout << pc << std::endl;
  word_t data = fetch(mem, pc);
  // std::cout << data << std::endl;
  Instruction instr = decode(data);
  instr.print();
  execute(instr);
  pc++;
}