#include "../cpu.hpp"
#include "../memory.hpp"

/*
   10430:       1101                    addi    sp,sp,-32
   10432:       ec22                    sd      s0,24(sp)
   10434:       1000                    addi    s0,sp,32
   10436:       478d                    li      a5,3
   10438:       fef42023                sw      a5,-32(s0)
   1043c:       4789                    li      a5,2
   1043e:       fef42223                sw      a5,-28(s0)
   10442:       fe042703                lw      a4,-32(s0)
   10446:       fe442783                lw      a5,-28(s0)
   1044a:       9fb9                    addw    a5,a5,a4
   1044c:       fef42423                sw      a5,-24(s0)
   10450:       fe042703                lw      a4,-32(s0)
   10454:       fe442783                lw      a5,-28(s0)
   10458:       40f707bb                subw    a5,a4,a5
   1045c:       fef42623                sw      a5,-20(s0)
   10460:       fec42783                lw      a5,-20(s0)
   10464:       853e                    mv      a0,a5
   10466:       6462                    ld      s0,24(sp)
   10468:       6105                    addi    sp,sp,32
   1046a:       8082                    ret
*/


int main() {
  Memory ram(1024 * 1024 * 16);
  Cpu cpu();
  std::vector<uint64_t> program = {
   0x1101,
   0xec22,
   0x1000,
   0x478d,
   0xfef42023,
   0x4789,
   0xfef42223,
   0xfe042703,
   0xfe442783,
   0x9fb9,
   0xfef42423,
   0xfe042703,
   0xfe442783,
   0x40f707bb,
   0xfef42623,
   0xfec42783,
   0x853e,
   0x6462,
   0x6105,
   0x8082,
  };

  ram.init();
  ram.write_program(0x00000000, program);

  cpu.pc = 0x00000000;
  uint32_t cycles = program.size();
  while (cycles > 0) {
    cpu.tick(ram);
    cycles--;
  }

  return 0;
}