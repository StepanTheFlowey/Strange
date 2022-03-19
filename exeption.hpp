#pragma once
#include <string>
#include <iostream>

class Exeption {
  std::wstring description_;
public:

  Exeption(const std::wstring wstr) {
    description_ = wstr;
  }

  const std::wstring wtf() const {
    return description_;
  }
};