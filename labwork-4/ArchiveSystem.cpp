#include "ArchiveSystem.h"

void ArchiveSystem::CreateArchive() {
  if (flag_create) {
    std::string name_archive = arhcname_save + ".haf";
    for (int i = 0; i < file_names.size(); i++) {
      FileAdd(file_names[i], name_archive);

    }

  }

}
void ArchiveSystem::ListArchive() {
  if (flag_list) {
    HammingSystem Hamming;
    std::ifstream Archive;
    Archive.open(arhcname_save, std::ios::binary | std::ios::app);
    unsigned char cin;
    std::string list_name;
    std::string size;
    while (!Archive.eof()) {
      if (Archive.eof()) {
        break;
      }

      for (int i = 0; i < kMaxLengthNameFile; i++) {
        cin = Archive.get();
        list_name += cin;
      }
      if (Archive.eof()) {
        break;
      }

      std::string file_name = DecodeNameFile(list_name);
      std::cout << file_name << "\n";
      list_name = "";
      for (int i = 0; i < kMaxLengthFileSize; i++) {
        cin = Archive.get();
        size += cin;
      }

      std::string size_cin = DecodeSizeFile(size);
      //раскодировка длины
      for (int i = 0; i < (std::stoi(size_cin) * 2); i++) {
        cin = Archive.get();
      }

    }

  }
}
void ArchiveSystem::AppendFile() {
  if (flag_append) {
    FileAdd(file_append, arhcname_save);
  }

}
void ArchiveSystem::ExtractFile() {
  if (flag_extract) {
    std::ifstream Archive;
    Archive.open(arhcname_save, std::ios::binary | std::ios::out | std::ios::app);
    unsigned char cin;
    std::string file;
    std::string size;
    int count = 0;
    while (!Archive.eof()) {
      if (Archive.eof()) {
        break;
      }
        for (int k = 0; k < file_names.size(); k++) {
          count++;
          for (int i = 0; i < kMaxLengthNameFile; i++) {
            cin = Archive.get();
            file += cin;
          }
          if (Archive.eof()) {
            break;
          }
          std::string file_name = DecodeNameFile(file);
          std::string file_comparison;
          //расскодировка
          for (int i = 0; i < file_names[k].size(); i++) {
            file_comparison += file_name[i];
          }
          if (file_comparison == file_names[k]) {
            for (int i = 0; i < kMaxLengthFileSize; i++) {
              cin = Archive.get();
              size += cin;
            }
            std::string size_decode = DecodeSizeFile(size);
            //раскодировка длины
            std::ofstream file_extract;
            file_extract.open(file_comparison, std::ios::binary | std::ios::app);
            std::string element;
            for (int i = 0; i < std::stoi(size_decode) * 2; i++) {
              cin = Archive.get();
              element += cin;
              if (element.size() == 2) {
                std::string element_decode = DecodeNameFile(element);
                file_extract << element_decode;
                element = "";
              }

            }
            if (Archive.eof()) {
              break;
            }
          } else {
            for (int i = 0; i < kMaxLengthFileSize; i++) {
              cin = Archive.get();
              size += cin;
            }

            for (int i = 0; i < std::stoi(size); i++) {
              cin = Archive.get();
            }

            if (Archive.eof()) {
              break;
            }

          }
          size = "";
          file = "";
        }
        if(count == file_names.size()) {
          break;
        }
      if (file_names.size() == 0) {
        for (int i = 0; i < kMaxLengthNameFile; i++) {
          cin = Archive.get();
          file += cin;
        }
        if (Archive.eof()) {
          break;
        }
        std::string file_name = DecodeNameFile(file);
        for (int i = 0; i < kMaxLengthFileSize; i++) {
          cin = Archive.get();
          size += cin;
        }
        std::string decode_size = DecodeSizeFile(size);
        //раскодировка длины
        std::ofstream file_extract;
        file_extract.open(file_name, std::ios::binary | std::ios::app);
        std::string element;
        for (int i = 0; i < std::stoi(decode_size) * 2; i++) {
          cin = Archive.get();
          element += cin;
          if (element.size() == 2) {
            std::string element_decode = DecodeNameFile(element);
            file_extract << element_decode;
            element = "";
          }
        }

      }
      size = "";
      file = "";
    }
  }

}
void ArchiveSystem::DeleteFile() {
  if (flag_delete) {
    Header header;
    std::string tmp_name = "tmp.haf";
    std::ifstream Archive;
    Archive.open(arhcname_save, std::ios::binary | std::ios::app | std::ios::in);
    unsigned char cin;
    std::string file;
    std::string size;
    std::ofstream tmp;
    tmp.open(tmp_name, std::ios::binary | std::ios::app);
    while (!Archive.eof()) {
      if (Archive.eof()) {
        break;
      }

      for (int i = 0; i < kMaxLengthNameFile; i++) {
        cin = Archive.get();
        file += cin;
      }

      if (Archive.eof()) {
        break;
      }
      std::string file_name;
      std::string file_comparison;
      file_name = DecodeNameFile(file);
      //расскодировка
      if (Archive.eof()) {
        break;
      }
      for (int i = 0; i < file_delete.size(); i++) {
        file_comparison += file_name[i];
      }

      if (file_comparison == file_delete) {
        for (int i = 0; i < kMaxLengthFileSize; i++) {
          cin = Archive.get();
          size += cin;
        }
        std::string size_file = DecodeSizeFile(size);
        //раскодировка длины
        for (int i = 0; i < (std::stoi(size_file) * 2); i++) {
          cin = Archive.get();
        }

      } else {
        //расскодировка если придет true вырубаю прогу(функция которую мне скинули)
        for (int i = 0; i < kMaxLengthFileSize; i++) {
          cin = Archive.get();
          size += cin;
        }
        std::string size_file = DecodeSizeFile(size);
        header.CreateHeader(tmp_name, file, size);
        //раскодировка длины
        //кодировка и запись в файл tmp

        for (int i = 0; i < (std::stoi(size_file) * 2); i++) {
          cin = Archive.get();

          tmp << cin;
        }
      }
      size = "";
      file = "";
    }
    tmp.close();
    Archive.close();
    std::remove(arhcname_save.c_str());
    std::filesystem::rename(tmp_name, arhcname_save);
  }
}
void ArchiveSystem::ConcatenateArchive() {
  if (flag_merge) {
    std::string name_archive = arhcname_save + ".haf";
    FileAdd(arhcname_one_merge, name_archive);
    FileAdd(arhcname_two_merge, name_archive);
  }
}
std::string ArchiveSystem::DecodeSizeFile(std::string size) {
  HammingSystem Hamming;
  std::string size_decode;
  unsigned char size_element;
  std::string size_give;
  for (int j = 0; j < size.size(); j++) {
    size_decode += Hamming.HammingDecoding(size[j]);
    if (size_decode.size() == 8) {
      for (int k = 0; k < size_decode.size(); k++) {
        size_element = (size_element << 1) + (size_decode[k] - '0');
      }
      size_give += size_element;
      size_element = 0;
      size_decode = "";
    }
  }
  return size_give;
}
std::string ArchiveSystem::DecodeNameFile(std::string file) {
  HammingSystem Hamming;
  std::string decode_char;
  std::string name_file;
  unsigned char element_name_file;
  for (int i = 0; i < file.size(); i++) {
    decode_char += Hamming.HammingDecoding(file[i]);
    if (decode_char.size() == 8) {
      for (int j = 0; j < decode_char.size(); j++) {
        element_name_file = (element_name_file << 1) + (decode_char[j] - '0');
      }

      name_file += element_name_file;
      element_name_file = 0;
      decode_char = "";
    }

  }
  return name_file;
}
void ArchiveSystem::FileAdd(std::string file_name, std::string name_archive) {
  Header header;
  HammingSystem Hamming;
  std::string name_code;

  for (int j = 0; j < file_name.size(); j++) {
    std::pair<unsigned char, unsigned char> element = Hamming.CodingElement(file_name[j]);
    name_code += element.first;
    name_code += element.second;
  }

  std::ifstream file(file_name, std::ios::binary);
  file.seekg(0, std::ios::end);
  int size_code = file.tellg();
  file.seekg(0, std::ios::beg);
  std::string size_code_string = std::to_string(size_code);
  std::string size_element;
  for (int j = 0; j < size_code_string.size(); j++) {
    std::pair<unsigned char, unsigned char> element = Hamming.CodingElement(size_code_string[j]);//**
    size_element += element.first;
    size_element += element.second;
  }

  header.CreateHeader(name_archive, name_code, size_element);
  name_code = "";
  size_element = "";
  std::fstream Archive;
  Archive.open(name_archive, std::ios::binary | std::ios::app);
  std::ifstream file_text;
  file_text.open(file_name, std::ios::binary | std::ios::app);
  while (!file_text.eof()) {
    unsigned char tmp = file_text.get();
    if (file_text.eof()) {
      break;
    }

    std::pair<unsigned char, unsigned char> element = Hamming.CodingElement(tmp);
    size_element += element.first;
    size_element += element.second;
    Archive << size_element;
    size_element = "";
  }

  Archive.close();
}

ArchiveSystem::ArchiveSystem(
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
    std::string file_append) {
  this->arhcname_save = arhcname_save;
  this->file_extract = file_extract;
  this->arhcname_one_merge = arhcname_one_merge;
  this->arhcname_two_merge = arhcname_two_merge;
  this->output_arhcfile = output_arhcfile;
  this->file_delete = file_delete;
  this->flag_extract = flag_extract;
  this->flag_delete = flag_delete;
  this->flag_merge = flag_merge;
  this->flag_create = flag_create;
  this->file_names = file_names;
  this->flag_list = flag_list;
  this->bit_size = bit_size;
  this->file_append = file_append;
  this->flag_append = flag_append;
  CreateArchive();
  ListArchive();
  AppendFile();
  DeleteFile();
  ConcatenateArchive();
  ExtractFile();
}



