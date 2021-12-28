#pragma once

#include "sceneBase.hpp"
#include "matrix.hpp"

#define MATRIX_COUNT 64

class SceneMatrix: public SceneBase {
  Matrix matrix_[MATRIX_COUNT];
public:

  SceneMatrix() {
#ifdef DEBUG
    std::wcout << L"SceneMatrix()" << std::endl;
#endif // DEBUG
  }

  ~SceneMatrix() {
#ifdef DEBUG
    std::wcout << L"~SceneMatrix()" << std::endl;
#endif // DEBUG
  }

  virtual void run(Context* context) override {
    for(uint8_t i = 0; i < MATRIX_COUNT; i++)
      matrix_[i].create(context);

    context->create();
    while(context->isOpen()) {
      context->autoClock();
      context->autoEvent();

      for(uint8_t i = 0; i < MATRIX_COUNT; i++)
        matrix_[i].update();

      context->window.clear(sf::Color(0, 0, 0, 128));
      for(uint8_t i = 0; i < MATRIX_COUNT; i++)
        matrix_[i].draw();
      context->window.display();
    }
  }
};