#include <fstream>
#include <iostream>
#include <string>
#include <vector>

// #include "../utils.hpp"
#include "../decoder.hpp"

int main(int argc, char **argv) {
  if (argc != 3) {
    std::cout << "Usage: ./test_decoder <file.hex> <file.asm>" << std::endl;
  }

  std::string hex_filepath = argv[1];
  std::string asm_filepath = argv[2];

  // std::cout << hex_filepath << std::endl;
  // std::cout << asm_filepath << std::endl;
  std::string line;

  std::ifstream hex_file(hex_filepath);
  std::vector<std::string> hex_lines;
  if (!hex_file.is_open()) {
    std::cout << "Could not open HEX file" << std::endl;
    return 1;
  }

  while (std::getline(hex_file, line)) {
    hex_lines.push_back(line);
  }

  hex_file.close();

  std::fstream asm_file(asm_filepath);
  std::vector<std::string> asm_lines;
  if (!asm_file.is_open()) {
    std::cout << "Could not open ASM file" << std::endl;
    return 1;
  }


  while (std::getline(asm_file, line)) {
    asm_lines.push_back(line);
  }

  Decoder decoder;

  // for (auto item: test_program) {
  //   if (Decoder.decode(item.first) != item.second) {
  //     std::__throw_bad_exception();
  //   }
  // }

  return 0;
}