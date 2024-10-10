#pragma once

#include "common.hpp"
#include "instruction.hpp"

// opcodes
#define LUI_OP      0b0110111 // lui
#define AUIPC_OP    0b0010111 // aiupc
#define JAL_OP      0b1101111 // jal
#define JALR_OP     0b1100111 // jalr
#define BRANCH_OP   0b1100011 // beq, bne, blt, bge, bltu, bgeu
#define LOAD_OP     0b0000011 // lb, lh, lw, lbu, lhu
#define STORE_OP    0b0100011 // sb, sh, sw
#define ITYPE_OP    0b0010011 // addi, slti, sltiu, xori, ori, andi, slli, srli, srai, 
#define RTYPE_OP    0b0110011 // add, sub, sll, slt, sltu, xor, srl, sra, or, and
#define FENCE_OP    0b0001111 // fence
#define SYSCALL_OP  0b1110011 // ecall, ebreak


// beq, bne, blt, bge, bltu, bgeu
uop_t handle_branch_op(word_t word) {
  uint8_t funct3 = ((word && funct3_mask) >> 12);
  switch (funct3) {
    case 0b000:
      std::cout << "beq ";
      return uop_beq;
    case 0b001:
      std::cout << "bne ";
      return uop_bne;
    case 0b100:
      std::cout << "blt ";
      return uop_blt;
    case 0b101:
      std::cout << "bge ";
      return uop_bge;
    case 0b110:
      std::cout << "bltu ";
      return uop_bltu;
    case 0b111: // bgeu
      std::cout << "bgeu ";
      return uop_bgeu;
    default:
      std::cout << "illegal funct3 in BRANCH_OP ";
  }
}

// lb, lh, lw, lbu, lhu
uop_t handle_load_op(word_t word) {
  uint8_t funct3 = ((word && funct3_mask) >> 12);
  switch (funct3) {
    case 0b000:
      std::cout << "lb ";
      return uop_lb;
    case 0b001:
      std::cout << "lh ";
      return uop_lh;
    case 0b010:
      std::cout << "lw ";
      return uop_lw;
    case 0b100:
      std::cout << "lbu ";
      return uop_lbu;
    case 0b101:
      std::cout << "lhu ";
      return uop_lhu;
    default:
      std::cout << "illegal funct3 in LOAD_OP ";
  }
}

// sb, sh, sw
uop_t handle_store_op(word_t word) {
  uint8_t funct3 = ((word && funct3_mask) >> 12);
  switch (funct3) {
    case 0b000: // sb
      std::cout << "sb ";
      return uop_sb;
    case 0b001: // sh
      std::cout << "sh ";
      return uop_sh;
    case 0b010: // sw
      std::cout << "sw ";
      return uop_sw;
    default:
      std::cout << "illegal funct3 in STORE_OP ";
  }
}

// addi, slti, sltiu, xori, ori, andi, slli, srli, srai
uop_t handle_itype_op(word_t word) {
  uint8_t funct3 = ((word && funct3_mask) >> 12);
  switch (funct3) {
    case 0b000: // addi
      std::cout << "addi ";
      return uop_addi;
    case 0b010: // slti
      std::cout << "slti ";
      return uop_slti;
    case 0b011: // sltiu
      std::cout << "sltiu ";
      return uop_sltiu;
    case 0b100: // xori
      std::cout << "xori ";
      return uop_xori;
    case 0b110: // ori
      std::cout << "ori ";
      return uop_ori;
    case 0b111: // andi
      std::cout << "andi ";
      return uop_andi;
    case 0b001: // slli
      std::cout << "slli ";
      return uop_slli;
    case 0b101: {// srli, srai
      uint8_t funct7 = ((word && funct7_mask) >> 25);
      if (funct7 == 0b0000000) {
        std::cout << "srli ";
      } else if (funct7 == 0b0100000) {
        std::cout << "srai ";      
      } else {
        std::cout << "illegal funct7 in ITYPE_OP ";
      }
    }
    default:
      std::cout << "illegal funct3 in ITYPE_OP ";
  }
}

// add, sub, sll, slt, sltu, xor, srl, sra, or, and
uop_t handle_rtype_op(word_t word) {
  uint8_t funct3 = ((word && funct3_mask) >> 12);
  switch (funct3) {
    case 0b000: { // addi
      uint8_t funct7 = ((word && funct7_mask) >> 25);
      if (funct7 == 0b0000000) {
        std::cout << "add ";
      } else if (funct7 == 0b0100000) {
        std::cout << "sub ";      
      } else {
        std::cout << "illegal funct7 in RTYPE_OP ";
      }
    }
    case 0b001:
      return uop_sll;
    case 0b010:
      return uop_slt;
    case 0b011:
      return uop_sltu;
    case 0b100:
      return uop_xor;
    case 0b101: {
      uint8_t funct7 = ((word && funct7_mask) >> 25);
      if (funct7 == 0b0000000) {
        return uop_srl;
      } else if (funct7 == 0b0100000) {
        return uop_sra;
      } else {
        std::cout << "illegal funct7 in RTYPE_OP ";
      }
    }
    case 0b110:
      return uop_or;
    case 0b111:
      return uop_and;
  }
};

uop_t handle_syscall_op(word_t word) {
  // uint8_t funct3 = ((word && funct3_mask) >> 12);
  uint16_t imm = ((word && itype_imm_mask) >> 20);
  if (imm == 0b000000000000) {
    return uop_ecall;
  } else if (imm == 0b000000000001) {
    return uop_ebreak;    
  } else {
    std::cout << "illegal imm in SYSCALL_OP ";
  }
}

class Decoder {
public:
  uop_t decode(word_t word);
  word_t decompress(hword_t hword);
};

uop_t Decoder::decode(word_t word) {
  uint8_t opcode = word & opcode_mask;
  switch (opcode) {
    case LUI_OP:      // lui
      return uop_lui;
    case AUIPC_OP:    // aiupc
      return uop_auipc;
    case JAL_OP:      // jal
      return uop_jal;
    case JALR_OP:     // jalr
      return uop_jalr;
    case BRANCH_OP:   // beq, bne, blt, bge, bltu, bgeu
      return handle_branch_op(word);
    case LOAD_OP:     // lb, lh, lw, lbu, lhu
      return handle_load_op(word);
    case STORE_OP:    // sb, sh, sw
      return handle_store_op(word);
    case ITYPE_OP:    // addi, slti, sltiu, xori, ori, andi, slli, srli, srai, 
      return handle_itype_op(word);
    case RTYPE_OP:    // add, sub, sll, slt, sltu, xor, srl, sra, or, and
      return handle_rtype_op(word);
    case FENCE_OP:    // fence
      return uop_fence;
    case SYSCALL_OP:  // ecall, ebreak
      return handle_syscall_op(word);
    default:
      std::cout << "illegal opcode ";
  }
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

