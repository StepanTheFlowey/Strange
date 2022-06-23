#pragma once

#include <string>

class Config {
public:
  struct Entry {
    std::string name;
    std::string value;
    bool write = false;
  };

  Config() = default;

  ~Config() = default;

  void load();

  void save();
};
extern Config* config;
