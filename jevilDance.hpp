#pragma once

#include "Entity.hpp"

class EntityJevil : public Entity {
  sf::Sprite sprite_;
  sf::Time time_;
  float moveSpeed_;
  int16_t moveDir_;
  uint8_t phase_;
  bool side_;
public:

  EntityJevil();

  ~EntityJevil();

  virtual void create() override;

  virtual void destroy() override;

  virtual void update() override;

  virtual void draw() override;
};
