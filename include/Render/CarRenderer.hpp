#ifndef RENDER_CARRENDERER_HPP
#define RENDER_CARRENDERER_HPP

#include "Render/ResourceManager.hpp"
#include <Core/Car.hpp>

class CarRenderer {
public:
    void DrawCar(const Car& car, const ResourceManager& res_manager) const;
};

#endif