#pragma once
#include "types.h"
#include "screen.hpp"

//Containers
#include <unordered_map>

//IO
#include <iostream>

//WinAPI
#include <Windows.h>
#include <Dwmapi.h>

//SFML
#include <SFML\Graphics.hpp>

//Disatance between A and B point
template <typename T> double_t getDistance(sf::Vector2<T> A, sf::Vector2<T> B) {
  T x = B.x - A.x;
  T y = B.y - A.y;
  return std::sqrt(x * x + y * y);
}

//Angle between AB and BC lines
template <typename T> double_t getAngle(sf::Vector2<T> A, sf::Vector2<T> B, sf::Vector2<T> C) {
  const double_t a = getDistance(A, C);
  const double_t b = getDistance(B, C);
  const double_t c = getDistance(B, A);

  if(a == 0 || b == 0 || c == 0) {
    return 0;
  }

  return std::acos((b * b + c * c - a * a) / (2 * b * c));
}

sf::Vector2i getRandomCreatorBeginPos() {
  auto desktopMode = sf::VideoMode::getDesktopMode();
  return sf::Vector2i(
    rand() % 2 ? -1 * (rand() % desktopMode.width) : desktopMode.width + (rand() % desktopMode.width),
    rand() % 2 ? -1 * (rand() % desktopMode.height) : desktopMode.height + (rand() % desktopMode.height)
  );
}

class CreatorArray;

class Creator {
  sf::VertexBuffer rect_;
  sf::VertexBuffer triangle_;
  bool deadable = false;
  gametime_t lifeTime_ = -1;
  gametime_t timeCounter = 0;
  int16_t tWidth_ = -1;        //Target width
  int16_t sWidth_ = 0;         //Step width
  int16_t iWidth_ = 0;         //Interval width
public:
  sf::Color color;
  sf::Vector2i beginPoint;
  sf::Vector2i endPoint;
  int16_t width = 0;
  bool changed = false;

  Creator():rect_(sf::Quads, sf::VertexBuffer::Stream), triangle_(sf::TriangleFan, sf::VertexBuffer::Stream) {
    if(!rect_.create(4)) {
      std::wcout << L"Cannot create VBO\n";
      _wsystem(L"pause");
      exit(0);
    }
  }

  bool update(gametime_t time) {
    if(deadable && lifeTime_ != -1) {
      lifeTime_ -= time;
      if(lifeTime_ < 0) {
        return true;
      }
    }
    if(tWidth_ != -1) {
      if(width <= tWidth_) {
        width += time / iWidth_ * sWidth_;
        timeCounter += time - (time / iWidth_ * sWidth_) * iWidth_;
        if(timeCounter > iWidth_) {
          width += timeCounter / iWidth_ * sWidth_;
          timeCounter -= (timeCounter / iWidth_ * sWidth_) * iWidth_;
        }
        if(width > tWidth_) {
          width = tWidth_;
          tWidth_ = -1;
        }
      }
      else {
        width -= time / iWidth_ * sWidth_;
        timeCounter += time - (time / iWidth_ * sWidth_) * iWidth_;
        if(timeCounter > iWidth_) {
          width -= timeCounter / iWidth_ * sWidth_;
          timeCounter -= (timeCounter / iWidth_ * sWidth_) * iWidth_;
        }
        if(width < tWidth_) {
          width = 0;
          tWidth_ = -1;
        }
      }

    }
    if(width <= 0) {
      return deadable;
    }

    if(width == 0 || !changed) {
      return false;
    }
    sf::Vertex rect[4];
    sf::Vector2i zeroPoint(beginPoint.x, endPoint.y);
    double_t angle = 0.0;
    if((beginPoint.x <= endPoint.x && beginPoint.y < endPoint.y) || (beginPoint.x >= endPoint.x && beginPoint.y > endPoint.y)) {
      angle = getAngle(zeroPoint, beginPoint, endPoint);
      angle += 1.5707963267948966192313216916398;
    }
    else {
      angle = getAngle(zeroPoint, endPoint, beginPoint);
    }

    rect[0].position.x = beginPoint.x - sin(angle) * width / 2;
    rect[0].position.y = beginPoint.y - cos(angle) * width / 2;

    rect[3].position.x = beginPoint.x + sin(angle) * width / 2;
    rect[3].position.y = beginPoint.y + cos(angle) * width / 2;

    rect[1].position.x = endPoint.x - sin(angle) * width / 2;
    rect[1].position.y = endPoint.y - cos(angle) * width / 2;

    rect[2].position.x = endPoint.x + sin(angle) * width / 2;
    rect[2].position.y = endPoint.y + cos(angle) * width / 2;

    rect[0].color = sf::Color::Red;
    rect[1].color = sf::Color::Red;
    rect[2].color = sf::Color::Red;
    rect[3].color = sf::Color::Red;

    rect_.update(rect);

    sf::Vertex *tri = new sf::Vertex[width + 2];
    triangle_.create(width + 2);
    tri[0].position = sf::Vector2f(endPoint);
    const uint16_t step = 180 / width;
    if(beginPoint.y <= endPoint.y) {
      angle += PI;
    }

    for(uint8_t i = 0; i < width + 1; i++) {
      tri[i + 1].position.x = sin(double_t(i * step) * DEG_TO_RAD + angle) * width / 2 + endPoint.x;
      tri[i + 1].position.y = cos(double_t(i * step) * DEG_TO_RAD + angle) * width / 2 + endPoint.y;
    }

    for(uint8_t i = 0; i < width + 2; i++) {
      tri[i].color = sf::Color::Red;
    }
    triangle_.update(tri);
    delete[] tri;
    return false;
  }

  void draw(Screen &screen) {
    screen.window.draw(rect_);
    screen.window.draw(triangle_);
  }

  friend CreatorArray;
};