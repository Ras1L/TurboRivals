#ifndef CORE_MODEL_COMPONENT_HPP
#define CORE_MODEL_COMPONENT_HPP

#include "Core/ModelID.hpp"
#include "Core/Transform3D.hpp"

struct ModelComponent {
    ModelID     mid;
    Transform3D transform;
};

#endif