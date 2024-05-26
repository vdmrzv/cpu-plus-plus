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
  word_t fetch(Memory& mem, word_t addr);
  Instruction decode(word_t data);
  void execute(Instruction& ins);
  void tick(Memory& mem);
};

Cpu::Cpu() {
  x.assign(32, 0);
  std::fill(x.begin(), x.end(), 0);
}

Cpu::~Cpu() {
}


word_t Cpu::fetch(Memory& mem, word_t addr) {
  return mem.read_word(addr);
}

Instruction Cpu::decode(word_t w) {

  std::cout << std::hex << w << std::endl;
  Instruction instr;
  instr.name = SUPPORTED_INSTRUCTIONS[instr.opcode].name;
  instr.opcode = w & opcode_mask;
  instr.rd = 0;
  instr.funct3 = 0;
  instr.rs1 = 0;
  instr.rs2 = 0;
  instr.funct7 = 0;
  instr.imm = 0;

  switch (SUPPORTED_INSTRUCTIONS[instr.opcode].type) {
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

void Cpu::execute(Instruction& ins) {
  // std::cout << "hello: " << std::hex << static_cast<int>(ins.opcode) << std::endl;
  switch (ins.opcode) {
    case ADDI:
      std::cout << "execute ADDI" << std::endl;
      x[ins.rd] = x[ins.rs1] + ins.imm;
      break;
    case ADD:
      x[ins.rd] = x[ins.rs1] + x[ins.rs2];
      break;
    default:
      std::cout << "illegal instruction" << std::endl;
  }
}

void Cpu::tick(Memory& mem) {
    word_t data = fetch(mem, x[pc]);
    Instruction instr = decode(data);
    print_instr(instr);
    execute(instr);
    pc++;
}