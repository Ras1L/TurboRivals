#include "Render/RenderSystem.hpp"
#include "Render/ResourceManager.hpp"

#include "rlgl.h" // дебри raylib 

const double near = 0.1f;
const double far  = 10000.f;

void RenderSystem::Init()
{
    rlSetClipPlanes(near, far); // это уже дебри raylib, но я горы хочу видеть
    res_manager.InitModels();
}

void RenderSystem::DrawCar(const Car& car) const
{
    car_renderer.DrawCar(car, res_manager);
}

void RenderSystem::DrawCars(std::span<const Car* const> cars) const
{
    for (auto car : cars) {
        car_renderer.DrawCar(*car, res_manager);
    }
}

void RenderSystem::DrawEnvironment(EnvironmentID id) const
{
    level_renderer.DrawEnvironment(id, res_manager);
}

void RenderSystem::Destroy()
{
    res_manager.UnloadModels();
}