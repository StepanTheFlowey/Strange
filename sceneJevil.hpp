#pragma once

#include <vector>
#include "Scene.hpp"
#include "Entity.hpp"

#define JEVIL_COUNT 64

class SceneJevil : public Scene {
  sf::Sound music_;
  std::vector<Entity*> jevils_;
public:

  SceneJevil();

  ~SceneJevil();

  virtual void run(Context* const context) override;
};