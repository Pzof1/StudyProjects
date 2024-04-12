#include "lib/Arr17.h"
#include "iostream"
#include <vector>

int main() {
  Array3D arr1 = Array3D::MakeArray(1, 1, 1);
  Array3D arr2 = Array3D::MakeArray(2, 1, 1);
  arr1[0][0][0] = 1;
  arr2[0][0][0] = 1;
  arr2[1][0][0] = 1;

  std::cout << arr1+arr2;
}