#pragma once

#include "Scene.hpp"
#include "Matrix.hpp"

#define MATRIX_COUNT 64

class SceneMatrix : public Scene {
  Matrix matrix_[MATRIX_COUNT];
public:

  SceneMatrix() {
    debug(L"SceneMatrix()");
  }

  ~SceneMatrix() {
    debug(L"~SceneMatrix()");
  }

  virtual void run() override;
};