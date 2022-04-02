#pragma once

#include "main.hpp"
#include "Context.hpp"

class Entity {
public:

  inline Entity() {
    debug(L"Entity()");
  }

  virtual inline ~Entity() {
    debug(L"~Entity()");
  }

  virtual inline void create() {
    exept(L"Entity::create(context)!");
  }

  virtual inline void destroy() {
    exept(L"Entity::destroy()!");
  }

  virtual inline void update() {
    exept(L"Entity::update()!");
  }

  virtual inline void draw() {
    exept(L"Entity::draw()!");
  }
};
