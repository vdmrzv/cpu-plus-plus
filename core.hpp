#pragma once

#include <vector>

#include "common.hpp"
#include "memory.hpp"
#include "decoder.hpp"

class Core {
private:
  word_t pc;

  std::vector<word_t> x;    // x registers
  std::vector<word_t> f;    // f registers
  std::vector<word_t> csr;  // csr registers

  Memory l2_cache;  // L2 cache
  Memory l1i_cache; // L1 insruction cache
  Memory l1d_cache; // L1 data cache

  Decoder decoder;
public:
  Core(uint32_t l2_size, uint32_t l1_size)
    : l2_cache(l2_size), l1i_cache(l1_size), l1d_cache(l1_size) {
    x.assign(32, 0);
    f.assign(32, 0.0);
    csr.assign(4096, 0);
  };
  void run();
  void reset();
};

void Core::run() {
  hword_t first_hword = l1i_cache.read_hword(pc);
  while(first_hword != 0) {
    word_t full_word;
    pc += 2;
    
    if ((first_hword & 0x3) == 0x3) {
      // 32-bit length non-compressed instruction
      hword_t second_hword = l1i_cache.read_hword(pc);
      pc += 2;
      full_word = (second_hword << 16) + first_hword;
      // std::cout << "32-bit" << " ";
    } else {
      // 16-bit compressed instruction 
      full_word = decoder.decompress(first_hword);
      // std::cout << "16-bit" << " ";
    }
    decoder.decode(full_word);
  }
  // Instruction instr = decoder.decode(data);
}

void Core::reset() {
  pc = 0x00000000;
}
