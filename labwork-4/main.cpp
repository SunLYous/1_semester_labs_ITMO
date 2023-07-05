#include "ParserSystem.h"
#include "ArchiveSystem.h"

int main(int argc, char* argv[]) {
  ParsingSystem parser = ParsingSystem(argc, argv);
  ArchiveSystem create_archive = ArchiveSystem(
      parser.getArhcnameSave(),
      parser.getFileExtract(),
      parser.getarhcnameOneMerge(),
      parser.getArhcnameTwoMerge(),
      parser.getOutputArhcFile(),
      parser.getFileDelete(),
      parser.getFlagExtract(),
      parser.getFlagDelete(),
      parser.getFlagMerge(),
      parser.getFlagCreate(),
      parser.getFileNames(),
      parser.getFlagList(),
      parser.getBitSize(),
      parser.getFlagAppend(),
      parser.getFileAppend()
  );
  return 0;
}