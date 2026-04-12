#include "Core/Physics.hpp"

#include "BulletCollision/BroadphaseCollision/btDbvtBroadphase.h"
#include "BulletCollision/CollisionShapes/btStaticPlaneShape.h"
#include "BulletDynamics/Dynamics/btRigidBody.h"
#include "BulletDynamics/Vehicle/btRaycastVehicle.h"
#include "BulletDynamics/Vehicle/btVehicleRaycaster.h"
#include "LinearMath/btTransform.h"
#include "LinearMath/btVector3.h"
#include <memory>

Physics::Physics()
{
    // WORLD
    broadphase = std::make_unique<btDbvtBroadphase>();
    config     = std::make_unique<btDefaultCollisionConfiguration>();
    dispatcher = std::make_unique<btCollisionDispatcher>(config.get());
    solver     = std::make_unique<btSequentialImpulseConstraintSolver>();
    world      = std::make_unique<btDiscreteDynamicsWorld>(dispatcher.get(), broadphase.get(), solver.get(), config.get());

    world->setGravity({0.f, -9.8f, 0.f});

    // GROUND
    groundShape  = std::make_unique<btStaticPlaneShape>(btVector3{0.f, 1.f, 0.f}, 0.f);
    groundMotion = std::make_unique<btDefaultMotionState>(btTransform::getIdentity());
    btRigidBody::btRigidBodyConstructionInfo groundCI(0.f, groundMotion.get(), groundShape.get());
    groundBody   = std::make_unique<btRigidBody>(groundCI);

    world->addRigidBody(groundBody.get());
}

void Physics::Update(float dt)
{
    world->stepSimulation(dt);
}

void Physics::addVehicle(btRaycastVehicle* v)
{
    world->addVehicle(v);
}

void Physics::removeVehicle(btRaycastVehicle* v)
{
    world->removeVehicle(v);
}

void Physics::addRigidBody(btRigidBody* rb)
{
    world->addRigidBody(rb);
}

std::unique_ptr<btVehicleRaycaster> Physics::createVehicleRaycaster()
{
    return std::make_unique<btDefaultVehicleRaycaster>(world.get());
}