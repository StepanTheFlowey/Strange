#pragma once
#include "context.hpp"

class Scene {
public:

  Scene();

  ~Scene();

  virtual void run() = NULL;/*{
    Objects creation

    Loop begin

    Clock update
    Event update

    Update objects
    Draw objects

    Loop end

    Objects destroying
  }*/
};