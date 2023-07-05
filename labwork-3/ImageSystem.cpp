#include "ImageSystem.h"

Color::Color()
    : red(0), green(0), blue(0) {}
Color::Color(short red, short green, short blue)
    : red(red), green(green), blue(blue) {}
ImageSystem::ImageSystem(uint16_t length, uint16_t width)
    : width_bmp(width), length_bmp(length), color_bmp(std::vector<Color>( width*length )) {}

Color ImageSystem::getColor(uint16_t y, uint16_t x) {

  return color_bmp[y * width_bmp + x];
}
Color ImageSystem::getWhiteColor() {

  return kWhiteColor;
}
Color ImageSystem::getGreenColor() {

  return kGreenColor;
}
Color ImageSystem::getMagentaColor() {

  return kMagentaColor;
}
Color ImageSystem::getYellowColor() {

  return kYellowColor;
}
Color ImageSystem::getBlackColor() {

  return kBlackColor;
}

void ImageSystem::setColor(Color color, uint16_t y, uint16_t x) {
  color_bmp[y * width_bmp + x].red = color.red;
  color_bmp[y * width_bmp + x].green = color.green;
  color_bmp[y * width_bmp + x].blue = color.blue;

}

void ImageSystem::Export(std::string way) {
  std::ofstream file;
  file.open(way, std::ios::out | std::ios::binary);

  unsigned char bmp_pad[3] = {0, 0, 0};
  int padding_amount = ((4 - (width_bmp * 3) % 4) % 4); //посчет байтов отступов
  const int kHeaderSize = 14;
  const int kInformationHeader = 40;
  int FileSize = kHeaderSize + kInformationHeader + width_bmp * length_bmp * 3 + padding_amount * width_bmp;
  unsigned char FileHeader[kHeaderSize];

  FileHeader[0] = 'B';
  FileHeader[1] = 'M';
  FileHeader[2] = FileSize;
  FileHeader[3] = FileSize >> 8;
  FileHeader[4] = FileSize >> 16;
  FileHeader[5] = FileSize >> 24;
  FileHeader[6] = 0;
  FileHeader[7] = 0;
  FileHeader[8] = 0;
  FileHeader[9] = 0;
  FileHeader[10] = kHeaderSize + kInformationHeader;
  FileHeader[11] = 0;
  FileHeader[12] = 0;
  FileHeader[13] = 0;

  unsigned char information_header[kInformationHeader];

  information_header[0] = kInformationHeader;
  information_header[1] = 0;
  information_header[2] = 0;
  information_header[3] = 0;

  information_header[4] = width_bmp;
  information_header[5] = width_bmp >> 8;
  information_header[6] = width_bmp >> 16;
  information_header[7] = width_bmp >> 24;

  information_header[8] = length_bmp;
  information_header[9] = length_bmp >> 8;
  information_header[10] = length_bmp >> 16;
  information_header[11] = length_bmp >> 24;

  information_header[12] = 1;
  information_header[13] = 0;

  information_header[14] = 24;
  for (int i = 15; i < kSize; i++) {
    information_header[i] = 0;
  }

  file.write(reinterpret_cast<char*>(FileHeader), kHeaderSize);
  file.write(reinterpret_cast<char*>(information_header), kInformationHeader);

  for (int y = 0; y < width_bmp; y++) {
    for (int x = 0; x < length_bmp; x++) {
      unsigned char red = getColor(y, x).red;
      unsigned char green = getColor(y, x).green;
      unsigned char blue = getColor(y, x).blue;
      unsigned char color[] = {blue, green, red};

      file.write(reinterpret_cast<char*>(color), 3);
    }
    file.write(reinterpret_cast<char*>(bmp_pad), padding_amount);
  }
  file.close();

  std::cout << "BMP created\n";
}
