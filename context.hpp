#pragma once
#include <map>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

#include "resource.h"
#include "Exeption.hpp"

class Context {
  std::map<uint16_t, sf::Texture> texture_;
  std::map<uint16_t, sf::SoundBuffer> audio_;
  std::map<uint16_t, sf::Music> music_;
  sf::ContextSettings contextSettings_;
  sf::Context context_;
public:

  sf::RenderWindow window;
  sf::VideoMode videoMode;
  sf::Event event;

  sf::Clock clock;
  sf::Time time;

  Context();

  ~Context();

  void load();

  void save() const;

  void create();

  void destroy();

  bool isActual() const;

  void autoEvent();

  void autoClock();

  bool pollEvent();

  const sf::Texture& getTexture(const uint16_t id);

  const sf::SoundBuffer& getSound(const uint16_t id);

  const sf::Music& getMusic(const uint16_t id);
};
extern Context context;