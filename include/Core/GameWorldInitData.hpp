#ifndef CORE_GAMEWORLD_INIT_DATA_HPP
#define CORE_GAMEWORLD_INIT_DATA_HPP

#include "Core/CollisionMeshData.hpp"
#include <vector>

struct GameWorldInitData {
    std::vector<CollisionMeshData> track_col_mesh;
};

#endif