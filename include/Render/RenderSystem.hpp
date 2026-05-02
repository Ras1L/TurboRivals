#ifndef RENDER_RENDERSYSTEM_HPP
#define RENDER_RENDERSYSTEM_HPP

#include "Core/Car.hpp"
#include "Render/ResourceManager.hpp"

#include <span>

class RenderSystem {
public:
    RenderSystem();

    void DrawCar(const Car& car, const ResourceManager& res_manager) const;
    void DrawCars(std::span<const Car* const> cars, const ResourceManager& res_manager) const;
    void DrawStaticModel(const ModelComponent& model_comp, const ResourceManager& res_manager) const;
};

#endif