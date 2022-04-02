#pragma once

#include "Entity.hpp"

class JevilDance : public Entity {
  sf::Sprite sprite_;
  sf::Time time_;
  float moveSpeed_;
  int16_t moveDir_;
  uint8_t phase_;
  bool side_;
public:

  JevilDance();

  ~JevilDance();

  virtual void create() override;

  virtual void update() override;

  virtual void draw() override;
};
