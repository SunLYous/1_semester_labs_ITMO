#ifndef LAB4__PARSERSYSTEM_H_
#define LAB4__PARSERSYSTEM_H_

#include<string>
#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>

class ParsingSystem {
 private:
  std::string arhcname_save;
  std::string file_extract;
  std::string arhcname_one_merge;
  std::string arhcname_two_merge;
  std::string output_arhcfile;
  std::string bits_size;
  std::string file_append;
  int bit_size;
  std::string file_delete;
  bool flag_extract = false;
  bool flag_delete = false;
  bool flag_merge = false;
  bool flag_create = false;
  bool flag_list = false;
  bool flag_append = false;
  std::vector<std::string> commands; // вектор с командами из arcv
  int count; // == arc

  std::vector<std::string> file_names; // массив
  void ParsingValues();

 public:
  bool getFlagAppend();
  std::string getFileAppend();
  std::string getArhcnameSave();
  std::string getFileExtract();
  std::string getarhcnameOneMerge();
  std::string getArhcnameTwoMerge();
  std::string getOutputArhcFile();
  std::string getFileDelete();
  bool getFlagExtract();
  std::vector<std::string> getFileNames();
  bool getFlagDelete();
  bool getFlagMerge();
  bool getFlagCreate();
  bool getFlagList();
  int getBitSize(); //длина кодировки
  ParsingSystem(int count_element, char** command);//конструктор
};
#endif //LAB4__PARSERSYSTEM_H_
