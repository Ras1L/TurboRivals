#include "Render/CarRenderer.hpp"
#include "raylib.h"
#include "raymath.h"

void CarRenderer::DrawCar(const Car& car, const ResourceManager& res_manager) const
{
    auto model = res_manager.GetModelByID(car.model_id);

    Matrix rot   = QuaternionToMatrix(car.transform.rot);
    Matrix trans = MatrixTranslate(
        car.transform.pos.x,
        car.transform.pos.y,
        car.transform.pos.z
    );
    model.transform = MatrixMultiply(rot, trans);
    
    DrawModel(model, {0.f, 0.f, 0.f}, 1.f, WHITE);
}