#ifndef RENDER_RENDERSYSTEM_HPP
#define RENDER_RENDERSYSTEM_HPP

#include "Core/Car.hpp"
#include "Render/CarRenderer.hpp"
#include "Render/LevelRenderer.hpp"
#include "Render/ResourceManager.hpp"

#include <span>

class RenderSystem {
public:
    RenderSystem() = default;
    RenderSystem(const RenderSystem&) = delete;
    RenderSystem& operator=(const RenderSystem&) = delete;

    void Init();
    void Destroy();

    void DrawCar(const Car& car) const;
    void DrawCars(std::span<const Car* const> cars) const;
    void DrawEnvironment(EnvironmentID id) const;

private:
    ResourceManager res_manager;
    CarRenderer     car_renderer;
    LevelRenderer   level_renderer;
};

#endif