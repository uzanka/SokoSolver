﻿#include "TableS.h"

///////////////////////////////////////////////////////////////////////////////
TableS::TableS() {
}

///////////////////////////////////////////////////////////////////////////////
TableS::TableS(const int width, const int height, const int default_value) {
  data_ = (char)width;
  data_ += (char)height;
  data_ += std::string(width * height, (char)default_value);
}

///////////////////////////////////////////////////////////////////////////////
TableS::~TableS() {
}

///////////////////////////////////////////////////////////////////////////////
void TableS::Clear(const int value) {
  for (int i = 2; i < data_.size(); i++) {
    data_[i] = value;
  }
}

///////////////////////////////////////////////////////////////////////////////
void TableS::Set(const int x, const int y, const int value) {
  data_[2 + y * Width() + x] = value;
}

///////////////////////////////////////////////////////////////////////////////
int TableS::Get(const int x, const int y, const int out_of_range_value) const {
  return data_[2 + y * Width() + x];
}

///////////////////////////////////////////////////////////////////////////////
int TableS::Width() const {
  return (int)data_[0];
}

///////////////////////////////////////////////////////////////////////////////
int TableS::Height() const {
  return (int)data_[1];
}

///////////////////////////////////////////////////////////////////////////////
void TableS::Replace(const int src, const int dst) {
  for (int i = 2; i < data_.size(); i++) {
    if (data_[i] == src) {
      data_[i] = dst;
    }
  }
}

///////////////////////////////////////////////////////////////////////////////
std::size_t TableS::Hash() const {
  std::size_t index = 32452843;
  for (int i = 2; i < data_.size(); i++) {
    index = index * 37 + static_cast<uint8_t>(data_[i]);
  }
  return index;
}
