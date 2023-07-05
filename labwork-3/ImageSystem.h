#ifndef LABWORK_3_SUNLYOUS__IMAGESYSTEM_H_
#define LABWORK_3_SUNLYOUS__IMAGESYSTEM_H_

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

struct Color {
  short red;
  short green;
  short blue;
  Color();
  Color(short red, short green, short blue);
};

class ImageSystem {
 private:
  uint16_t length_bmp;
  uint16_t width_bmp;
  std::vector<Color> color_bmp;
  uint16_t const kSize = 40;
  const Color kWhiteColor{255, 255, 255};
  const Color kGreenColor{0, 255, 0};
  const Color kMagentaColor{128, 0, 128};
  const Color kYellowColor{255, 255, 0};
  const Color kBlackColor{0, 0, 0};

 public:
  ImageSystem(uint16_t digit_length, uint16_t digit_width);

  Color getWhiteColor();
  Color getGreenColor();
  Color getMagentaColor();
  Color getYellowColor();
  Color getBlackColor();

  Color getColor(uint16_t y, uint16_t x);
  void setColor(Color color, uint16_t y, uint16_t x);

  void Export(std::string way);
};

#endif //LABWORK_3_SUNLYOUS__IMAGESYSTEM_H_