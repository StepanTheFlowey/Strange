#pragma once
#include <string>
#include <iostream>

class Exeption {
  std::wstring description_;
public:

  Exeption(std::wstring wstr) {
    description_ = wstr;
  }

  void print() const {
    std::wcerr << "OH NO WARNING ERROR STH BAD HAPPENS SOS PLEASE REINSTALL YOUR SYSTEM" << std::endl;
    std::wcerr << "BECAUSE EXEPTION (OH MY GOD) WAS THROWN WITH NEXT DESCRIPTION:" << std::endl;
    std::wcerr << description_ << std::endl;
    std::wcerr << "OMG WE ALL WILL BE DIE AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA\a" << std::endl;
  }
};