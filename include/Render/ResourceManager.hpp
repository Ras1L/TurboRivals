#ifndef RENDER_RESOURCEMANAGER_HPP
#define RENDER_RESOURCEMANAGER_HPP

#include "Core/ModelID.hpp"

#include "raylib.h"
#include <unordered_map>
#include <vector>
#include <string>

class ResourceManager {
public:
    ResourceManager();
    void InitModels();
    void UnloadModels();

    Model GetModelByID(ModelID id) const;

private:
    std::unordered_map<ModelID, Model> models;
    std::vector<std::string> model_paths;
};

#endif