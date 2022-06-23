#pragma once

#include "Context.hpp"
#include "Entity.hpp"

class Matrix : public Entity {
  sf::Sprite sprite_[MATRIX_LENGHT];
  sf::Time moveTime_;
  sf::Time updateTime_;
  sf::Vector2i position_;
  uint16_t speed;
public:

  inline Matrix() {
    debug(L"Matrix()");
    speed = 30 + rand() % 40;
  }

  inline ~Matrix() {
    debug(L"~Matrix()");
  }

  virtual void create() override;

  virtual void destroy() override;

  virtual void update() override;

  virtual void draw() override;
};
