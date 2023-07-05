#ifndef LAB4__ARCHIVESYSTEM_H_
#define LAB4__ARCHIVESYSTEM_H_

#include "Header.h"
#include "HammingSystem.h"

#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <bitset>
#include <iostream>
#include <cstring>
#include <filesystem>
#include <cstdio>

class ArchiveSystem {
 private:
  void CreateArchive();
  void ListArchive();
  void AppendFile();
  void DeleteFile();
  void ConcatenateArchive();
  void ExtractFile();

  std::string arhcname_save;
  std::string file_extract;
  std::string arhcname_one_merge;
  std::string arhcname_two_merge;
  std::string output_arhcfile;
  std::string file_delete;
  bool flag_extract;
  bool flag_delete;
  bool flag_merge;
  bool flag_create;
  std::vector<std::string> file_names;
  bool flag_list;
  int bit_size;
  bool flag_append;
  std::string file_append;
  std::string size_char;
  const int kMaxLengthNameFile = 20;
  const int kMaxLengthFileSize = 60;

  void FileAdd(std::string file_name, std::string archive_name);
  std::string DecodeSizeFile(std::string size);
  std::string DecodeNameFile(std::string file);
 public:

  ArchiveSystem(
      std::string arhcname_save,
      std::string file_extract,
      std::string arhcname_one_merge,
      std::string arhcname_two_merge,
      std::string output_arhcfile,
      std::string file_delete,
      bool flag_extract,
      bool flag_delete,
      bool flag_merge,
      bool flag_create,
      std::vector<std::string> file_names,
      bool flag_list,
      int bit_size,
      bool flag_append,
  std::string file_append
  );

};
#endif //LAB4__ARCHIVESYSTEM_H_
