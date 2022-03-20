#include "JevilDance.hpp"

inline JevilDance::JevilDance() {
#ifdef DEBUG
    std::wcout << L"JevilDance()" << std::endl;
#endif // DEBUG
    moveSpeed_ = 0.8F + static_cast<float>(rand() % 5) / 10.0F;
    moveDir_ = rand() % 360;
    phase_ = rand() % 8;
    side_ = rand() % 2;
}

inline JevilDance::~JevilDance() {
#ifdef DEBUG
    std::wcout << L"~JevilDance()" << std::endl;
#endif // DEBUG
}

inline void JevilDance::create(Context* context) {
    context_ = context;
    sprite_.setTexture(context_->getTexture(IDB_PNG1));
    sprite_.setPosition(
        static_cast<float>(rand() % context_->videoMode.width),
        static_cast<float>(rand() % context_->videoMode.height)
    );
    sprite_.setScale(2.0F, 2.0F);
    sprite_.setOrigin(23, 24);

    sprite_.setTextureRect(sf::IntRect(phase_ * 46, side_ * 48, 46, 48));
}

inline void JevilDance::update() {
    sf::Vector2f pos = sprite_.getPosition();

    if(pos.x < 0 || pos.x > context_->videoMode.width || pos.y < 0 || pos.y > context_->videoMode.height) {
        moveDir_ += 180 - moveDir_ % 90 * 2;
        sprite_.move(sinf(moveDir_ * DEG_TO_RAD_F), cosf(moveDir_ * DEG_TO_RAD_F));
    }

    if(moveDir_ < 360) {
        moveDir_ += 360;
    }
    if(moveDir_ > 360) {
        moveDir_ -= 360;
    }

    sprite_.move(sinf(moveDir_ * DEG_TO_RAD_F), cosf(moveDir_ * DEG_TO_RAD_F));

    time += context_->time;

    if(time.asMilliseconds() > 70) {
        time -= sf::milliseconds(70);

        phase_++;
        if(phase_ > 7) {
            phase_ = 0;
            side_ = !side_;
        }
        sprite_.setTextureRect(sf::IntRect(phase_ * 46, side_ * 48, 46, 48));
    }
}

inline void JevilDance::draw() {
    context_->window.draw(sprite_);
#ifdef DEBUG
    sf::Vertex vt[2];
    vt[0].color = sf::Color::Green;
    vt[1].color = sf::Color::Green;
    vt[0].position = sprite_.getPosition();
    vt[1].position = sprite_.getPosition() + sf::Vector2f(sinf(moveDir_ * DEG_TO_RAD) * 100.0F, cosf(moveDir_ * DEG_TO_RAD) * 100.0F);
    context_->window.draw(vt, 2, sf::Lines);
#endif // DEBUG
}
