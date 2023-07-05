#ifndef LABWORK_3_SUNLYOUS__PARSINGSYSTEM_H_
#define LABWORK_3_SUNLYOUS__PARSINGSYSTEM_H_

#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>

class ParsingSystem {
 private:
  uint16_t digit_length;
  uint16_t digit_width;
  std::string tab_separated_values;
  std::string path_to_the_directory;
  uint16_t number_of_iterations = 0;
  uint16_t save_frequency = 0;

  std::vector<std::string> commands; // вектор с командами из arcv
  int count; // == arc

  long int** picture; // массив двумерный

  void ParsingTsv();
  void ParsingValues();

 public:
  uint16_t getDigitLength();
  uint16_t getDigitWidth();
  uint16_t getNumberOfIterations();
  uint16_t getSaveFrequency();
  long int** getPicture();//гетеры
  std::string getPathToTheDirectory();

  ParsingSystem(int count_element, char** command);//конструктор
};

#endif //LABWORK_3_SUNLYOUS__PARSINGSYSTEM_H_