#ifndef RENDER_RESOURCEMANAGER_HPP
#define RENDER_RESOURCEMANAGER_HPP

#include "Core/ModelID.hpp"
#include "Core/EnvironmentID.hpp"

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

    Model GetModelByID(ModelID id) const;
    Model GetEnvironmentByID(EnvironmentID id) const;

private:
    std::unordered_map<ModelID, Model> models;
    std::vector<std::string> model_paths;

    std::unordered_map<EnvironmentID, Model> environments;
    std::vector<std::string> environment_paths;
};

#endif