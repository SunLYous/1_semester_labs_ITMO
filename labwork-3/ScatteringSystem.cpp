#include "ScatteringSystem.h"

void ScatteringSystem::ScatteringOfGrainsOfSand() {

  int count = 0;
  ImageSystem Image(length_image, width_image);
  while (!flag_image) {
    count++;
    for (int y = 0; y < width_image; y++) {
      for (int x = 0; x < length_image; x++) {
        if (image[y][x] > 3) {
          if (x - 1 >= 0) {
            image[y][x - 1] += 1;
            if (image[y][x - 1] > 3) {
              flag_image = true;
            }

          }

          if (x + 1 < length_image ) {
            image[y][x + 1] += 1;
            if (image[y][x + 1]) {
              flag_image = true;
            }
          }

          if (y - 1 >= 0) {
            image[y - 1][x] += 1;
            if (image[y - 1][x] > 3) {
              flag_image = true;
            }
          }

          if (y + 1 < width_image ) {
            image[y + 1][x] += 1;
            if (image[y + 1][x] > 3) {
              flag_image = true;
            }
          }

          image[y][x] -= 4;
        }

        if (image[y][x] > 3) {
          flag_image = true;
        }
      }

    }
    if ((frequency_image != 0 && count % frequency_image == 0)
        || (!flag_image && frequency_image == 0)
        || count + 1 == number_of_iteration_image) {

      for (uint16_t y = 0; y < width_image  ; y++) {
        for (uint16_t x = 0; x < length_image ; x++) {

          if (image[y][x] == 0) {
            Image.setColor(Image.getWhiteColor(), (y *  cs + x * sn)  , (x * cs - y * sn));
          } else if (image[y][x] == 1) {
            Image.setColor(Image.getGreenColor(), (y *  cs + x * sn), rx);
          } else if (image[y][x] == 2) {
            Image.setColor(Image.getMagentaColor(), (y *  cs + x * sn), (x * cs - y * sn));
          } else if (image[y][x] == 3) {
            Image.setColor(Image.getYellowColor(), (y *  cs + x * sn), (x * cs - y * sn));
          } else if (image[y][x] > 3) {
            Image.setColor(Image.getBlackColor(), (y *  cs + x * sn), (x * cs - y * sn));
          }


        }

      }

      Image.Export(path_to_the_directory_image + '\\' + std::to_string(count) + ".bmp");
    }

    if (flag_image == false || count == number_of_iteration_image) { break; }
    else if (flag_image == true) {
      flag_image = false;
    }

  }

}

long int** ScatteringSystem::get_image() {

  return image;
}

ScatteringSystem::ScatteringSystem(uint16_t digit_length,
                                   uint16_t digit_width,
                                   uint16_t number_of_iteration,
                                   long int** picture, uint16_t frequency, std::string path_to_the_directory) {
  length_image = digit_length;
  width_image = digit_width;
  number_of_iteration_image = number_of_iteration;
  image = picture;
  frequency_image = frequency;
  path_to_the_directory_image = path_to_the_directory;

  ScatteringOfGrainsOfSand();
}
