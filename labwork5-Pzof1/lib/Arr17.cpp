#include "Arr17.h"

//uint17_t
uint17_t::uint17_t(uint8_t* first_byte, uint8_t first_bit)
  : first_byte_{first_byte}
  , first_bit_{first_bit} {}

uint17_t::operator uint32_t() const {
  return GetValue();
}
uint32_t uint17_t::GetValue() const {
  uint32_t result = 0;
  uint8_t* byte = first_byte_;
  uint8_t bit = first_bit_;

  for (int i = 0; i < uint17_t::bit_count_uint17_t_; ++i) {
    result |= ((*byte >> bit) & 1) << i;

    ++bit;
    if (bit == 8) {
      ++byte;
      bit = 0;
    }
  }

  return result;
}
void uint17_t::SetValue(uint32_t value) {
  uint8_t* byte = first_byte_;
  uint8_t bit = first_bit_;
  for (int i = 0; i < bit_count_uint17_t_; ++i) {
    *byte &= ~(1 << (bit));
    *byte |= ((value >> i) & 1) << bit;

    ++bit;
    if (bit%8 == 0) {
      ++byte;
      bit = 0;
    }
  }
}

uint17_t& uint17_t::operator=(uint32_t value) {
  SetValue(value);

  return *this;
}

uint17_t& uint17_t::operator=(uint17_t&& rhs) {
  SetValue(rhs.GetValue());

  return *this;
}
std::istream& operator>>(std::istream& is, uint17_t&& rhs) {
  uint32_t value;
  is >> value;
  rhs.SetValue(value);

  return is;
}
std::ostream& operator<<(std::ostream& os, const uint17_t& rhs) {
  os << rhs.GetValue();

  return os;
}

//Array3D

Array3D Array3D::MakeArray(size_t x, size_t y, size_t z) {
  return {x, y, z};
}

Array3D::Array3D(size_t x, size_t y, size_t z)
  : size_x_(x)
  , size_y_(y)
  , size_z_(z)
  , array_(new uint8_t[(x * y * z * uint17_t::bit_count_uint17_t_) / 8 + 1]) {}
Array3D::~Array3D() {
  delete[] array_;
}

Array3D::Array3D(const Array3D& rhs) {
  size_x_ = rhs.size_x_;
  size_y_ = rhs.size_y_;
  size_z_ = rhs.size_z_;
  u_int64_t size = (size_x_ * size_y_ * size_z_ * uint17_t::bit_count_uint17_t_) / 8 + 1;
  array_ = new uint8_t[size];

  for(size_t i = 0; i < size; ++i) {
    array_[i] = rhs.array_[i];
  }
}

Array2D Array3D::operator[](size_t x) const{
  return {(*this), x};
}
Array3D& Array3D::operator=(const Array3D& rhs) {
  if (this == &rhs) {
    return *this;
  }

  size_x_ = rhs.size_x_;
  size_y_ = rhs.size_y_;
  size_z_ = rhs.size_z_;
  delete[] array_;
  u_int64_t size = (size_x_ * size_y_ * size_z_ * uint17_t::bit_count_uint17_t_) / 8 + 1;
  array_ = new uint8_t[size];

  for(size_t i = 0; i < size; ++i) {
    array_[i] = rhs.array_[i];
  }

  return *this;
}
Array3D Array3D::operator+(const Array3D& rhs) const {
  if(size_x_ != rhs.size_x_ or size_y_ != rhs.size_y_ or size_z_ != rhs.size_z_) {
    throw std::range_error("Array sizes are not equal");
  }

  Array3D result{size_x_, size_y_, size_z_};

  for(size_t x = 0; x < size_x_; ++x)
    for(size_t y = 0; y < size_y_; ++y)
      for(size_t z = 0; z < size_z_; ++z)
        result[x][y][z] = ((*this)[x][y][z] + rhs[x][y][z]);

  return result;
}
Array3D Array3D::operator-(const Array3D& rhs) const {
  if(size_x_ != rhs.size_x_ or size_y_ != rhs.size_y_ or size_z_ != rhs.size_z_) {
    throw std::range_error("Array sizes are not equal");
  }

  Array3D result = *this;

  for(size_t x = 0; x < size_x_; ++x)
    for(size_t y = 0; y < size_y_; ++y)
      for(size_t z = 0; z < size_z_; ++z)
        result[x][y][z] = result[x][y][z] -rhs[x][y][z];

  return result;
}
Array3D Array3D::operator*(size_t rhs) const {
  Array3D result{size_x_, size_y_, size_z_};

  for(size_t x = 0; x < size_x_; ++x)
    for(size_t y = 0; y < size_y_; ++y)
      for(size_t z = 0; z < size_z_; ++z)
        result[x][y][z] = (uint32_t((*this)[x][y][z]) * rhs);

  return result;
}
Array3D Array3D::operator/(size_t rhs) const {
  Array3D result{size_x_, size_y_, size_z_};

  for(size_t x = 0; x < size_x_; ++x)
    for(size_t y = 0; y < size_y_; ++y)
      for(size_t z = 0; z < size_z_; ++z)
        result[x][y][z] = (uint32_t((*this)[x][y][z]) / rhs);

  return result;
}
bool Array3D::operator!=(const Array3D &rhs) const {
  return !(*this == rhs);
}
bool Array3D::operator==(const Array3D& rhs) const{
  for(size_t x = 0; x < size_x_; ++x)
    for(size_t y = 0; y < size_y_; ++y)
      for(size_t z = 0; z < size_z_; ++z)
        if((*this)[x][y][z] != rhs[x][y][z])
          return false;
  return true;
}

std::ostream& operator<<(std::ostream &os, const Array3D& rhs) {
  ArraySizes sizes = rhs.GetSizes();
  for (size_t x = 0; x < sizes.size_x_; ++x)
    for (size_t y = 0; y < sizes.size_y_; ++y)
      for (size_t z = 0; z < sizes.size_z_; ++z)
        os << rhs[x][y][z] << " ";

  return os;
}
std::istream& operator>>(std::istream &is, const Array3D& rhs) {
  ArraySizes sizes = rhs.GetSizes();
  for (size_t x = 0; x < sizes.size_x_; ++x)
    for (size_t y = 0; y < sizes.size_y_; ++y)
      for (size_t z = 0; z < sizes.size_z_; ++z)
        is >> rhs[x][y][z];

  return is;
}

//Array2D
Array2D::Array2D(const Array3D& array_3d, size_t x)
  : array_3d{array_3d}
  , x_{x} {}

Array1D Array2D::operator[](size_t y) const{
  return {array_3d, x_, y};
}

//Array1D
Array1D::Array1D(const Array3D& array_3d, size_t x, size_t y)
  : array_3d_{array_3d}
  , x_{x}, y_{y} {}

uint17_t Array1D::operator[](size_t z) {
  return array_3d_.GetElement(x_,y_,z);
}

//Other functions
uint8_t* Array3D::GetPointerToArray() const{
  return array_;
}
ArraySizes Array3D::GetSizes() const {
  return {size_x_, size_y_, size_z_};
}
uint17_t Array3D::GetElement(size_t x, size_t y, size_t z) const {
  if(x >= size_x_ or y >= size_y_ or z >= size_z_ or x < 0 or y < 0 or z < 0) {
    throw std::range_error("Index out of range");
  }

  size_t index = size_x_*size_y_*z + y*size_x_ + x;

  size_t first_byte = (index * uint17_t::bit_count_uint17_t_) / 8;
  uint8_t first_bit = (index * uint17_t::bit_count_uint17_t_) % 8;

  return {(array_+first_byte), first_bit};
}

