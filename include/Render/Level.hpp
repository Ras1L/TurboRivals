#ifndef RENDER_LEVEL_HPP
#define RENDER_LEVEL_HPP

#include "raylib.h"

const int floorExtent = 25;
const float tileSize = 5.0f;
const Color tileColor1{ 150, 200, 200, 255 };

class Level {
public:
    void DrawLevel();
};

#endif