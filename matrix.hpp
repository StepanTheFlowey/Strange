#pragma once

#include "Context.hpp"

#define MATRIX_LENGHT 32

class Matrix {
  Context* context_=nullptr;
  sf::Sprite sprite_[MATRIX_LENGHT];
  sf::Time moveTime_;
  sf::Time updateTime_;
  sf::Vector2i position_;
  uint16_t speed;
public:

  Matrix() {
#ifdef DEBUG
    std::wcout << L"Matrix()" << std::endl;
#endif // DEBUG
    speed = 30 + rand() % 40;
  }

  ~Matrix() {
#ifdef DEBUG
    std::wcout << L"~Matrix()" << std::endl;
#endif // DEBUG
  }

  void create(Context* context) {
    context_ = context;

    position_.y = rand() % (context_->videoMode.height / 18) * 18;
    position_.x = rand() % (context_->videoMode.width / 12) * 12;

    uint8_t color;
    for(uint8_t i = 0; i < MATRIX_LENGHT; i++) {
      sprite_[i].setTexture(context_->getTexture(IDB_PNG2));
      color = 256 / MATRIX_LENGHT * i;
      sprite_[i].setColor(sf::Color(color, color, color));
      sprite_[i].setScale(2.0F, 2.0F);
    }
  }

  void update() {
    moveTime_ += context_->time;
    if(moveTime_.asMilliseconds() > speed) {
      moveTime_ -= sf::milliseconds(speed);
      position_.y += 18;

      if(position_.y > static_cast<int>(context_->videoMode.height) + MATRIX_LENGHT * 18) {
        position_.y = -(MATRIX_LENGHT * 18);
        position_.x = rand() % (context_->videoMode.width / 12) * 12;
      }
    }

    updateTime_ += context_->time;
    if(updateTime_.asMilliseconds() > 100) {
      updateTime_ -= sf::milliseconds(100);
      for(uint8_t i = 0; i < MATRIX_LENGHT; i++)
        sprite_[i].setTextureRect(sf::IntRect(rand() % 16 * 6, 0, 6, 9));
    }

    for(uint8_t i = 0; i < MATRIX_LENGHT; i++)
      sprite_[i].setPosition(sf::Vector2f(position_) + sf::Vector2f(0, i * 18));
  }

  void draw() {
    for(uint8_t i = 0; i < MATRIX_LENGHT; i++)
      context_->window.draw(sprite_[i]);
  }
};