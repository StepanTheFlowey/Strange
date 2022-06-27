#pragma once

#define WIN32_LEAN_AND_MEAN
#define NOMINMAX

#include <iostream>
#include <Windows.h>

constexpr double PI = 3.1415926535897932384626433832795;
constexpr double RAD_TO_DEG = 57.295779513082320876798154814105;
constexpr double DEG_TO_RAD = 0.01745329251994329576923690768489;

constexpr float F_PI = 3.1415926535897932384626433832795;
constexpr float F_RAD_TO_DEG = 57.295779513082320876798154814105F;
constexpr float F_DEG_TO_RAD = 0.01745329251994329576923690768489F;

#ifdef DEBUG

#define debug(str) std::wcout << str << std::endl

#else

#define debug(str)

#endif // DEBUG

#define exept(str) throw Exeption(str, __FILE__, __LINE__)

inline std::wstring wide(const std::string string) {
  return std::wstring(string.begin(), string.end());
}

inline std::string shrink(const std::wstring wstring) {
  return std::string(wstring.begin(), wstring.end());
}
