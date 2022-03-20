#include "Exeption.hpp"

#include "main.hpp"
#include <sstream>

inline Exeption::Exeption(const std::wstring description, const std::string filename, const uint64_t line) {
  description_ = description;
  filename_ = wide(filename);
  line_ = line;
}

const std::wstring Exeption::wtf() const {
  std::wstringstream out;
  out << L"wtf():" << std::endl;
  out << L"Problem: " << description_ << std::endl;
  out << L"File: " << filename_ << std::endl;
  out << L"Line: " << line_ << std::endl;
  out << L"Please contact app vendor" << std::endl;
  return out.str();
}