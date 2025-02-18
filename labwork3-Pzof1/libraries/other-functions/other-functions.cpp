//
// Created by Александр Коновалов on 30.10.2023.
//

#include "other-functions.h"

char* ToString(int number) {
  int number1 = number;
  int8_t pow = 0;

  while(number1 > 0) {
    pow += 1;
    number1 /= 10;
  }
  char* result = new char[pow];
  pow -= 1;
  number1 = number;
  while(pow >= 0) {
    result[pow] = char((number1 % 10) + int('0'));
    --pow;
    number1 /= 10;
  }

  return result;
}

char* GetFileName(int iter) {
  char* number = ToString(iter);
  size_t size = strlen(number) + strlen(".bmp");
  char* result = new char[size];
  size_t i = 0;

  for(i; i < strlen(number); ++i){
    result[i] = number[i];
  }
  for(i; i < size; ++i) {
    result[i] = ".bmp"[i-strlen(number)];
  }
  //удали потом резулт когда рисуешь картинку
  delete number;
  return result;
}

uint64_t** ArrayConvert(uint64_t* mas, uint16_t width, uint16_t height) {
  auto new_mas = new uint64_t*[height];
  for(uint16_t i = 0;i <height; ++i) {
    new_mas[i] = new uint64_t[width];
  }
  uint32_t k = 0;
  for(uint16_t i = 0; i < height; ++i) {
    for(uint16_t j = 0; j < width; ++j) {
      new_mas[i][j] = mas[k];
      ++k;
    }
  }
  return new_mas;
}

void StartModel(ProgramParameters &Arguments) {
  MyVector my_vector = ReadFromTSV(Arguments.input_path);
  Queue queue = my_vector.GetQueue();

  uint64_t counter_iter = 0;
  uint64_t bmp_counter = 1;

  if(Arguments.max_iterations == 0 or Arguments.freq == 0) {
    while(!queue.IsEmpty()) {
      queue = my_vector.NextQueue(queue);
    }
    CreateBMP(strcat(Arguments.output_path, "1.bmp"), my_vector, ArrayConvert(my_vector.mas,my_vector.width, my_vector.height));
  } else {
    while(!queue.IsEmpty() and counter_iter < Arguments.max_iterations) {
      queue = my_vector.NextQueue(queue);
      if(counter_iter % Arguments.freq == 0) {
        char* temp = new char[200];
        strcpy(temp,Arguments.output_path);
        strcat(temp, GetFileName(counter_iter/Arguments.freq));
        CreateBMP(temp, my_vector, ArrayConvert(my_vector.mas, my_vector.width,my_vector.height));
      }
      counter_iter++;
      bmp_counter++;
    }
    if(counter_iter >= Arguments.max_iterations) {
      while(!queue.IsEmpty()) {
        queue = my_vector.NextQueue(queue);
      }
      counter_iter++;
      char* temp = new char[200];
      strcpy(temp,Arguments.output_path);
      strcat(temp, GetFileName(counter_iter/Arguments.freq));
      CreateBMP(temp, my_vector, ArrayConvert(my_vector.mas, my_vector.width,my_vector.height));
    }

  }
}