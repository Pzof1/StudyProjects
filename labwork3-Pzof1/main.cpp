#include "libraries/parser/parser.h"
#include "libraries/bmp/bmp.h"
#include "libraries/data-storage/data-storage.h"
#include "libraries/other-functions/other-functions.h"
#include <cinttypes>

int main(int argc, char *argv[]) {
  struct ProgramParameters Arguments;
  ParseArguments(argv, argc, Arguments);
  MyVector my_vector = ReadFromTSV(Arguments.input_path);
  StartModel(Arguments);
}