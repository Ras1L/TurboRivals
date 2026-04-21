#ifndef RENDER_RESOURCEMANAGER_HPP
#define RENDER_RESOURCEMANAGER_HPP

#include "Core/ModelID.hpp"
#include "Core/CollisionMeshData.hpp"

#include "raylib.h"
#include <unordered_map>
#include <vector>
#include <string>

class ResourceManager {
public:
    ResourceManager();
    ResourceManager(const ResourceManager&) = delete;
    ResourceManager& operator=(const ResourceManager&) = delete;

    void InitModels();
    void UnloadModels();

    Model                          GetModelByID(ModelID id) const;
    std::vector<CollisionMeshData> GetCollisionMeshDataByID(ModelID id);

private:
    std::unordered_map<ModelID, Model> models;
    std::vector<std::string> model_paths;
};

#endif