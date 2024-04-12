//
// Created by Александр Коновалов on 23.10.2023.
//

#include "bmp.h"
void CreateBMP(char* output_path, MyVector my_vector, uint64_t** mas) {
  BITMAPFILEHEADER bmp_file_header;
  BITMAPINFOHEADER bmp_info_header;

  std::ofstream output_file(output_path, std::ios::out|std::ios::binary);
  if (!output_file.is_open())
    InputError();

  RGBQUAD Palette[16];
  //white
  Palette[0].rgbRed = 255;
  Palette[0].rgbGreen = 255;
  Palette[0].rgbBlue = 255;
  //green
  Palette[1].rgbRed = 0;
  Palette[1].rgbGreen = 255;
  Palette[1].rgbBlue = 0;
  //yellow
  Palette[2].rgbRed = 255;
  Palette[2].rgbGreen = 255;
  Palette[2].rgbBlue = 0;
  //violet
  Palette[3].rgbRed = 139;
  Palette[3].rgbGreen = 0;
  Palette[3].rgbBlue = 255;
  //black
  for(int i = 4; i < 16; i++) {
    Palette[4].rgbRed = 0;
    Palette[4].rgbGreen = 0;
    Palette[4].rgbBlue = 0;
  }


  bmp_file_header.bfType = 0x4D42;
  bmp_file_header.bfOffBits = sizeof(bmp_file_header) + sizeof(bmp_info_header) + sizeof(Palette);
  bmp_file_header.bfSize = bmp_file_header.bfOffBits +
      my_vector.width * my_vector.height/2 +
      my_vector.height * ((4 - (my_vector.width / 2) % 4) % 4);
  bmp_info_header.biSize = sizeof(bmp_info_header);
  bmp_info_header.biBitCount = 4;
  bmp_info_header.biHeight = my_vector.height;
  bmp_info_header.biWidth = my_vector.width;
  bmp_info_header.biPlanes = 1;

  output_file.write(reinterpret_cast <char*>(&bmp_file_header), sizeof(bmp_file_header));
  output_file.write(reinterpret_cast <char*>(&bmp_info_header), sizeof(bmp_info_header));
  output_file.write(reinterpret_cast <char*> (&Palette), sizeof(Palette));

  uint8_t byte_for_padding = 0;
  for (int i = my_vector.y_min; i <= my_vector.y_max; ++i) {//вывод перевернутый

    for (int j = my_vector.x_min; j <= my_vector.x_max; j+=2) {
      uint8_t byte_for_2_pix = ((mas[i-my_vector.y_min][j-my_vector.x_min] % 16) << 4 | mas[i - my_vector.y_min][j+1 - my_vector.x_min] % 16);
      output_file.write(reinterpret_cast <char*> (&byte_for_2_pix), sizeof(byte_for_2_pix));
    }
    for (int a = 0; a < ( (4-(my_vector.width/2)%4) %4); ++a) {
      output_file.write(reinterpret_cast <char*> (&byte_for_padding), sizeof(byte_for_padding));
    }
  }
  //все работает не трогай

  output_file.close();
}
