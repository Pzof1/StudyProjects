#ifndef LABWORK3_PZOF1_LIBRARIES_DATA_STORAGE_DATA_STORAGE_H_
#define LABWORK3_PZOF1_LIBRARIES_DATA_STORAGE_DATA_STORAGE_H_

#include <iostream>
#include <fstream>
#include <cinttypes>
#include "../parser/parser.h"

struct Node {
  uint64_t value;
  int16_t x;
  int16_t y;
  Node* next;

  Node(uint64_t _val, int16_t _y, int16_t _x) {
    value = _val;
    x = _x;
    y = _y;
    next = nullptr;
  }
};

struct Queue {
  Node* head;
  Node* tail;

  Queue() {
    head = nullptr;
    tail = nullptr;
  }

  void Push(uint64_t value, int16_t y , int16_t x);

  void Pop();

  Node* GetNode();

  bool IsEmpty();

  void Print();
};


struct MyVector {
  uint64_t* mas;
  uint16_t height;
  uint16_t width;
  uint32_t size;
  int16_t x_max = INT16_MIN;
  int16_t x_min = INT16_MAX;
  int16_t y_max = INT16_MIN;
  int16_t y_min = INT16_MAX;

  void AddToBottom();

  void AddToTop();

  void AddToRight();

  void AddToLeft();

  Queue GetQueue();

  Queue NextQueue(Queue &prev_queue);

  void CheckExtension(Node* cell);
};

MyVector ReadFromTSV(const char* path);




#endif //LABWORK3_PZOF1_LIBRARIES_DATA_STORAGE_DATA_STORAGE_H_
