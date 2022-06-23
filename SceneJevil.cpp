#include "SceneJevil.hpp"

#include "JevilDance.hpp"

void SceneJevil::run() {
  music_ = context->getMusic(ID_MUS1);
  music_->setLoop(true);
  music_->play();

  for(uint_fast8_t i = 0; i < JEVIL_COUNT; ++i) {
    jevils_.push_back(new EntityJevil);
    jevils_.back()->create();
  }

  while(context->alive()) {
    context->autoClock();

    for(auto& i : jevils_) {
      i->update();
    }

    context->window.clear(sf::Color::Transparent);
    for(const auto& i : jevils_) {
      i->draw();
    }
    context->window.display();
    context->autoEvent();
  }

  for(uint8_t i = 0; i < JEVIL_COUNT; ++i) {
    delete jevils_[i];
  }
}