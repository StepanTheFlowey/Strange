#pragma once

#include <vector>
#include "sceneBase.hpp"
#include "jevilDance.hpp"

#define JEVIL_COUNT 64

class SceneJevil : public SceneBase {
  sf::Sound music_;
  std::vector<JevilBase*> jevils_;
public:

  SceneJevil() {
#ifdef DEBUG
    std::wcout << L"SceneJevil()" << std::endl;
#endif // DEBUG
    jevils_.reserve(JEVIL_COUNT);
  }

  ~SceneJevil() {
#ifdef DEBUG
    std::wcout << L"~SceneJevil()" << std::endl;
#endif // DEBUG
  }

  virtual void run(Context* context) {
    music_.setBuffer(context->getAudio(IDR_WAVE1));
    music_.setLoop(true);
    music_.play();

    for(uint8_t i = 0; i < JEVIL_COUNT; i++) {
      jevils_.push_back(new JevilDance);
      jevils_.back()->create(context);
    }

    context->create();
    while(context->isOpen()) {
      context->autoClock();
      context->autoEvent();

      for(uint8_t i = 0; i < JEVIL_COUNT; i++)
        jevils_[i]->update();

      context->window.clear(sf::Color::Transparent);
      for(uint8_t i = 0; i < JEVIL_COUNT; i++)
        jevils_[i]->draw();
      context->window.display();
    }

    music_.resetBuffer();
    for(uint8_t i = 0; i < JEVIL_COUNT; i++)
      delete jevils_[i];
  }
};