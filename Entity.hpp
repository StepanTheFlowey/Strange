#pragma once

#include "Context.hpp"

class Entity {
public:

  Entity();

  ~Entity();

  virtual void create(Context* const context);

  virtual void destroy();

  virtual void update();

  virtual void draw();
};