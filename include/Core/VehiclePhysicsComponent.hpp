#ifndef CORE_VEHICLE_PHYSICS_COMPONENT_HPP
#define CORE_VEHICLE_PHYSICS_COMPONENT_HPP

#include "BulletCollision/CollisionShapes/btCollisionShape.h"
#include "BulletDynamics/Dynamics/btRigidBody.h"
#include "BulletDynamics/Vehicle/btRaycastVehicle.h"
#include "BulletDynamics/Vehicle/btVehicleRaycaster.h"
#include "Core/Physics.hpp"
#include "Core/Transform3D.hpp"
#include "LinearMath/btDefaultMotionState.h"
#include "Core/Input.hpp"
#include <memory>

class VehiclePhysicsComponent {
public:
    void Init(Vector3 pos, Physics& physic_world);
    void Destroy(Physics& physic_world);

    void        Update(Input input, float dt);
    Transform3D GetVehicleTransform();

private:
    std::unique_ptr<btCollisionShape>     chassisShape;
    std::unique_ptr<btDefaultMotionState> motion;
    std::unique_ptr<btRigidBody>          chassis;

    // тут прикол, чтобы raycaster создать нужно ему дать <btDiscreteDynamicsWorld*> или просто world
    // за этот глобальный world отвечает class Physics, но владеть по логике raycaster-ом должны отдельные Car через CarPhysicsComponent
    // по итогу raycaster нам создает Physics по нашему запросу и передает владение, то есть unique_ptr нам возвращает
    std::unique_ptr<btVehicleRaycaster>   raycaster;

    std::unique_ptr<btRaycastVehicle> vehicle;

    float engine     = 0.f;
    float steering   = 0.f;
    float brakeForce = 0.f;
};

#endif