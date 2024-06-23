#pragma once

#include <map>
#include <bitset>
#include <iostream>

#include "common.hpp"
#include "core.hpp"
#include "memory.hpp"
#include "instruction.hpp"

// #include "mmu.hpp"

class Cpu {
public:
  Cpu(uint32_t l3_size, uint32_t l2_size, uint32_t l1_size) : core: l3(l3_size) {};
  ~Cpu() = default;

  Core core;
  Memory l3; // L3 cache

  // word_t fetch(Memory& mem, word_t addr);
  void run(uint32_t ticks);
};

void Cpu::execute(Instruction& i) {
  switch (i.opcode) {
    case ADDI:
      // std::cout << "execute ADDI" << std::endl;
      // sign extend?
      x[i.rd] = x[i.rs1] + static_cast<word_t>(i.imm);
      break;
    case 0x33: // ADD, SUB, XOR, OR, AND
      switch (i.funct7) {
        case 0b0000000: // ADD
          // std::cout << "execute ADD" << std::endl;
          x[i.rd] = x[i.rs1] + x[i.rs2];
          break;
        case 0b0100000: // SUB
          // std::cout << "execute SUB" << std::endl;
          x[i.rd] = x[i.rs1] - x[i.rs2];
          break;
        default:
          // std::cout << "illegal instruction" << " ";
          break;
      }
      break;
    default:
      // std::cout << "illegal instruction" << " ";
      break;
  }
}

void Cpu::run(uint32_t ticks) {
  word_t fetched_word = fetch(mem, pc);
  word_t word2decode;
  if ((fetched_word & 0x3) == 0x3) {
    std::cout << "32-bit" << " ";
    pc += 4; // 32-bit length non-compressed instruction
    word2decode = fetched_word;
  } else {
    std::cout << "16-bit" << " ";
    pc += 2; // 16-bit length compressed instruction
    word2decode = decompress(fetched_word & 0xffff);
  }
  Instruction instr = decode(word2decode);


  // print_instruction<instr.type>();
  // instr.print();
  execute(instr);
  // pc++;
}