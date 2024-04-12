#include <lib/Arr17.h>
#include <gtest/gtest.h>
#include <sstream>
#include <iostream>

TEST(Arr17TestSuite, GetUint17_t_1) {
  Array3D arr = Array3D::MakeArray(5, 2, 11);
  arr[0][0][0] = (1<<17);
  arr[0][0][0] = arr[0][0][0] - 1;
  int first_byte = arr.GetPointerToArray()[0];
  int second_byte = arr.GetPointerToArray()[1];
  int third_byte = arr.GetPointerToArray()[2];

  ASSERT_EQ(first_byte, 255);
  ASSERT_EQ(second_byte, 255);
  ASSERT_EQ(third_byte, 1);
}

TEST(Arr17TestSuite, GetUint17_t_2) {
  Array3D arr = Array3D::MakeArray(1, 1, 1);
  arr[0][0][0] = (1<<17);

  ASSERT_EQ(arr[0][0][0], 0);
}

TEST(Arr17TestSuite, GetUint17_t_3) {
  Array3D arr = Array3D::MakeArray(2, 1, 1);
  arr[0][0][0] = 1;
  arr[1][0][0] = (1 << 17);
  ASSERT_EQ(arr[0][0][0], 1);
  ASSERT_EQ(arr[1][0][0], 0);
}

TEST(Arr17TestSuite, SumTest) {
  Array3D arr1 = Array3D::MakeArray(2, 1, 2);
  Array3D arr2 = Array3D::MakeArray(2, 1, 2);
  Array3D arr3 = Array3D::MakeArray(2, 1, 2);

  for(uint8_t x = 0; x < 2; ++x)
    for(uint8_t y = 0; y < 1; ++y)
      for(uint8_t z = 0; z < 2; ++z)
        arr1[x][y][z] = 5;

  for(uint8_t x = 0; x < 2; ++x)
    for(uint8_t y = 0; y < 1; ++y)
      for(uint8_t z = 0; z < 2; ++z)
        arr2[x][y][z] = 10;

  for(uint8_t x = 0; x < 2; ++x)
    for(uint8_t y = 0; y < 1; ++y)
      for(uint8_t z = 0; z < 2; ++z)
        arr3[x][y][z] = 15;

  ASSERT_EQ(arr1+arr2, arr3);
}

TEST(Arr17TestSuite, DiffTest) {
  Array3D arr1 = Array3D::MakeArray(2, 1, 2);
  Array3D arr2 = Array3D::MakeArray(2, 1, 2);
  Array3D arr3 = Array3D::MakeArray(2, 1, 2);

  for(uint8_t x = 0; x < 2; ++x)
    for(uint8_t y = 0; y < 1; ++y)
      for(uint8_t z = 0; z < 2; ++z)
        arr1[x][y][z] = 10;

  for(uint8_t x = 0; x < 2; ++x)
    for(uint8_t y = 0; y < 1; ++y)
      for(uint8_t z = 0; z < 2; ++z)
        arr2[x][y][z] = 5;

  for(uint8_t x = 0; x < 2; ++x)
    for(uint8_t y = 0; y < 1; ++y)
      for(uint8_t z = 0; z < 2; ++z)
        arr3[x][y][z] = 5;

  ASSERT_EQ(arr1-arr2, arr3);
}

TEST(Arr17TestSuite, MultTest) {
  Array3D arr1 = Array3D::MakeArray(2, 1, 2);
  Array3D arr2 = Array3D::MakeArray(2, 1, 2);

  for(uint8_t x = 0; x < 2; ++x)
    for(uint8_t y = 0; y < 1; ++y)
      for(uint8_t z = 0; z < 2; ++z)
        arr1[x][y][z] = 5;

  for(uint8_t x = 0; x < 2; ++x)
    for(uint8_t y = 0; y < 1; ++y)
      for(uint8_t z = 0; z < 2; ++z)
        arr2[x][y][z] = 50;

  ASSERT_EQ(arr1*10, arr2);
}

TEST(Arr17TestSuite, DivTest) {
  Array3D arr1 = Array3D::MakeArray(2, 1, 2);
  Array3D arr2 = Array3D::MakeArray(2, 1, 2);

  for(uint8_t x = 0; x < 2; ++x)
    for(uint8_t y = 0; y < 1; ++y)
      for(uint8_t z = 0; z < 2; ++z)
        arr1[x][y][z] = 500;

  for(uint8_t x = 0; x < 2; ++x)
    for(uint8_t y = 0; y < 1; ++y)
      for(uint8_t z = 0; z < 2; ++z)
        arr2[x][y][z] = 50;

  ASSERT_EQ(arr1/10, arr2);
}

TEST(Arr17TestSuite, Uint17_tIstreamTest) {
  Array3D arr1 = Array3D::MakeArray(2, 1, 2);
  std::string st = "0 131071 131072 1";
  std::stringstream ss;
  ss << st;

  for(uint8_t x = 0; x < 2; ++x)
    for(uint8_t y = 0; y < 1; ++y)
      for(uint8_t z = 0; z < 2; ++z)
        ss >> arr1[x][y][z];

  ASSERT_EQ(arr1[0][0][0], 0);
  ASSERT_EQ(arr1[0][0][1], 131071);
  ASSERT_EQ(arr1[1][0][0], 0);
  ASSERT_EQ(arr1[1][0][1], 1);
}

TEST(Arr17TestSuite, Uint17_tOstreamTest) {
  Array3D arr1 = Array3D::MakeArray(2, 1, 2);
  std::string st = "0 131071 0 1 ";
  std::stringstream ss;

  arr1[0][0][0] = 0;
  arr1[0][0][1] = (1 << 17) - 1;
  arr1[1][0][0] = (1 << 17);
  arr1[1][0][1] = 1;

  for(uint8_t x = 0; x < 2; ++x)
    for(uint8_t y = 0; y < 1; ++y)
      for(uint8_t z = 0; z < 2; ++z)
        ss << arr1[x][y][z] << " ";

  std::cout << ss.str();
  ASSERT_EQ(ss.str(), st);
}

TEST(Arr17TestSuit, CopyTest) {
  Array3D arr1 = Array3D::MakeArray(2, 1, 2);
  arr1[0][0][0] = 0;
  arr1[0][0][1] = (1 << 17) - 1;
  arr1[1][0][0] = (1 << 17);
  arr1[1][0][1] = 1;

  Array3D arr1_copy = arr1;
  arr1_copy[0][0][1] = 1337;
  arr1_copy[1][0][1] = 11;

  ASSERT_EQ(arr1[0][0][0], 0);
  ASSERT_EQ(arr1[0][0][1], 131071);
  ASSERT_EQ(arr1[1][0][0], 0);
  ASSERT_EQ(arr1[1][0][1], 1);
}

TEST(Arr17TestSuit, IndexOutOfRangeTest1) {
  Array3D arr1 = Array3D::MakeArray(1, 1, 1);
  arr1[0][0][0] = 1;

  ASSERT_THROW(arr1[0][0][1], std::range_error);
}

TEST(Arr17TestSuit, DifferentSizesTest) {
  Array3D arr1 = Array3D::MakeArray(1, 1, 1);
  Array3D arr2 = Array3D::MakeArray(2, 1, 1);
  arr1[0][0][0] = 1;
  arr2[0][0][0] = 1;
  arr2[1][0][0] = 1;

  ASSERT_THROW(arr1+arr2, std::range_error);
  ASSERT_THROW(arr1-arr2, std::range_error);
}