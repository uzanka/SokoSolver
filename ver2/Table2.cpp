#include "Table2.h"

///////////////////////////////////////////////////////////////////////////////
Table2::Table2()
  : width_(0), height_(0), size_(0), data_(nullptr) {
}

///////////////////////////////////////////////////////////////////////////////
Table2::Table2(const int width, const int height, const int default_value)
  : width_(0), height_(0), size_(0), data_(nullptr) {
#ifdef _DEBUG
  if ((width <= 0 || width > std::numeric_limits<int8_t>::max())
   || (height <= 0 || height > std::numeric_limits<int8_t>::max())) {
    throw std::runtime_error("Range error.");
  }
#endif
  width_ = (int8_t)width;
  height_ = (int8_t)height;
  size_ = ((width_ * height_ * 2) + ((sizeof(uint8_t) * 8) - 1)) / (sizeof(uint8_t) * 8);
  data_ = new uint8_t[size_];
  //memset(data_, 0, size_);
  data_[size_ - 1] = 0;
  Clear(default_value);
}

///////////////////////////////////////////////////////////////////////////////
Table2::Table2(const Table2& tmp)
  : width_(0), height_(0), size_(0), data_(nullptr) {
  operator=(tmp);
}

///////////////////////////////////////////////////////////////////////////////
Table2::~Table2() {
  if (data_ != nullptr) {
    delete[] data_;
  }
}

///////////////////////////////////////////////////////////////////////////////
void Table2::Clear(const int value) {
/*
  for (int y = 0; y < height_; y++) {
    for (int x = 0; x < width_; x++) {
      Set(x, y, value);
    }
  }
*/
  uint8_t fill = (value << 6) | (value << 4) | (value << 2) | value;
  memset(data_, fill, size_);
}

///////////////////////////////////////////////////////////////////////////////
void Table2::Set(const int x, const int y, const int value) {
#ifdef _DEBUG
  if ((x < 0 || x >= width_)
   || (y < 0 || y >= height_)
   || (value < 0 || value > 3)) {
#ifdef _DEBUG
    throw std::runtime_error("Range error.");
#else
    return;
#endif
  }
#endif

  int index = ((y * width_ + x) * 2) / (sizeof(uint8_t) * 8);
  switch (((y * width_ + x) * 2) % (sizeof(uint8_t) * 8)) {
  case 0: data_[index] = (data_[index] & (~0x03)) | value;        break;
  case 2: data_[index] = (data_[index] & (~0x0C)) | (value << 2); break;
  case 4: data_[index] = (data_[index] & (~0x30)) | (value << 4); break;
  case 6: data_[index] = (data_[index] & (~0xC0)) | (value << 6); break;
  default: throw std::runtime_error("Range error.");
  }
}

///////////////////////////////////////////////////////////////////////////////
int Table2::Get(const int x, const int y, const int out_of_range_value) const {
  if ((x < 0 || x >= width_)
   || (y < 0 || y >= height_)) {
    return out_of_range_value;
  }

  int index = ((y * width_ + x) * 2) / (sizeof(uint8_t) * 8);
  switch (((y * width_ + x) * 2) % (sizeof(uint8_t) * 8)) {
  case 0: return (data_[index] & 0x03);
  case 2: return (data_[index] & 0x0C) >> 2;
  case 4: return (data_[index] & 0x30) >> 4;
  case 6: return (data_[index] & 0xC0) >> 6;
  default: throw std::runtime_error("Range error.");
  }
}

///////////////////////////////////////////////////////////////////////////////
int Table2::Width() const {
  return width_;
}

///////////////////////////////////////////////////////////////////////////////
int Table2::Height() const {
  return height_;
}

///////////////////////////////////////////////////////////////////////////////
void Table2::Replace(const int src, const int dst) {
  for (int y = 0; y < height_; y++) {
    for (int x = 0; x < width_; x++) {
      if (Get(x, y) == src) {
        Set(x, y, dst);
      }
    }
  }
}

///////////////////////////////////////////////////////////////////////////////
std::size_t Table2::Hash() const {
  std::size_t index = 32452843;
  for (int i = 0; i < size_; i++) {
    index = index * 37 + static_cast<uint8_t>(data_[i]);
  }
  return index;
}

///////////////////////////////////////////////////////////////////////////////
Table2& Table2::operator = (const Table2& tmp) {
  if (&tmp != this) {
    if (data_ != nullptr) {
      delete[] data_;
      data_ = nullptr;
    }
    width_ = tmp.width_;
    height_ = tmp.height_;
    size_ = ((width_ * height_ * 2) + ((sizeof(uint8_t) * 8) - 1)) / (sizeof(uint8_t) * 8);
    data_ = new uint8_t[size_];
    memcpy(data_, tmp.data_, size_);
  }
  return *this;
}

///////////////////////////////////////////////////////////////////////////////
bool Table2::Equal(const Table2& tmp) const {
#ifdef _DEBUG
  if (width_ != tmp.width_) return false;
  if (height_ != tmp.height_) return false;
#endif
/*
  for (int y = 0; y < height_; y++) {
    for (int x = 0; x < width_; x++) {
      if (Get(x, y) != tmp.Get(x, y)) {
        return false;
      }
    }
  }
  return true;
*/
  return memcmp(data_, tmp.data_, size_) == 0;
}
