#pragma once

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
