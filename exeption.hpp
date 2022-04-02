#pragma once
#include <string>
#include <iostream>

class Exeption {
  uint64_t line_;
  std::wstring filename_;
  std::wstring description_;
public:

  //
  Exeption(const std::wstring description,const std::string filename,const uint64_t line);

  //
  const std::wstring wtf() const;
};
