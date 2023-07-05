#include "ParsingSystem.h"

void ParsingSystem::ParsingTsv() {
  std::ifstream file_name(tab_separated_values);
  int grits_x;
  int grits_y;
  int amount_grits;
  std::string value;
  std::stringstream value_s; // поток из стрингов

  picture = new long int* [digit_width];
  for (int i = 0; i < digit_width; i++) {
    picture[i] = new long int[digit_length]{};
  } // создание двумерного массива

  while (getline(file_name, value)) {
    value_s << value; // заполняем поток стрингами
    value_s >> grits_y >> grits_x >> amount_grits; // достаем из потока
    picture[grits_y][grits_x] = amount_grits;
  } // считывание значений из директории tsv

}

void ParsingSystem::ParsingValues() {
  for (int i = 0; i < count - 1; i++) {
    std::string command = commands[i];
    if (command == "--length" || command == "-l") {
      digit_length = std::stoi(commands[i + 1]);
    }

    if (command == "--width" || command == "-w") {
      digit_width = std::stoi(commands[i + 1]);
    }

    if (command == "--input" || command == "-i") {
      tab_separated_values = commands[i + 1];
    }

    if (command == "--output" || command == "-o") {
      path_to_the_directory = commands[i + 1];
    }

    if (command == "--max-iter" || command == "-m") {
      number_of_iterations = std::stoi(commands[i + 1]);
    }

    if (command == "--freq" || command == "-f") {
      save_frequency = std::stoi(commands[i + 1]);
    }

  }

}

uint16_t ParsingSystem::getDigitLength() {

  return digit_length;
}

uint16_t ParsingSystem::getDigitWidth() {

  return digit_width;
}

uint16_t ParsingSystem::getNumberOfIterations() {

  return number_of_iterations;
}

uint16_t ParsingSystem::getSaveFrequency() {

  return save_frequency;
}

long int** ParsingSystem::getPicture() {

  return picture;
}

ParsingSystem::ParsingSystem(int count_element, char** command) {
  for (int i = 0; i < count_element; i++) {
    commands.push_back(command[i]);
  }

  ParsingValues(); //вызов метода парсинга значений из командной строки
  ParsingTsv();//вызов метода парсинга tsv
}
std::string ParsingSystem::getPathToTheDirectory() {

  return path_to_the_directory;
}
//конструктор с вызовом методов
