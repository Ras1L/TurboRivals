#include "Render/RenderSystem.hpp"

#include "raymath.h"
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
    auto model = res_manager.GetModelByID(car.model_comp.mid);
    
    Matrix rot   = QuaternionToMatrix(car.model_comp.transform.rot);
    Matrix trans = MatrixTranslate(
        car.model_comp.transform.pos.x,
        car.model_comp.transform.pos.y,
        car.model_comp.transform.pos.z
    );
    model.transform = MatrixMultiply(rot, trans);

    DrawModel(model, {0.f, 0.f, 0.f}, 1.f, WHITE);
}

void RenderSystem::DrawCars(std::span<const Car* const> cars) const
{
    for (auto car : cars) {
        DrawCar(*car);
    }
}

void RenderSystem::DrawEnvironment(const Environment& environment) const
{
    auto model = res_manager.GetModelByID(environment.model_comp.mid);
    model.transform = MatrixTranslate(
        environment.model_comp.transform.pos.x,
        environment.model_comp.transform.pos.y,
        environment.model_comp.transform.pos.z
    );

    DrawModel(model, {0.f, 0.f, 0.f}, 1.f, WHITE);
}

void RenderSystem::Destroy()
{
    res_manager.UnloadModels();
}