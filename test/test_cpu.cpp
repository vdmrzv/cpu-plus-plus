#include <iostream>
#include <iomanip>
#include <cstdint>

#include "../cpu.hpp"
#include "../memory.hpp"

int main()
{
  uint32_t ram_size = 1024 * 1024 * 16; // 16 MB
  uint32_t l3 = 8 * 1024 * 1024; // 8 MB
  uint32_t l2 = 512 * 1024; // 512 kB
  uint32_t l1 = 32 * 1024; // 32 kB

  Memory ram(ram_size);
  Cpu cpu(l3, l2, l1);

  // ram.init();
  // ram.write_word(0x00000000, 0x00300793);
  // ram.write_word(0x00000004, 0x00200813);
  // ram.write_word(0x00000008, 0x01078533);
  // ram.write_word(0x0000000c, 0x410785b3);

  // 0x00200793   li    a5,2
  // 0x00300813   li    a6,3
  // 0x01078533   add   a0,a5,a6
  // 0x41078533   sub   a1,a5,a6

  // li is a pseudo instruction so in reality it is compiled to

  // 0x00200793   addi  a5,zero,3    000000000011 00000 000 01111 0010011
  // 0x00300813   addi  a6,zero,2    000000000010 00000 000 10000 0010011
  // 0x01078533   add   a0,a5,a6    0000000 10000 01111 000 01010 0110011
  // 0x41078533   sub   a1,a5,a6    0100000 10000 01111 000 01011 0110011

  // 0b1011110111000001111 0111011

  // cpu.pc = 0x00000000;
  // uint32_t cycles = 4;
  // while (cycles > 0) {
  //   cpu.tick(ram);
  //   cycles--;
  // }

  // std::cout << cpu.x[a0] << std::endl;
  // std::cout << cpu.x[a1] << std::endl;

  return 0;
}
