#ifndef LAB4__HEADER_H_
#define LAB4__HEADER_H_

#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <bitset>
#include <math.h>
#include <iostream>
#include <cstring>

class Header {
 private:
  const int kMaxLengthNameFile = 20;
  const int kMaxLengthFileSize = 60;
  int size_file = 0;
  int file_size;
  std::string archive_name;
 public:
  void CreateHeader(std::string archive, std::string file_name, std::string size_char);
};

#endif //LAB4__HEADER_H_
