#pragma once

#include <map>
#include <bitset>
#include <iostream>

#include "common.hpp"
#include "core.hpp"
#include "memory.hpp"
#include "instruction.hpp"

class Cpu {
public:
  ~Cpu() = default;

  Core core;
  Memory l3_cache; // L3 cache

  Cpu(uint32_t l3_size, uint32_t l2_size, uint32_t l1_size)
    : core(l2_size, l1_size), l3_cache(l3_size) {};
  void run();
  void reset();
};

// void Cpu::execute(Instruction& i) {
//   switch (i.opcode) {
//     case ADDI:
//       // std::cout << "execute ADDI" << std::endl;
//       // sign extend?
//       x[i.rd] = x[i.rs1] + static_cast<word_t>(i.imm);
//       break;
//     case 0x33: // ADD, SUB, XOR, OR, AND
//       switch (i.funct7) {
//         case 0b0000000: // ADD
//           // std::cout << "execute ADD" << std::endl;
//           x[i.rd] = x[i.rs1] + x[i.rs2];
//           break;
//         case 0b0100000: // SUB
//           // std::cout << "execute SUB" << std::endl;
//           x[i.rd] = x[i.rs1] - x[i.rs2];
//           break;
//         default:
//           // std::cout << "illegal instruction" << " ";
//           break;
//       }
//       break;
//     default:
//       // std::cout << "illegal instruction" << " ";
//       break;
//   }
// }

void Cpu::run() {
  core.run();
}

void Cpu::reset() {
  core.reset();
  l3_cache.init();
}