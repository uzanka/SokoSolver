#include "Table8.h"

///////////////////////////////////////////////////////////////////////////////
Table8::Table8()
  : width_(0), height_(0), size_(0), data_(nullptr) {
}

///////////////////////////////////////////////////////////////////////////////
Table8::Table8(const int width, const int height, const int default_value)
  : width_(0), height_(0), size_(0), data_(nullptr) {
#ifdef _DEBUG
  if ((width <= 0 || width > std::numeric_limits<int8_t>::max())
   || (height <= 0 || height > std::numeric_limits<int8_t>::max())) {
    throw std::runtime_error("Range error.");
  }
#endif
  width_ = (int8_t)width;
  height_ = (int8_t)height;
  size_ = (int16_t)(width_ * height_);
  data_ = new int8_t[size_];
  //memset(data_, 0, size_);
  Clear(default_value);
}

///////////////////////////////////////////////////////////////////////////////
Table8::Table8(const Table8& tmp)
  : width_(0), height_(0), size_(0), data_(nullptr) {
  operator=(tmp);
}

///////////////////////////////////////////////////////////////////////////////
Table8::~Table8() {
  delete[] data_;
}

///////////////////////////////////////////////////////////////////////////////
void Table8::Clear(const int value) {
/*
  for (int y = 0; y < height_; y++) {
    for (int x = 0; x < width_; x++) {
      Set(x, y, value);
    }
  }
*/
  memset(data_, value, size_);
}

///////////////////////////////////////////////////////////////////////////////
void Table8::Set(const int x, const int y, const int value) {
//#ifdef _DEBUG
  if ((x < 0 || x >= width_)
   || (y < 0 || y >= height_)
   || (value < 0 || value > std::numeric_limits<int8_t>::max())) {
#ifdef _DEBUG
    throw std::runtime_error("Range error.");
#else
    return;
#endif
  }
//#endif

  data_[y * width_ + x] = value;
}

///////////////////////////////////////////////////////////////////////////////
int Table8::Get(const int x, const int y, const int out_of_range_value) const {
//#ifdef _DEBUG
  if ((x < 0 || x >= width_)
   || (y < 0 || y >= height_)) {
    return out_of_range_value;
  }
//#endif

  return data_[y * width_ + x];
}

///////////////////////////////////////////////////////////////////////////////
int Table8::Width() const {
  return width_;
}

///////////////////////////////////////////////////////////////////////////////
int Table8::Height() const {
  return height_;
}

///////////////////////////////////////////////////////////////////////////////
void Table8::Replace(const int src, const int dst) {
  for (int y = 0; y < height_; y++) {
    for (int x = 0; x < width_; x++) {
      if (Get(x, y) == src) {
        Set(x, y, dst);
      }
    }
  }
}

///////////////////////////////////////////////////////////////////////////////
std::size_t Table8::Hash() const {
  std::size_t index = 32452843;
  for (int i = 0; i < size_; i++) {
    index = index * 37 + static_cast<uint8_t>(data_[i]);
  }
  return index;
}

///////////////////////////////////////////////////////////////////////////////
Table8& Table8::operator = (const Table8& tmp) {
  if (&tmp != this) {
    width_ = tmp.width_;
    height_ = tmp.height_;
    if (data_ != nullptr) {
      delete[] data_;
      data_ = nullptr;
    }
    data_ = new int8_t[size_];
    memmove(data_, tmp.data_, size_);
  }
  return *this;
}

///////////////////////////////////////////////////////////////////////////////
bool Table8::Equal(const Table8& tmp) const {
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
