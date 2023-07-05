#ifndef LABWORK_3_SUNLYOUS__SCATTERINGSYSTEM_H_
#define LABWORK_3_SUNLYOUS__SCATTERINGSYSTEM_H_

#include "ImageSystem.h"
#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <math.h>

class ScatteringSystem {
 private:
  long int** image;
  uint16_t frequency_image = 0;
  uint16_t length_image;
  uint16_t width_image;
  bool flag_image = false;
  uint16_t number_of_iteration_image = 0;
  void ScatteringOfGrainsOfSand();
  std::string path_to_the_directory_image;

 public:
  long int** get_image();

  ScatteringSystem(uint16_t digit_length,
                   uint16_t digit_width,
                   uint16_t number_of_iteration,
                   long int** picture,
                   uint16_t frequency_image,
                   std::string path_to_the_directory);
};

#endif //LABWORK_3_SUNLYOUS__SCATTERINGSYSTEM_H_