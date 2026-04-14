#ifndef RENDER_RENDERSYSTEM_HPP
#define RENDER_RENDERSYSTEM_HPP

#include "Core/Car.hpp"
#include "Core/Environment.hpp"
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
    void DrawEnvironment(const Environment& environment) const;

private:
    ResourceManager res_manager;
};

#endif