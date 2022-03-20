#include "Context.hpp"

#include <iostream>
#include <filesystem>
#include <Windows.h>
#include <Dwmapi.h>
#include "main.hpp"

namespace fs = std::filesystem;

Context::Context() :window(), event() {
  debug(L"Context()");
  contextSettings_.antialiasingLevel = 0;
  contextSettings_.depthBits = 16;
  contextSettings_.majorVersion = 2;
  contextSettings_.minorVersion = 1;
  contextSettings_.sRgbCapable = false;

  videoMode = sf::VideoMode::getDesktopMode();
  videoMode.height--;
}

Context::~Context() {
  debug(L"~Context()");
  destroy();
}

void Context::load() {

}

void Context::save() const {

}

void Context::create() {
  window.create(videoMode, L"Strange", sf::Style::None, contextSettings_);
  window.setVerticalSyncEnabled(true);

  MARGINS margins = {-1};
  DwmExtendFrameIntoClientArea(window.getSystemHandle(), &margins);
}

inline void Context::destroy() {
  window.close();
}

inline bool Context::isActual() const {
  return window.isOpen();
}

void Context::autoEvent() {
  if(window.pollEvent(event)) {
    if(sf::Event::Closed == event.type) {
      window.close();
    }
  }
}

inline void Context::autoClock() {
  time = clock.restart();
}

bool Context::pollEvent() {
  if(window.pollEvent(event)) {
    if(sf::Event::Closed == event.type) {
      window.close();
    }
    return true;
  }
  return false;
}

const sf::Texture& Context::getTexture(const uint16_t id) {
  const auto& iterator = texture_.find(id);
  if(iterator != texture_.end()) {
    return iterator->second;
  }

  HRSRC hResource = NULL;
  HGLOBAL hMemory = NULL;

  hResource = FindResourceW(NULL, MAKEINTRESOURCEW(id), L"IMG");
  if(!hResource) {
    exept(L"hResource was NULL");
  }
  hMemory = LoadResource(NULL, hResource);
  if(!hMemory) {
    exept(L"hMemory was NULL");
  }

  texture_.emplace(id, sf::Texture());
  if(!texture_[id].loadFromMemory(LockResource(hMemory), SizeofResource(NULL, hResource))) {
    exept(L"Error loading texture from memory");
  }
  return texture_[id];
}

const sf::SoundBuffer& Context::getSound(const uint16_t id) {
  const auto& iterator = audio_.find(id);
  if(iterator != audio_.end()) {
    return iterator->second;
  }

  HRSRC hResource = NULL;
  HGLOBAL hMemory = NULL;

  hResource = FindResourceW(NULL, MAKEINTRESOURCEW(id), L"SND");
  if(!hResource) {
    throw Exeption(L"hResource was NULL", __FILE__, __LINE__);
  }
  hMemory = LoadResource(NULL, hResource);
  if(!hMemory) {
    throw Exeption(L"hMemory was NULL", __FILE__, __LINE__);
  }

  audio_.emplace(id, sf::SoundBuffer());
  if(!audio_[id].loadFromMemory(LockResource(hMemory), SizeofResource(NULL, hResource))) {
    throw Exeption(L"Error loading audio from memory", __FILE__, __LINE__);
  }
  return audio_[id];
}

const sf::Music& Context::getMusic(const uint16_t id) {
  const auto& iterator = music_.find(id);
  if(iterator != music_.end()) {
    return iterator->second;
  }

  HRSRC hResource = NULL;
  HGLOBAL hMemory = NULL;

  hResource = FindResourceW(NULL, MAKEINTRESOURCEW(id), L"MUS");
  if(!hResource) {
    throw Exeption(L"hResource was NULL", __FILE__, __LINE__);
  }
  hMemory = LoadResource(NULL, hResource);
  if(!hMemory) {
    throw Exeption(L"hMemory was NULL", __FILE__, __LINE__);
  }

  music_.emplace(id, sf::SoundBuffer());
  if(!music_[id].openFromMemory(LockResource(hMemory), SizeofResource(NULL, hResource))) {
    throw Exeption(L"Error loading audio from memory", __FILE__, __LINE__);
  }
  return music_[id];
}

Context context;