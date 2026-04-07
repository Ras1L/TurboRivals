#ifndef RENDER_LEVELRENDERER_HPP
#define RENDER_LEVELRENDERER_HPP

#include "raylib.h"

const int floorExtent = 25;
const float tileSize = 5.0f;
const Color tileColor1{ 150, 200, 200, 255 };

enum class LevelModelID {
    SNOW,
    
    COUNT
};

class LevelRenderer {
public:
    void DrawLevel();
};

#endif