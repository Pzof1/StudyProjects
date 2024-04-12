#ifndef LABWORK3_PZOF1_LIBRARIES_BMP_BMP_H
#define LABWORK3_PZOF1_LIBRARIES_BMP_BMP_H

#include <cinttypes>
#include <cstring>
#include <fstream>
#include "../parser/parser.h"
#include "../data-storage/data-storage.h"

#pragma pack(push, 1)
struct BITMAPFILEHEADER {
  uint16_t bfType = 0x4D12;
  uint32_t bfSize = 0;
  uint16_t bfReserved1 = 0;
  uint16_t bfReserved2 = 0;
  uint32_t bfOffBits = 0;
};
#pragma pack(pop)

struct BITMAPINFOHEADER {
  uint32_t biSize = 0;
  int32_t biWidth = 0;
  int32_t biHeight = 0;
  uint16_t biPlanes = 0;
  uint16_t biBitCount = 0;
  uint32_t biCompression = 0;
  uint32_t biSizeImage = 0;
  int32_t biXPelsPerMeter = 0;
  int32_t biYPelsPerMeter = 0;
  uint32_t biClrUsed = 0;
  uint32_t biClrImportant = 0;
} ;

struct RGBQUAD {
  uint8_t rgbBlue = 0;
  uint8_t rgbGreen = 0;
  uint8_t rgbRed = 0;
  uint8_t rgbReserved = 0;
};

void CreateBMP(char* output_path, MyVector my_vector, uint64_t** mas);

#endif LABWORK3_PZOF1_LIBRARIES_BMP_BMP_H
