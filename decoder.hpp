#pragma once

#include "common.hpp"
#include "instruction.hpp"

class Decoder {
public:
  uop decode(word_t word);
  word_t decompress(hword_t hword);
};

uop Decoder::decode(word_t word) {
  // Instruction instr = {};
  // instr.opcode = word & opcode_mask;

  // switch (instr.opcode) {
  //   case InstructionType::R:
  //     std::cout << "R" << " ";
  //     parse_rtype(instr, word);
  //     break;
  //   case InstructionType::I:
  //     std::cout << "I" << " ";
  //     parse_itype(instr, word);
  //     break;
  //   case InstructionType::S:
  //     std::cout << "S" << " ";
  //     parse_stype(instr, word);
  //     break;
  //   case InstructionType::B:
  //     std::cout << "B" << " ";
  //     parse_btype(instr, word);
  //     break;
  //   case InstructionType::U:
  //     std::cout << "U" << " ";
  //     return parse_utype(instr, word);
  //     break;
  //   case InstructionType::J:
  //     std::cout << "J" << " ";
  //     return parse_jtype(instr, word);


  //   default:
  //     std::cout << "Error: unknown instruction type." << std::endl;
  //     break;
  // }
}

word_t Decoder::decompress(hword_t halfword) {
  auto opcode = halfword & 0x3; // [1:0]
  auto funct3 = (halfword >> 13) & 0x7; // [15:13]

  // @TODO not an INT
  uint32_t funct2;
  uint32_t rd, rs1, rs2, offset;
  uint32_t imm, imm1, imm2, imm11_5, imm4_0, funct1;
  uint32_t r, shamt, nzuimm, nzimm, funct2_2; // what the fuck is this?

  switch(opcode) {
    case 0:
      switch (funct3) {
        case 0:
          // C.ADDI4SPN
          // addi rd+8, x2, nzuimm
          rd = (halfword >> 2) & 0x7; // [4:2]
          nzuimm =
            ((halfword >> 7) & 0x30) | // nzuimm[5:4] <= [12:11]
            ((halfword >> 1) & 0x3c0) | // nzuimm{9:6] <= [10:7]
            ((halfword >> 4) & 0x4) | // nzuimm[2] <= [6]
            ((halfword >> 2) & 0x8); // nzuimm[3] <= [5]
          // nzuimm == 0 is reserved instruction
          if (nzuimm != 0) {
            return (nzuimm << 20) | (2 << 15) | ((rd + 8) << 7) | 0x13;
          }
        case 1:
          // @TODO: Support C.LQ for 128-bit
          // C.FLD for 32, 64-bit
          // fld rd+8, offset(rs1+8)
          rd = (halfword >> 2) & 0x7; // [4:2]
          rs1 = (halfword >> 7) & 0x7; // [9:7]
          offset =
            ((halfword >> 7) & 0x38) | // offset[5:3] <= [12:10]
            ((halfword << 1) & 0xc0); // offset[7:6] <= [6:5]
          return (offset << 20) | ((rs1 + 8) << 15) | (3 << 12) | ((rd + 8) << 7) | 0x7;
        case 2:
          // C.LW
          // lw rd+8, offset(rs1+8)
          rs1 = (halfword >> 7) & 0x7; // [9:7]
          rd = (halfword >> 2) & 0x7; // [4:2]
          offset =
            ((halfword >> 7) & 0x38) | // offset[5:3] <= [12:10]
            ((halfword >> 4) & 0x4) | // offset[2] <= [6]
            ((halfword << 1) & 0x40); // offset[6] <= [5]
          return (offset << 20) | ((rs1 + 8) << 15) | (2 << 12) | ((rd + 8) << 7) | 0x3;
        case 3:
          // @TODO: Support C.FLW in 32-bit mode
          // C.LD in 64-bit mode
          // ld rd+8, offset(rs1+8)
          rs1 = (halfword >> 7) & 0x7; // [9:7]
          rd = (halfword >> 2) & 0x7; // [4:2]
          offset =
            ((halfword >> 7) & 0x38) | // offset[5:3] <= [12:10]
            ((halfword << 1) & 0xc0); // offset[7:6] <= [6:5]
          return (offset << 20) | ((rs1 + 8) << 15) | (3 << 12) | ((rd + 8) << 7) | 0x3;
        case 4:
          // Reserved
        case 5:
          // C.FSD
          // fsd rs2+8, offset(rs1+8)
          rs1 = (halfword >> 7) & 0x7; // [9:7]
          rs2 = (halfword >> 2) & 0x7; // [4:2]
          offset = 
            ((halfword >> 7) & 0x38) | // uimm[5:3] <= [12:10]
            ((halfword << 1) & 0xc0); // uimm[7:6] <= [6:5]
          imm11_5 = (offset >> 5) & 0x7f;
          imm4_0 = offset & 0x1f;
          return (imm11_5 << 25) | ((rs2 + 8) << 20) | ((rs1 + 8) << 15) | (3 << 12) | (imm4_0 << 7) | 0x27;
        case 6:
          // C.SW
          // sw rs2+8, offset(rs1+8)
          rs1 = (halfword >> 7) & 0x7; // [9:7]
          rs2 = (halfword >> 2) & 0x7; // [4:2]
          offset = 
            ((halfword >> 7) & 0x38) | // offset[5:3] <= [12:10]
            ((halfword << 1) & 0x40) | // offset[6] <= [5]
            ((halfword >> 4) & 0x4); // offset[2] <= [6]
          imm11_5 = (offset >> 5) & 0x7f;
          imm4_0 = offset & 0x1f;
          return (imm11_5 << 25) | ((rs2 + 8) << 20) | ((rs1 + 8) << 15) | (2 << 12) | (imm4_0 << 7) | 0x23;
        case 7:
          // @TODO: Support C.FSW in 32-bit mode
          // C.SD
          // sd rs2+8, offset(rs1+8)
          rs1 = (halfword >> 7) & 0x7; // [9:7]
          rs2 = (halfword >> 2) & 0x7; // [4:2]
          offset = 
            ((halfword >> 7) & 0x38) | // uimm[5:3] <= [12:10]
            ((halfword << 1) & 0xc0); // uimm[7:6] <= [6:5]
          imm11_5 = (offset >> 5) & 0x7f;
          imm4_0 = offset & 0x1f;
          return (imm11_5 << 25) | ((rs2 + 8) << 20) | ((rs1 + 8) << 15) | (3 << 12) | (imm4_0 << 7) | 0x23;
        default:
          break;
          // ha?
      }
    case 1:
      switch (funct3) {
        case 0:
          r = (halfword >> 7) & 0x1f; // [11:7]
          imm = ((halfword & 0x1000) == 0x1000 ? 0xffffffc0 : 0) | // imm[31:6] <= [12]
          ((halfword >> 7) & 0x20) | // imm[5] <= [12]
          ((halfword >> 2) & 0x1f); // imm[4:0] <= [6:2]
          if (r == 0 && imm == 0) {
            // C.NOP
            // addi x0, x0, 0
            return 0x13;
          } else if (r != 0) {
            // C.ADDI
            // addi r, r, imm
            return (imm << 20) | (r << 15) | (r << 7) | 0x13;
          }
          // @TODO: Support HINTs
          // r == 0 and imm != 0 is HINTs
        case 1:
          // @TODO: Support C.JAL in 32-bit mode
          // C.ADDIW
          // addiw r, r, imm
          r = (halfword >> 7) & 0x1f;
          imm = ((halfword & 0x1000) == 0x1000 ? 0xffffffc0 : 0) | // imm[31:6] <= [12]
          ((halfword >> 7) & 0x20) | // imm[5] <= [12]
          ((halfword >> 2) & 0x1f); // imm[4:0] <= [6:2]
          if (r != 0) {
            return (imm << 20) | (r << 15) | (r << 7) | 0x1b;
          }
          // r == 0 is reserved instruction
        case 2:
          // C.LI
          // addi rd, x0, imm
          r = (halfword >> 7) & 0x1f;
          imm = ((halfword & 0x1000) == 0x1000 ? 0xffffffc0 : 0) | // imm[31:6] <= [12]
          ((halfword >> 7) & 0x20) | // imm[5] <= [12]
          ((halfword >> 2) & 0x1f); // imm[4:0] <= [6:2]
          if (r != 0) {
            return (imm << 20) | (r << 7) | 0x13;
          }
          // @TODO: Support HINTs
          // r == 0 is for HINTs
        case 3:
          r = (halfword >> 7) & 0x1f; // [11:7]
          if (r == 2) {
            // C.ADDI16SP
            // addi r, r, nzimm
            imm = ((halfword & 0x1000) == 0x1000 ? 0xfffffc00 : 0) | // imm[31:10] <= [12]
            ((halfword >> 3) & 0x200) | // imm[9] <= [12]
            ((halfword >> 2) & 0x10) | // imm[4] <= [6]
            ((halfword << 1) & 0x40) | // imm[6] <= [5]
            ((halfword << 4) & 0x180) | // imm[8:7] <= [4:3]
            ((halfword << 3) & 0x20); // imm[5] <= [2]
            if (imm != 0) {
              return (imm << 20) | (r << 15) | (r << 7) | 0x13;
            }
            // imm == 0 is for reserved instruction
          }
          if (r != 0 && r != 2) {
            // C.LUI
            // lui r, nzimm
            nzimm = ((halfword & 0x1000) == 0x1000 ? 0xfffc0000 : 0) | // nzimm[31:18] <= [12]
            ((halfword << 5) & 0x20000) | // nzimm[17] <= [12]
            ((halfword << 10) & 0x1f000); // nzimm[16:12] <= [6:2]
            if (nzimm != 0) {
              return nzimm | (r << 7) | 0x37;
            }
            // nzimm == 0 is for reserved instruction
          }
        case 4:
          funct2 = (halfword >> 10) & 0x3; // [11:10]
          switch (funct2) {
            case 0:
              // C.SRLI
              // c.srli rs1+8, rs1+8, shamt
              shamt = 
                ((halfword >> 7) & 0x20) | // shamt[5] <= [12]
                ((halfword >> 2) & 0x1f); // shamt[4:0] <= [6:2]
              rs1 = (halfword >> 7) & 0x7; // [9:7]
              return (shamt << 20) | ((rs1 + 8) << 15) | (5 << 12) | ((rs1 + 8) << 7) | 0x13;
            case 1:
              // C.SRAI
              // srai rs1+8, rs1+8, shamt
              shamt = 
                ((halfword >> 7) & 0x20) | // shamt[5] <= [12]
                ((halfword >> 2) & 0x1f); // shamt[4:0] <= [6:2]
              rs1 = (halfword >> 7) & 0x7; // [9:7]
              return (0x20 << 25) | (shamt << 20) | ((rs1 + 8) << 15) | (5 << 12) | ((rs1 + 8) << 7) | 0x13;
            case 2:
              // C.ANDI
              // andi, r+8, r+8, imm
              r = (halfword >> 7) & 0x7; // [9:7]
              imm = ((halfword & 0x1000) == 0x1000 ? 0xffffffc0 : 0) | // imm[31:6] <= [12]
              ((halfword >> 7) & 0x20) | // imm[5] <= [12]
              ((halfword >> 2) & 0x1f); // imm[4:0] <= [6:2]
              return (imm << 20) | ((r + 8) << 15) | (7 << 12) | ((r + 8) << 7) | 0x13;
            case 3:
              funct1 = (halfword >> 12) & 1; // [12]
              funct2_2 = (halfword >> 5) & 0x3; // [6:5] 
              rs1 = (halfword >> 7) & 0x7;
              rs2 = (halfword >> 2) & 0x7;
              switch (funct1) {
                case 0:
                  switch (funct2_2) {
                  case 0:
                    // C.SUB
                    // sub rs1+8, rs1+8, rs2+8
                    return (0x20 << 25) | ((rs2 + 8) << 20) | ((rs1 + 8) << 15) | ((rs1 + 8) << 7) | 0x33;
                  case 1:
                    // C.XOR
                    // xor rs1+8, rs1+8, rs2+8
                    return ((rs2 + 8) << 20) | ((rs1 + 8) << 15) | (4 << 12) | ((rs1 + 8) << 7) | 0x33;
                  case 2:
                    // C.OR
                    // or rs1+8, rs1+8, rs2+8
                    return ((rs2 + 8) << 20) | ((rs1 + 8) << 15) | (6 << 12) | ((rs1 + 8) << 7) | 0x33;
                  case 3:
                    // C.AND
                    // and rs1+8, rs1+8, rs2+8
                    return ((rs2 + 8) << 20) | ((rs1 + 8) << 15) | (7 << 12) | ((rs1 + 8) << 7) | 0x33;
                  default:
                    std::cout << "this should not happen" << std::endl;
                  }
                case 1:
                  switch (funct2_2) {
                  case 0:
                    // C.SUBW
                    // subw r1+8, r1+8, r2+8
                    return (0x20 << 25) | ((rs2 + 8) << 20) | ((rs1 + 8) << 15) | ((rs1 + 8) << 7) | 0x3b;
                  case 1:
                    // C.ADDW
                    // addw r1+8, r1+8, r2+8
                    return ((rs2 + 8) << 20) | ((rs1 + 8) << 15) | ((rs1 + 8) << 7) | 0x3b;
                  case 2:
                    // Reserved
                  case 3:
                    // Reserved
                  default:
                    std::cout << "this should not happen" << std::endl;
                  }
                default:
                  std::cout << "this should not happen" << std::endl;
              }
            default:
              std::cout << "this should not happen" << std::endl;
          }
        case 5:
          // C.J
          // jal x0, imm
          offset = ((halfword & 0x1000) == 0x1000 ? 0xfffff000 : 0) | // offset[31:12] <= [12]
            ((halfword >> 1) & 0x800) | // offset[11] <= [12]
            ((halfword >> 7) & 0x10) | // offset[4] <= [11]
            ((halfword >> 1) & 0x300) | // offset[9:8] <= [10:9]
            ((halfword << 2) & 0x400) | // offset[10] <= [8]
            ((halfword >> 1) & 0x40) | // offset[6] <= [7]
            ((halfword << 1) & 0x80) | // offset[7] <= [6]
            ((halfword >> 2) & 0xe) | // offset[3:1] <= [5:3]
            ((halfword << 3) & 0x20); // offset[5] <= [2]
          imm =
            ((offset >> 1) & 0x80000) | // imm[19] <= offset[20]
            ((offset << 8) & 0x7fe00) | // imm[18:9] <= offset[10:1]
            ((offset >> 3) & 0x100) | // imm[8] <= offset[11]
            ((offset >> 12) & 0xff); // imm[7:0] <= offset[19:12]
          return (imm << 12) | 0x6f;
        case 6:
          // C.BEQZ
          // beq r+8, x0, offset
          r = (halfword >> 7) & 0x7;
          offset = ((halfword & 0x1000) == 0x1000 ? 0xfffffe00 : 0) | // offset[31:9] <= [12]
            ((halfword >> 4) & 0x100) | // offset[8] <= [12]
            ((halfword >> 7) & 0x18) | // offset[4:3] <= [11:10]
            ((halfword << 1) & 0xc0) | // offset[7:6] <= [6:5]
            ((halfword >> 2) & 0x6) | // offset[2:1] <= [4:3]
            ((halfword << 3) & 0x20); // offset[5] <= [2]
          imm2 =
            ((offset >> 6) & 0x40) | // imm2[6] <= [12]
            ((offset >> 5) & 0x3f); // imm2[5:0] <= [10:5]
          imm1 =
            (offset & 0x1e) | // imm1[4:1] <= [4:1]
            ((offset >> 11) & 0x1); // imm1[0] <= [11]
          return (imm2 << 25) | ((r + 8) << 20) | (imm1 << 7) | 0x63;
        case 7:
          // C.BNEZ
          // bne r+8, x0, offset
          r = (halfword >> 7) & 0x7;
          offset = ((halfword & 0x1000) == 0x1000 ? 0xfffffe00 : 0) | // offset[31:9] <= [12]
            ((halfword >> 4) & 0x100) | // offset[8] <= [12]
            ((halfword >> 7) & 0x18) | // offset[4:3] <= [11:10]
            ((halfword << 1) & 0xc0) | // offset[7:6] <= [6:5]
            ((halfword >> 2) & 0x6) | // offset[2:1] <= [4:3]
            ((halfword << 3) & 0x20); // offset[5] <= [2]
          imm2 =
            ((offset >> 6) & 0x40) | // imm2[6] <= [12]
            ((offset >> 5) & 0x3f); // imm2[5:0] <= [10:5]
          imm1 =
            (offset & 0x1e) | // imm1[4:1] <= [4:1]
            ((offset >> 11) & 0x1); // imm1[0] <= [11]
          return (imm2 << 25) | ((r + 8) << 20) | (1 << 12) | (imm1 << 7) | 0x63;
        default:
          std::cout << "this should not happen" << std::endl;
      }
    case 2:
      switch (funct3) {
        case 0:
          // C.SLLI
          // slli r, r, shamt
          r = (halfword >> 7) & 0x1f;
          shamt =
            ((halfword >> 7) & 0x20) | // imm[5] <= [12]
            ((halfword >> 2) & 0x1f); // imm[4:0] <= [6:2]
          if (r != 0) {
            return (shamt << 20) | (r << 15) | (1 << 12) | (r << 7) | 0x13;
          }
          // r == 0 is reserved instruction?
        case 1:
          // C.FLDSP
          // fld rd, offset(x2)
          rd = (halfword >> 7) & 0x1f;
          offset =
            ((halfword >> 7) & 0x20) | // offset[5] <= [12]
            ((halfword >> 2) & 0x18) | // offset[4:3] <= [6:5]
            ((halfword << 4) & 0x1c0); // offset[8:6] <= [4:2]
          if (rd != 0) {
            return (offset << 20) | (2 << 15) | (3 << 12) | (rd << 7) | 0x7;
          }
          // rd == 0 is reseved instruction
        case 2:
          // C.LWSP
          // lw r, offset(x2)
          r = (halfword >> 7) & 0x1f;
          offset =
            ((halfword >> 7) & 0x20) | // offset[5] <= [12]
            ((halfword >> 2) & 0x1c) | // offset[4:2] <= [6:4]
            ((halfword << 4) & 0xc0); // offset[7:6] <= [3:2]
          if (r != 0) {
            return (offset << 20) | (2 << 15) | (2 << 12) | (r << 7) | 0x3;
          }
          // r == 0 is reseved instruction
        case 3:
          // @TODO: Support C.FLWSP in 32-bit mode
          // C.LDSP
          // ld rd, offset(x2)
          rd = (halfword >> 7) & 0x1f;
          offset =
            ((halfword >> 7) & 0x20) | // offset[5] <= [12]
            ((halfword >> 2) & 0x18) | // offset[4:3] <= [6:5]
            ((halfword << 4) & 0x1c0); // offset[8:6] <= [4:2]
          if (rd != 0) {
            return (offset << 20) | (2 << 15) | (3 << 12) | (rd << 7) | 0x3;
          }
          // rd == 0 is reseved instruction
        case 4:
          funct1 = (halfword >> 12) & 1; // [12]
          rs1 = (halfword >> 7) & 0x1f; // [11:7]
          rs2 = (halfword >> 2) & 0x1f; // [6:2]
          switch (funct1) {
            case 0:
              if (rs1 != 0 && rs2 == 0) {
                // C.JR
                // jalr x0, 0(rs1)
                return (rs1 << 15) | 0x67;
              }
              // rs1 == 0 is reserved instruction
              if (rs1 != 0 && rs2 != 0) {
                // C.MV
                // add rs1, x0, rs2
                // println!("C.MV RS1:{:x} RS2:{:x}", rs1, rs2);
                return (rs2 << 20) | (rs1 << 7) | 0x33;
              }
              // rs1 == 0 && rs2 != 0 is Hints
              // @TODO: Support Hints
            case 1:
              if (rs1 == 0 && rs2 == 0) {
                // C.EBREAK
                // ebreak
                return 0x00100073;
              }
              if (rs1 != 0 && rs2 == 0) {
                // C.JALR
                // jalr x1, 0(rs1)
                return (rs1 << 15) | (1 << 7) | 0x67;
              }
              if (rs1 != 0 && rs2 != 0) {
                // C.ADD
                // add rs1, rs1, rs2
                return (rs2 << 20) | (rs1 << 15) | (rs1 << 7) | 0x33;
              }
              // rs1 == 0 && rs2 != 0 is Hists
              // @TODO: Supports Hinsts
            default:
              std::cout << "this should not happen" << std::endl;
          }
        case 5:
          // @TODO: Implement
          // C.FSDSP
          // fsd rs2, offset(x2)
          rs2 = (halfword >> 2) & 0x1f; // [6:2]
          offset =
            ((halfword >> 7) & 0x38) | // offset[5:3] <= [12:10]
            ((halfword >> 1) & 0x1c0); // offset[8:6] <= [9:7]
          imm11_5 = (offset >> 5) & 0x3f;
          imm4_0 = offset & 0x1f;
          return (imm11_5 << 25) | (rs2 << 20) | (2 << 15) | (3 << 12) | (imm4_0 << 7) | 0x27;
        case 6:
          // C.SWSP
          // sw rs2, offset(x2)
          rs2 = (halfword >> 2) & 0x1f; // [6:2]
          offset =
            ((halfword >> 7) & 0x3c) | // offset[5:2] <= [12:9]
            ((halfword >> 1) & 0xc0); // offset[7:6] <= [8:7]
          imm11_5 = (offset >> 5) & 0x3f;
          imm4_0 = offset & 0x1f;
          return (imm11_5 << 25) | (rs2 << 20) | (2 << 15) | (2 << 12) | (imm4_0 << 7) | 0x23;
        case 7:
          // @TODO: Support C.FSWSP in 32-bit mode
          // C.SDSP
          // sd rs, offset(x2)
          rs2 = (halfword >> 2) & 0x1f; // [6:2]
          offset =
            ((halfword >> 7) & 0x38) | // offset[5:3] <= [12:10]
            ((halfword >> 1) & 0x1c0); // offset[8:6] <= [9:7]
          imm11_5 = (offset >> 5) & 0x3f;
          imm4_0 = offset & 0x1f;
          return (imm11_5 << 25) | (rs2 << 20) | (2 << 15) | (3 << 12) | (imm4_0 << 7) | 0x23;
        default:
          std::cout << "this should not happen" << std::endl;
      }
    default:
      std::cout << "illegal opcode in compressed instruction" << std::endl;
  }
}