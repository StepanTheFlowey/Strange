#include "JevilDance.hpp"

EntityJevil::EntityJevil() {
  debug(L"EntityJevil()");

  moveSpeed_ = 0.8F + static_cast<float>(rand() % 5) / 10.0F;
  moveDir_ = rand() % 360;
  phase_ = rand() % 8;
  side_ = rand() % 2;
}

EntityJevil::~EntityJevil() {
  debug(L"~EntityJevil()");
}

void EntityJevil::create() {
  sprite_.setTexture(*context->getTexture(ID_IMG1));
  sprite_.setPosition(
    static_cast<float>(rand() % context->videoMode.width),
    static_cast<float>(rand() % context->videoMode.height)
  );
  sprite_.setScale(2.0F, 2.0F);
  sprite_.setOrigin(23, 24);

  sprite_.setTextureRect(sf::IntRect(phase_ * 46, side_ * 48, 46, 48));
}

void EntityJevil::destroy() {}

void EntityJevil::update() {
  sf::Vector2f pos = sprite_.getPosition();

  if(pos.x < 0 || pos.x > context->videoMode.width || pos.y < 0 || pos.y > context->videoMode.height) {
    moveDir_ += 180 - moveDir_ % 90 * 2;
    sprite_.move(sinf(moveDir_ * F_DEG_TO_RAD), cosf(moveDir_ * F_DEG_TO_RAD));
  }

  if(moveDir_ < 360) {
    moveDir_ += 360;
  }
  if(moveDir_ > 360) {
    moveDir_ -= 360;
  }

  sprite_.move(sinf(moveDir_ * F_DEG_TO_RAD), cosf(moveDir_ * F_DEG_TO_RAD));

  time_ += context->time;

  if(time_.asMilliseconds() > 70) {
    time_ -= sf::milliseconds(70);

    phase_++;
    if(phase_ > 7) {
      phase_ = 0;
      side_ = !side_;
    }
    sprite_.setTextureRect(sf::IntRect(phase_ * 46, side_ * 48, 46, 48));
  }
}

void EntityJevil::draw() {
  context->window.draw(sprite_);
#ifdef DEBUG
  sf::Vertex vt[2];
  vt[0].color = sf::Color::Green;
  vt[1].color = sf::Color::Green;
  vt[0].position = sprite_.getPosition();
  vt[1].position = sprite_.getPosition() + sf::Vector2f(sinf(moveDir_ * DEG_TO_RAD) * 100.0F, cosf(moveDir_ * DEG_TO_RAD) * 100.0F);
  context->window.draw(vt, 2, sf::Lines);
#endif // DEBUG
}
