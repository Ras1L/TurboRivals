#include "Render/Level.hpp"

void Level::DrawLevel()
{
    for (int y = -floorExtent; y < floorExtent; y++)
    {
        for (int x = -floorExtent; x < floorExtent; x++)
        {
            if ((y & 1) && (x & 1))
            {
                DrawPlane({ x*tileSize, 0.0f, y*tileSize}, { tileSize, tileSize }, tileColor1);
            }
            else if (!(y & 1) && !(x & 1))
            {
                DrawPlane({ x*tileSize, 0.0f, y*tileSize}, { tileSize, tileSize }, LIGHTGRAY);
            }
        }
    }
}