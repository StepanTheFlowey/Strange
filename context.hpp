#pragma once
#include <map>
#include <iostream>
#include <filesystem>
#include <Windows.h>
#include <Dwmapi.h>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

#include "resource.h"
#include "exeption.hpp"

#define DEG_TO_RAD 0.01745329251994329576923690768489
#define DEG_TO_RAD_F 0.01745329251994329576923690768489F

namespace fs = std::filesystem;

class Context {
  std::map<uint16_t, sf::Texture> texture_;
  std::map<uint16_t, sf::SoundBuffer> audio_;
  sf::ContextSettings contextSettings_;
  sf::Context context_;
public:
  sf::RenderWindow window;
  sf::VideoMode videoMode;
  sf::Event event;

  sf::Clock clock;
  sf::Time time;

  Context():window(), event() {
    contextSettings_.antialiasingLevel = 0;
    contextSettings_.depthBits = 16;
    contextSettings_.stencilBits = 0;
    contextSettings_.majorVersion = 2;
    contextSettings_.minorVersion = 1;
    contextSettings_.sRgbCapable = false;

    videoMode = sf::VideoMode::getDesktopMode();
    videoMode.height--;
  }

  ~Context() {

  }

  void load() {

  }

  void save() {

  }

  void create() {
    window.create(videoMode, L"[name]", sf::Style::None, contextSettings_);
    window.setVerticalSyncEnabled(true);

    MARGINS margins = {-1};
    DwmExtendFrameIntoClientArea(window.getSystemHandle(), &margins);
  }

  void destroy() {
    window.close();
  }

  bool isOpen() {
    return window.isOpen();
  }

  void autoEvent() {
    if(window.pollEvent(event)) {
      if(sf::Event::Closed == event.type) {
        window.close();
      }
    }
  }

  void autoClock() {
    time = clock.restart();
  }

  bool pollEvent() {
    if(window.pollEvent(event)) {
      if(sf::Event::Closed == event.type) {
        window.close();
      }
      return true;
    }
    return false;
  }

  sf::Texture& getTexture(const uint16_t id) {
    const auto& iterator = texture_.find(id);
    if(iterator != texture_.end()) {
      return iterator->second;
    }

    HRSRC hResource = NULL;
    HGLOBAL hMemory = NULL;

    hResource = FindResourceW(NULL, MAKEINTRESOURCEW(id), L"PNG");
    if(!hResource) {
      throw Exeption(L"hResource was NULL");
    }
    hMemory = LoadResource(NULL, hResource);
    if(!hMemory) {
      throw Exeption(L"hMemory was NULL");
    }

    texture_.emplace(id,sf::Texture());
    if(!texture_[id].loadFromMemory(LockResource(hMemory), SizeofResource(NULL, hResource))) {
      throw Exeption(L"Error loading texture from memory");
    }
    return texture_[id];
  }

  sf::SoundBuffer& getAudio(const uint16_t id) {
    const auto& iterator = audio_.find(id);
    if(iterator != audio_.end()) {
      return iterator->second;
    }

    HRSRC hResource = NULL;
    HGLOBAL hMemory = NULL;

    hResource = FindResourceW(NULL, MAKEINTRESOURCEW(id), L"WAVE");
    if(!hResource) {
      throw Exeption(L"hResource was NULL");
    }
    hMemory = LoadResource(NULL, hResource);
    if(!hMemory) {
      throw Exeption(L"hMemory was NULL");
    }

    audio_.emplace(id, sf::SoundBuffer());
    if(!audio_[id].loadFromMemory(LockResource(hMemory), SizeofResource(NULL, hResource))) {
      throw Exeption(L"Error loading audio from memory");
    }
    return audio_[id];
  }
};