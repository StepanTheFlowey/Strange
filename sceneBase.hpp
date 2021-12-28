#pragma once
#include "context.hpp"

class SceneBase {
public:

  SceneBase() {
#ifdef DEBUG
    std::wcout << L"SceneBase()" << std::endl;
#endif // DEBUG
  }

  ~SceneBase() {
#ifdef DEBUG
    std::wcout << L"~SceneBase()" << std::endl;
#endif // DEBUG
  }

  virtual void run(Context* context) = NULL;/*{
    Objects creation
    Context creation (only if first scene)

    Loop begin

    Clock update
    Event update

    Update objects
    Draw object

    Loop end

    Context destroying (or next scene begin)
    Objects destroying
  }*/
};