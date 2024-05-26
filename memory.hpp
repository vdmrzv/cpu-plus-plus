#pragma once

#include <cstdint>
#include <vector>
#include <iostream>

#include "global.hpp"

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

  byte_t read_byte(word_t address) const;
  word_t read_word(word_t address) const;
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
    storage[i] = 0b00000000;
  }
}

void Memory::write_byte(word_t address, byte_t data) {
  if (address > size) {
    throw std::length_error("store to address > size");
  }
  storage[address] = data;
}

void Memory::write_word(word_t address, word_t data) {
  if (address > size) {
    throw std::length_error("store to address > size");
  }
  reinterpret_cast<word_t*>(storage)[address] = data;
}

byte_t Memory::read_byte(word_t address) const {
  if (address > size) {
    throw std::length_error("fetch from address > size");
  }
  return storage[address];
}

word_t Memory::read_word(word_t address) const {
  if (address > size) {
    throw std::length_error("fetch from address > size");
  }
  return reinterpret_cast<word_t*>(storage)[address];
}


