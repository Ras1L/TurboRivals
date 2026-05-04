#include "Render/ResourceManager.hpp"
#include "raylib.h"

ResourceManager::ResourceManager()
{
    model_paths = {
        "assets/models/porsche_911_carrera_993_gt2psx_style_v2.glb",
        "assets/models/1969_dodge_charger_rt_gt2psx_style.glb",
        "assets/models/ps1_gt1-style_model_-_1996_horai_bx300.glb",
    
        "assets/environments/3d_skybox_montain__game-ready.glb",

        "assets/tracks/race_track__low_poly_v2.glb"
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

std::vector<CollisionMeshData> ResourceManager::GetCollisionMeshDataByID(ModelID id)
{
    Model m = GetModelByID(id);
    std::vector<CollisionMeshData> collision_mesh_data;

    for (int i = 0; i < m.meshCount; ++i)
    {
        collision_mesh_data.push_back({
            m.meshes[i].vertexCount,
            m.meshes[i].triangleCount,
            m.meshes[i].vertices,
            m.meshes[i].indices
        });
    }

    return collision_mesh_data;
}

void ResourceManager::UnloadModels()
{
    for (auto it = models.cbegin(); it != models.cend(); ++it)
    {
        UnloadModel(it->second);
    }
}