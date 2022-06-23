#pragma once

#include "main.hpp"
#include "Context.hpp"

class Entity {
public:

  Entity() {
    debug(L"Entity()");
  }

  virtual ~Entity() {
    debug(L"~Entity()");
  }

  virtual void create() = 0;

  virtual void destroy() = 0;

  virtual void update() = 0;

  virtual void draw() = 0;
};
