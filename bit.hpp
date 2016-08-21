#ifndef BIT_L
#define BIT_L

#include <bitset>
#include <string>
#include <vector>

std::bitset<64> sToBit(std::string msg);

std::vector<std::string> byBlock(std::string msg);

std::string bToString(std::bitset<64> bitset);

std::string bToHex(std::bitset<64> bitset);

std::bitset<64> HextoBit(std::string msg);

void printBitset(std::vector<std::bitset<64>> bitset, size_t final,int ch);

#endif