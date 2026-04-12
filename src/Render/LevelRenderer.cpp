#include "Render/LevelRenderer.hpp"
#include "Render/ResourceManager.hpp"
#include "raylib.h"

void LevelRenderer::DrawEnvironment(EnvironmentID id, const ResourceManager& res_manager) const
{
    Model model = res_manager.GetEnvironmentByID(id);
    static const Vector3 pos = {0.f, -164.f, 0.f};

    DrawModel(model, pos, 300.f, WHITE);
}