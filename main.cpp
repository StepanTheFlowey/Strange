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

#ifdef DEBUG
int main() {
#else
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd) {
#endif // DEBUG
  srand(static_cast<unsigned int>(time(0)));
  int exitcode = 0;

  try {
    exitcode = secureMain();
  }
  catch(Exeption exeption) {
#ifdef DEBUG
    std::cerr << L"wtf(): " << exeption.wtf() << std::endl;
#else
    MessageBoxW(NULL, exeption.wtf().c_str(), L"Strange", MB_ICONERROR | MB_OK);
#endif // DEBUG
    exitcode = -1;
  }
  catch(...) {
#ifdef DEBUG
    std::cerr << "omg shit happens\a" << std::endl;
#else
    MessageBoxW(NULL, L"omg shit happens", L"Strange", MB_ICONERROR | MB_OK);
#endif // DEBUG
    exitcode = -1;
  }

#ifdef DEBUG
  _wsystem(L"pause");
#endif // DEBUG
  exit(exitcode);
}