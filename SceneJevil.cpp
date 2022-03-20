#include "SceneJevil.hpp"

#include "main.hpp"
#include "JevilDance.hpp"

inline SceneJevil::SceneJevil() {
  debug(L"SceneJevil()");
  jevils_.reserve(JEVIL_COUNT);
}

inline SceneJevil::~SceneJevil() {
  debug(L"~SceneJevil()");
}

inline void SceneJevil::run() {
  music_.setBuffer(context->getSound(IDR_WAVE1));
  music_.setLoop(true);
  music_.play();

  for(uint8_t i = 0; i < JEVIL_COUNT; ++i) {
    jevils_.push_back(new JevilDance);
    jevils_.back()->create(context);
  }

  while(context->isActual()) {
    context->autoClock();
    context->autoEvent();

    for(auto& i : jevils_)
      i->update();

    context->window.clear(sf::Color::Transparent);
    for(auto& i : jevils_)
      i->draw();
    context->window.display();
  }

  music_.resetBuffer();
  for(uint8_t i = 0; i < JEVIL_COUNT; i++)
    delete jevils_[i];
}