#pragma once
#include "context.hpp"

class JevilBase {
protected:
  Context* context_ = nullptr;
  sf::Sprite sprite_;
public:

  JevilBase() {
#ifdef DEBUG
    std::wcout << L"JevilBase()" << std::endl;
#endif // DEBUG
  }

  ~JevilBase() {
#ifdef DEBUG
    std::wcout << L"~JevilBase()" << std::endl;
#endif // DEBUG
  }

  virtual void create(Context*) = NULL;

  virtual void update() = NULL;

  virtual void draw() = NULL;
};