#include "ParsingSystem.h"
#include "ScatteringSystem.h"
#include "ImageSystem.h"

int main(int argc, char* argv[]) {
  ParsingSystem parser = ParsingSystem(argc, argv);
  ScatteringSystem scattering = ScatteringSystem(parser.getDigitLength(),
                                                 parser.getDigitWidth(),
                                                 parser.getNumberOfIterations(),
                                                 parser.getPicture(),
                                                 parser.getSaveFrequency(),
                                                 parser.getPathToTheDirectory());
  ImageSystem image(parser.getDigitLength(), parser.getDigitWidth());

  return 0;
}