#pragma once

#include <map>
#include <vector>
#include <iostream>
#include <iomanip>
#include <cstdint>
#include <functional>

std::map<uint8_t, std::string> registers = {
  {0, "zero"},   // hardwired zero
  {1, "ra"},  // return address
  {2, "sp"},  // stack pointer
  {3, "gp"},  // global pointer
  {4, "tp"},  // thread pointer
  {5, "t0"},  // temporary register 0
  {6, "t1"},  // temporary register 1
  {7, "t2"},  // temporary register 2
  {8, "s0"},  // saved register 0 / frame pointer
  {9, "s1"},  // saved register 1
  {10, "a0"},  // function argument 0 / return value 0
  {11, "a1"},  // function argument 1 / return value 1
  {12, "a2"},  // function argument 2
  {13, "a3"},  // function argument 3
  {14, "a4"},  // function argument 4
  {15, "a5"},  // function argument 5
  {16, "a6"},  // function argument 6
  {17, "a7"},  // function argument 7
  {18, "s2"},  // saved register 2
  {19, "s3"},  // saved register 3
  {20, "s4"},  // saved register 4
  {21, "s5"},  // saved register 5
  {22, "s6"},  // saved register 6
  {23, "s7"},  // saved register 7
  {24, "s8"},  // saved register 8
  {25, "s9"},  // saved register 9
  {26, "s10"},   // saved register 10
  {27, "s11"},   // saved register 11
  {28, "t3"},  // temporary register 3
  {29, "t4"},  // temporary register 4
  {30, "t5"},  // temporary register 5
  {31, "t6"},  // temporary register 6
};

enum reg {
  zero,// hardwired zero
  ra,  // return address
  sp,  // stack pointer
  gp,  // global pointer
  tp,  // thread pointer
  t0, t1, t2,  // temporary register 0-2
  s0,  // saved register 0 / frame pointer
  fp,  // saved register 0 / frame pointer
  s1,  // saved register 1
  a0,  // function argument 0 / return value 0
  a1,  // function argument 1 / return value 1
  a2, a3, a4, a5, a6, a7,  // function argument 2-7
  s2, s3, s4, s5, s6, s7, s8, s9, s10, s11, // saved register 2-11
  t3, t4, t5, t6, // temporary register 3-6
};

using byte_t = uint8_t;
using hword_t = uint16_t;
using word_t = uint32_t;
using dword_t = uint64_t;
using uop_t = uint8_t;
