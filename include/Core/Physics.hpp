#ifndef CORE_PHYSICS_HPP
#define CORE_PHYSICS_HPP

#include "Core/Body.hpp"

class Physics {
public:
    void UpdateBody(Body& body, float rot, char forward, char sideway);
};

#endif