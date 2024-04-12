#ifndef LABWORK3_PZOF1_LIBRARIES_OTHER_FUNCTIONS_OTHER_FUNCTIONS_H_
#define LABWORK3_PZOF1_LIBRARIES_OTHER_FUNCTIONS_OTHER_FUNCTIONS_H_

#include <cinttypes>
#include <cstring>
#include <iostream>
#include "../data-storage/data-storage.h"
#include "../parser/parser.h"
#include "../bmp/bmp.h"

char* GetFileName(int iter);
uint64_t** ArrayConvert(uint64_t* mas, uint16_t width, uint16_t height);
char* ToString(int number);
void StartModel(ProgramParameters &Arguments);

#endif //LABWORK3_PZOF1_LIBRARIES_OTHER_FUNCTIONS_OTHER_FUNCTIONS_H_
