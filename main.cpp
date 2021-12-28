#pragma once
#define WIN32_LEAN_AND_MEAN
#define NOMINMAX
#include <iostream>

#include "context.hpp"
#include "sceneJevil.hpp"
#include "sceneMatrix.hpp"

int secureMain() {
  Context* context = new Context;
  context->load();

  SceneBase* scene = nullptr;
  switch(rand() % 2) {
    case 0:
      scene = new SceneJevil;
      break;
    case 1:
      scene = new SceneMatrix;
      break;
  }
  scene->run(context);

  delete scene;
  delete context;
  return 0;
}

int main() {
  srand(static_cast<unsigned int>(time(0)));
#ifndef DEBUG
  FreeConsole();
#endif // DEBUG
  int exitcode = 0;

  try {
    exitcode = secureMain();
  }
  catch(Exeption exeption) {
#ifndef DEBUG
    AllocConsole();
#endif // DEBUG
    exeption.print();
    exitcode = -1;
  }
  catch(...) {
#ifndef DEBUG
    AllocConsole();
#endif // DEBUG
    std::cerr << "omg shit happens\a" << std::endl;
    exitcode = -1;
  }

#ifdef DEBUG
  _wsystem(L"pause");
#endif // DEBUG
  exit(exitcode);
}