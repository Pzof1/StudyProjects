#ifndef LABWORK5_PZOF1_LIB_ARR17_H_
#define LABWORK5_PZOF1_LIB_ARR17_H_
#include <cinttypes>
#include <iostream>

class Array1D;
class Array2D;
class Array3D;

class uint17_t{
 private:
  uint8_t* first_byte_;
  uint8_t first_bit_;

 public:
  static const size_t bit_count_uint17_t_ = 17;

  uint17_t(uint8_t* first_byte, uint8_t first_bit);

  operator uint32_t() const;

  uint17_t& operator=(uint32_t value);
  uint17_t& operator=(uint17_t&& rhs);
  uint32_t GetValue() const;

  void SetValue(uint32_t value);
};

std::ostream& operator<<(std::ostream& os, const uint17_t& rhs);
std::istream& operator>>(std::istream& is, uint17_t&& rhs);

struct ArraySizes {
  size_t size_x_;
  size_t size_y_;
  size_t size_z_;
};

class Array1D {
 private:
  size_t x_;
  size_t y_;
  const Array3D& array_3d_;
 public:
  Array1D(const Array3D& array_3d, size_t x,size_t y);
  uint17_t operator[](size_t z) ;
};

class Array2D {
 private:
  const Array3D& array_3d;
  size_t x_;
 public:
  Array2D(const Array3D& array_3d, size_t x);
  Array1D operator[](size_t y) const;
};

class Array3D {
 private:
  uint8_t* array_;
  size_t size_x_;
  size_t size_y_;
  size_t size_z_;

 public:
  Array3D(size_t x, size_t y, size_t z);
  Array3D(const Array3D& rhs);
  static Array3D MakeArray(size_t x, size_t y, size_t z);

  ~Array3D();

  uint8_t* GetPointerToArray() const;
  ArraySizes GetSizes() const;
  uint17_t GetElement(size_t x, size_t y, size_t z) const;

  Array2D operator[](size_t x) const;
  Array3D& operator=(const Array3D& rhs);
  Array3D operator+(const Array3D& rhs) const;
  Array3D operator-(const Array3D& rhs) const;
  Array3D operator*(size_t rhs) const;
  Array3D operator/(size_t rhs) const;
  bool operator==(const Array3D& rhs) const;
  bool operator!=(const Array3D& rhs) const;
};

std::ostream& operator<<(std::ostream& os, const Array3D& rhs);
std::istream& operator>>(std::istream& is, const Array3D& rhs);

#endif //LABWORK5_PZOF1_LIB_ARR17_H_
