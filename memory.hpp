#pragma once

#include <cstdint>
#include <vector>
#include <iostream>

#include "common.hpp"

class Memory {
private:
  uint32_t size; // in bytes
  byte_t* storage;
public:
  Memory(uint32_t sz);
  ~Memory();
  void init();
  void print_size();

  void write_byte(word_t address, byte_t data);
  void write_word(word_t address, word_t data);
  void write_hword(word_t address, hword_t data);

  byte_t read_byte(word_t address) const;
  word_t read_word(word_t address) const;
  hword_t read_hword(word_t address) const;

  void write_program(word_t address, std::vector<uint64_t> prog);

  int is_valid_address(word_t address) const;
};

Memory::Memory(uint32_t sz) {
  size = sz;
  storage = new byte_t[sz];
}

Memory::~Memory() {
  delete[] storage;
}

void Memory::print_size() {
  std::cout << size / 1024 / 1024 << "MB" << std::endl;
}

void Memory::init() {
  for (uint32_t i = 0; i < size; ++i) {
    storage[i] = 0x0;
  }
}

int Memory::is_valid_address(word_t address) const {
  if (address > size) {
    return 0;
  } else if (address < 0) {
    return 0;
  }
  return 1;
}

void Memory::write_byte(word_t address, byte_t data) {
  storage[address] = data;
}

void Memory::write_word(word_t address, word_t data) {
  reinterpret_cast<word_t*>(storage)[address] = data;
}

void Memory::write_hword(word_t address, hword_t data) {
  reinterpret_cast<hword_t*>(storage)[address] = data;
}

byte_t Memory::read_byte(word_t address) const {
  // if (is_valid_address(address))
  return storage[address];
}

word_t Memory::read_word(word_t address) const {
  // if (is_valid_address(address))
  return reinterpret_cast<word_t*>(storage)[address];
}

hword_t Memory::read_hword(word_t address) const {
  // if (is_valid_address(address))
  return reinterpret_cast<hword_t*>(storage)[address];
}





