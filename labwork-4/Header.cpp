#include "Header.h"

void Header::CreateHeader(std::string Archive, std::string file_name, std::string size_char) {
  std::ofstream archive_with_file;
  archive_with_file.open(Archive, std::ios::binary | std::ios::app);
  file_size = file_name.size();
  unsigned char* FileHeader = new unsigned char[kMaxLengthNameFile];
  unsigned char* FileSizeHeader = new unsigned char[kMaxLengthFileSize];
  for (int i = 0; i < file_size ; i++) {
    FileHeader[i] = file_name[i];
  }
  for(int i = file_size; i < kMaxLengthNameFile; i++){
    FileHeader[i] = 0;
  }
  for (int i = 0; i < size_char.size(); ++i) {
    FileSizeHeader[i] = size_char[i];
  }
  for(int i = size_char.size(); i < kMaxLengthFileSize; i++) {
    FileSizeHeader[i] = 0;
  }
  archive_with_file.write(reinterpret_cast <const char*>(FileHeader), kMaxLengthNameFile);
  archive_with_file.write(reinterpret_cast <const char*>(FileSizeHeader), kMaxLengthFileSize);
  std::cout << "Name created\n";
  archive_with_file.close();
}
