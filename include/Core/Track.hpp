#ifndef CORE_TRACK_HPP
#define CORE_TRACK_HPP

#include "Core/ModelComponent.hpp"
#include "Core/TrackCollisionComponent.hpp"

struct Track {
    ModelComponent          model_comp;
    TrackCollisionComponent collision_comp;
};


#endif