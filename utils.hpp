#pragma once

#include <vector>

#include "common.h"

void write_program(Memory mem, word_t address, std::vector<uint64_t> prog) {
  word_t cur_address = address;
  for (auto inst: prog) {
    if ((inst >> 16) == 0) {
      mem.store_hword(cur_address, inst)
      cur_address += 2;
    } else if ((inst >> 32) == 0) {
      mem.store_word(cur_address, inst)
      cur_address += 4;
    } else {
      std::cout << "should not happen" << std::endl;
    }
  }
}