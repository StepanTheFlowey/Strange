#pragma once

#include <vector>
#include "Scene.hpp"
#include "Entity.hpp"

#define JEVIL_COUNT 64

class SceneJevil : public Scene {
  sf::Music* music_ = nullptr;
  std::vector<Entity*> jevils_;
public:

  inline SceneJevil() {
    debug(L"SceneJevil()");
    jevils_.reserve(JEVIL_COUNT);
  }

  inline ~SceneJevil() {
    debug(L"~SceneJevil()");
  }

  virtual void run() override;
};