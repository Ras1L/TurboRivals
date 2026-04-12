#ifndef RENDER_LEVELRENDERER_HPP
#define RENDER_LEVELRENDERER_HPP

#include "Render/ResourceManager.hpp"

// const int floorExtent = 25;
// const float tileSize = 5.0f;
// const Color tileColor1{ 150, 200, 200, 255 };

class LevelRenderer {
public:
    void DrawEnvironment(EnvironmentID id, const ResourceManager& res_manager) const;

private:

};

#endif