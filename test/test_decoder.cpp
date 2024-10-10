#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "../utils.hpp"
#include "../decoder.hpp"

int main(int argc, char **argv) {
  if (argc != 3) {
    std::cout << "Usage: ./test_decoder <file.hex> <file.asm>" << std::endl;
  }

  std::string hex_filepath = argv[1];
  std::string asm_filepath = argv[2];
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

  asm_file.close();

  Decoder decoder;

  if (hex_lines.size() != asm_lines.size()) {
    throw std::runtime_error("HEX and ASM files should have same number of lines.");
  }

  size_t n_lines = hex_lines.size();
  word_t w;

  for (size_t i = 0; i < n_lines; ++i) {
    // convert hex string to binary
    std::string bin_str = hex_to_bin(hex_lines[i]);

    if (bin_str.size() == 16) {
      std::bitset<16> hw(bin_str);
      w = decoder.decompress(static_cast<hword_t>(hw.to_ulong()));
    } else if (bin_str.size() == 32) {
      std::bitset<32> fw(bin_str);
      w = static_cast<word_t>(fw.to_ulong());
    } else {
      throw std::runtime_error("Something wrong with line " + std::to_string(i) + " in .hex file");
    }

    std::cout << asm_lines[i] << "\t" << decoder.decode(w) << std::endl;
    // if (decoder.decode() != asm_lines[i]) {
    //   std::cout << hex_lines[i] << " ERROR decoding" << std::endl;
    // }

  }

  return 0;
}