#ifndef UI_INPUT_HPP
#define UI_INPUT_HPP

#include "raylib.h"

struct Input {
    char forward;
    char sideway;
    Vector2 lookRotation;
};

#endif