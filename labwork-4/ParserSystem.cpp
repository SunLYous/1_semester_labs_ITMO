#include "ParserSystem.h"

void ParsingSystem::ParsingValues() {
  for (int i = 1; i < count; i++) {
    if (commands[i] == "--create" || commands[i] == "-c") {
      flag_create = true;
      int k = 1;
      while (i + k < count  && i + k - 1 > 0) {
        if (commands[i + k][0] != '-'&& commands[i + k - 1] != "-f") {
          file_names.push_back(commands[i + k]);
        }

        k++;
      }

    }

    if ((commands[i][0] == '-' && commands[i][1] == '-' && commands[i][2] == 'f')) {
      for (int k = 2; k < commands[i].size(); k++) {
        if (commands[i][k] == '=') {
          for (int j = k + 1; j < commands[i].size(); j++) {
            arhcname_save += commands[i][j];
          }

        }

      }

    } else if (commands[i][0] == '-' && commands[i][1] == 'f') {
      arhcname_save = commands[i + 1];
    }

    if (commands[i] == "--list" || commands[i] == "-l") {
      flag_list = true;
    }

    if (commands[i] == "--extract" || commands[i] == "-x") {
      flag_extract = true;
      int k = 1;
      while (i + k < count) {
        if (commands[i + k][0] != '-' && commands[i + k - 1] != "-f" && i + k - 1 > 0) {
          file_names.push_back(commands[i + k]);
        }

        k++;
      }

    }

    if (commands[i] == "--delete" || commands[i] == "-d") {
      for (int j = 1; j < commands.size(); j++) {
        if (commands[j][0] != '-' && commands[j - 1] != "-f" && j - 1 > 0) {
          file_delete = commands[j];
        }

      }

      flag_delete = true;
    }

    if (commands[i] == "--concatenate" || commands[i] == "-A") {
      for (int j = 1; j < commands.size(); j++) {
        if (commands[j][0] != '-' && commands[j - 1] != "-f" ) {
          arhcname_one_merge = commands[j];
          arhcname_two_merge = commands[j + 1];
          break;
        }

      }
      flag_merge = true;
    }

    if ((commands[i][0] == '-' && commands[i][1] == '-' && commands[i][2] == 'b')
        || (commands[i][0] == '-' && commands[i][1] == 'b')) {
      for (int k = 0; k < commands.size(); k++) {
        if (commands[i][k] == '=') {
          for (int j = k + 1; j < commands[i].size(); j++) {
            bits_size += commands[i][j];
          }

          bit_size = std::stoi(bits_size);
        }

      }

    }
    if (commands[i] == "-a" || commands[i] == "--append") {
      for(int j = 1; j < commands.size(); j++) {
        if (commands[j][0] != '-' && commands[j - 1] != "-f" ) {
          file_append = commands[j];
        }
      }
      flag_append = true;
    }

  }

}

ParsingSystem::ParsingSystem(int count_element, char** command) {
  count = count_element;
  for (int i = 0; i < count; i++) {
    commands.push_back(command[i]);
  }

  ParsingValues(); //вызов метода парсинга значений из командной строки
}

std::string ParsingSystem::getArhcnameSave() {

  return arhcname_save;
}

std::string ParsingSystem::getFileExtract() {

  return file_extract;
}

std::string ParsingSystem::getarhcnameOneMerge() {

  return arhcname_one_merge;
}

std::string ParsingSystem::getArhcnameTwoMerge() {

  return arhcname_two_merge;
}

std::string ParsingSystem::getOutputArhcFile() {

  return output_arhcfile;
}
std::string ParsingSystem::getFileDelete() {

  return file_delete;
}
bool ParsingSystem::getFlagExtract() {

  return flag_extract;
}
std::vector<std::string> ParsingSystem::getFileNames() {

  return file_names;
}
bool ParsingSystem::getFlagDelete() {

  return flag_delete;
}
bool ParsingSystem::getFlagMerge() {

  return flag_merge;
}
bool ParsingSystem::getFlagCreate() {

  return flag_create;
}
bool ParsingSystem::getFlagList() {

  return flag_list;
}
int ParsingSystem::getBitSize() {

  return bit_size;
}
bool ParsingSystem::getFlagAppend() {

  return flag_append;
}
std::string ParsingSystem::getFileAppend() {

  return file_append;
}

