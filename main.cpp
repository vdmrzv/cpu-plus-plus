#include <iostream>
#include <iomanip>
#include <cstdint>

#include "cpu.hpp"
// #include "mmu.hpp"
#include "memory.hpp"

int main()
{
  Memory ram(1024 * 1024 * 16);
  Cpu cpu;
  // Mmu mmu;
  // ram.print_size();
  ram.init();
  ram.write_word(0x00000000, 0x00200793);
  // ram.write_word(0x00000001, 0x00300813);
  // ram.write_word(0x00000002, 0x01078533);

  // 00200793   li    a5,2
  // 00300813   li    a6,3
  // 01078533   add   a0,a5,a6

  // li is a pseudo instruction so in reality it is compiled to

  // 00200793   addi  a5,zero,2   000000000010 00000 000 01111 0010011
  // 00300813   addi  a6,zero,3   000000000011 00000 000 10000 0010011
  // 01078533   add   a0,a5,a6    000000010000 01111 000 01010 0110011

  // std::cout << std::hex << ram.read_word(0x00000000) << std::endl;

  cpu.pc = 0x00000000;
  uint32_t cycles = 1;
  while (cycles > 0) {
    cpu.tick(ram);
    cycles--;
  }
  return 0;
}
