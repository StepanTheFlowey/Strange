#pragma once

#include <vector>
#include "Scene.hpp"
#include "Entity.hpp"

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