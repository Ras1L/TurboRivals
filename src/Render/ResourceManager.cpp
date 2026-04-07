#include "Render/ResourceManager.hpp"
#include "raylib.h"
#include <cstddef>

ResourceManager::ResourceManager()
{
    model_paths = {
        "assets/models/porsche_911_carrera_993_gt2psx_style_v2.glb",
        "assets/models/1969_dodge_charger_rt_gt2psx_style.glb"
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
}

Model ResourceManager::GetModelByID(ModelID id) const
{
    return models.at(id);
}

void ResourceManager::UnloadModels()
{
    for (auto it = models.cbegin(); it != models.cend(); ++it)
    {
        UnloadModel(it->second);
    }
}