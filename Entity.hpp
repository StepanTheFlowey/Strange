#pragma once

#include "main.hpp"
#include "Context.hpp"

class Entity {
public:

  inline Entity() {
    debug(L"Entity()");
  }

  inline virtual ~Entity() {
    debug(L"~Entity()");
  }

  inline virtual void create() {
    exept(L"Entity::create(context)!");
  }

  inline virtual void destroy() {
    exept(L"Entity::destroy()!");
  }

  inline virtual void update() {
    exept(L"Entity::update()!");
  }

  inline virtual void draw() {
    exept(L"Entity::draw()!");
  }
};
