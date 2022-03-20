#pragma once

#define WIN32_LEAN_AND_MEAN
#define NOMINMAX
#include <iostream>
#include <Windows.h>

#define PI 3.1415926535897932384626433832795
#define RAD_TO_DEG 57.295779513082320876798154814105
#define RAD_TO_DEG_F 57.295779513082320876798154814105F
#define DEG_TO_RAD 0.01745329251994329576923690768489
#define DEG_TO_RAD_F 0.01745329251994329576923690768489F

#ifdef DEBUG

#define debug(str) std::wcout << str << std::endl

#else

#define debug(str)

#endif // DEBUG

#define exept(str) throw Exeption(str, __FILE__, __LINE__)

std::wstring wide(const std::string string);

std::string shrink(const std::wstring wstring);