#include "SceneMatrix.hpp"

void SceneMatrix::run() {
  for(uint8_t i = 0; i < MATRIX_COUNT; ++i)
    matrix_[i].create();

  context->create();
  while(context->alive()) {
    context->autoClock();

    for(uint8_t i = 0; i < MATRIX_COUNT; ++i)
      matrix_[i].update();

    context->window.clear(sf::Color(0, 0, 0, 128));
    for(uint8_t i = 0; i < MATRIX_COUNT; ++i)
      matrix_[i].draw();
    context->window.display();
    context->autoEvent();
  }
}
