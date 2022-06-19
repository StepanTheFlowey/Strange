#include "Exeption.hpp"

#include "main.hpp"
#include <sstream>

Exeption::Exeption(const std::wstring description, const std::string filename, const uint64_t line) {
  description_ = description;
  filename_ = wide(filename);
  line_ = line;
}

const std::wstring Exeption::wtf() const {
  std::wstringstream out;
  
  out << L"wtf():\n";
  out << L"Problem:\t" << description_ << L'\n';
  out << L"File:\t" << filename_ << L'\n';
  out << L"Line:\t" << line_ << L'\n';
  out << L"Please contact app vendor" << std::endl;

  return out.str();
}
