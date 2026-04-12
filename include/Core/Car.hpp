#ifndef CORE_CAR_HPP
#define CORE_CAR_HPP

#include "Core/CarPhysicsComponent.hpp"
#include "Core/Transform3D.hpp"
#include "Core/ModelID.hpp"

struct Car {
    ModelID             model_id;
    Transform3D         transform;
    CarPhysicsComponent physic_model;
};

#endif