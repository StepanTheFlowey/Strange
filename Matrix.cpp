#include "Matrix.hpp"

void Matrix::create() {
  position_.y = rand() % (context->videoMode.height / 18) * 18;
  position_.x = rand() % (context->videoMode.width / 12) * 12;

  uint8_t color;
  for(uint_fast8_t i = 0; i < MATRIX_LENGHT; ++i) {
    sprite_[i].setTexture(*context->getTexture(ID_IMG2));
    color = 256 / MATRIX_LENGHT * i;
    sprite_[i].setColor(sf::Color(color, color, color));
    sprite_[i].setScale(2.0F, 2.0F);
  }
}

void Matrix::destroy() {

}

void Matrix::update() {
  moveTime_ += context->time;
  if(moveTime_.asMilliseconds() > speed) {
    moveTime_ -= sf::milliseconds(speed);
    position_.y += 18;

    if(position_.y > static_cast<int>(context->videoMode.height) + MATRIX_LENGHT * 18) {
      position_.y = -(MATRIX_LENGHT * 18);
      position_.x = rand() % (context->videoMode.width / 12) * 12;
    }
  }

  updateTime_ += context->time;
  if(updateTime_.asMilliseconds() > 100) {
    updateTime_ -= sf::milliseconds(100);
    for(uint_fast8_t i = 0; i < MATRIX_LENGHT; ++i) {
      sprite_[i].setTextureRect(sf::IntRect(rand() % 16 * 6, 0, 6, 9));
    }
  }

  for(uint_fast8_t i = 0; i < MATRIX_LENGHT; ++i) {
    sprite_[i].setPosition(sf::Vector2f(position_) + sf::Vector2f(0, i * 18));
  }
}

void Matrix::draw() {
  for(uint_fast8_t i = 0; i < MATRIX_LENGHT; ++i) {
    context->window.draw(sprite_[i]);
  }
}
