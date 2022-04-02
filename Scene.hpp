#pragma once

#include "Context.hpp"
#include "main.hpp"

class Scene {
public:

  Scene() {
    debug(L"Scene()");
  }

  ~Scene() {
    debug(L"~Scene()");
  }

  virtual void run();/*{
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
