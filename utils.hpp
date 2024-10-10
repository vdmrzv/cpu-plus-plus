#pragma once

#include <vector>

#include "common.hpp"
#include "memory.hpp"

std::string hex_to_bin(const std::string& hex_str) {
  std::string bin_str;
  bin_str.reserve(hex_str.length() * 4); // Allocate space for the binary data

  for (char c : hex_str) {
    int value = std::stoi(std::string(1, c), nullptr, 16);
    std::string bin_digit;
    for (int i = 0; i < 4; i++) {
      bin_digit = std::to_string(value & 1) + bin_digit;
      value >>= 1;
    }
    bin_str += bin_digit;
  }

  return bin_str;
}

void write_program(Memory mem, word_t address, std::vector<uint64_t> prog) {
  word_t cur_address = address;
  for (auto inst: prog) {
    if ((inst >> 16) == 0) {
      mem.write_hword(cur_address, inst);
      cur_address += 2;
    } else if ((inst >> 32) == 0) {
      mem.write_word(cur_address, inst);
      cur_address += 4;
    } else {
      std::cout << "write_program is broken" << std::endl;
    }
  }
}