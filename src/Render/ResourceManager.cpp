#include "Render/ResourceManager.hpp"
#include "Core/EnvironmentID.hpp"
#include "raylib.h"

ResourceManager::ResourceManager()
{
    model_paths = {
        "assets/models/porsche_911_carrera_993_gt2psx_style_v2.glb",
        "assets/models/1969_dodge_charger_rt_gt2psx_style.glb",
        "assets/models/ps1_gt1-style_model_-_1992_emery_aventus.glb",
        "assets/models/ps1_gt1-style_model_-_1994_kineto_rm-x.glb",
        "assets/models/ps1_gt1-style_model_-_1996_horai_bx300.glb"
    };

    environment_paths = {
        "assets/environments/3d_skybox_montain__game-ready.glb"
    };
}

void ResourceManager::InitModels()
{
    for (size_t i = 0; i < model_paths.size(); ++i)
    {
        ModelID id = static_cast<ModelID>(i);
        Model m = LoadModel(model_paths[i].c_str());

        models.insert({id, m});
    }

    for (size_t i = 0; i < environment_paths.size(); ++i)
    {
        EnvironmentID id = static_cast<EnvironmentID>(i);
        Model m = LoadModel(environment_paths[i].c_str());

        environments.insert({id, m});
    }
}

Model ResourceManager::GetModelByID(ModelID id) const
{
    return models.at(id);
}

Model ResourceManager::GetEnvironmentByID(EnvironmentID id) const
{
    return environments.at(id);
}

void ResourceManager::UnloadModels()
{
    for (auto it = models.cbegin(); it != models.cend(); ++it)
    {
        UnloadModel(it->second);
    }
    for (auto it = environments.cbegin(); it != environments.cend(); ++it)
    {
        UnloadModel(it->second);
    }
}