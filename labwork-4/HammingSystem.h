#ifndef LAB4__HAMMINGSYSTEM_H_
#define LAB4__HAMMINGSYSTEM_H_

#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <bitset>
#include <math.h>
#include <iostream>
#include <cstring>

class HammingSystem {
 public:
  std::pair<unsigned char, unsigned char> CodingElement(unsigned char element);
  unsigned char HammingCode(std::string element);
  std::string  HammingDecoding(unsigned char element);

};

#endif //LAB4__HAMMINGSYSTEM_H_
