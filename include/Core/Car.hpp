#ifndef CORE_CAR_HPP
#define CORE_CAR_HPP

#include "Core/VehiclePhysicsComponent.hpp"
#include "Core/ModelComponent.hpp"

struct Car {
    ModelComponent          model_comp;
    VehiclePhysicsComponent vehicle_physics_comp;
};

#endif