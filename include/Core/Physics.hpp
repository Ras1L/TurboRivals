#ifndef CORE_PHYSICS_HPP
#define CORE_PHYSICS_HPP

#include "BulletDynamics/Dynamics/btDiscreteDynamicsWorld.h"
#include "BulletCollision/BroadphaseCollision/btBroadphaseInterface.h"
#include "BulletCollision/CollisionDispatch/btCollisionDispatcher.h"
#include "BulletCollision/CollisionDispatch/btDefaultCollisionConfiguration.h"
#include "BulletCollision/CollisionShapes/btCollisionShape.h"
#include "BulletDynamics/ConstraintSolver/btSequentialImpulseConstraintSolver.h"
#include "BulletDynamics/Dynamics/btDiscreteDynamicsWorld.h"
#include "BulletDynamics/Dynamics/btRigidBody.h"
#include "BulletDynamics/Vehicle/btRaycastVehicle.h"
#include "BulletDynamics/Vehicle/btVehicleRaycaster.h"
#include "LinearMath/btDefaultMotionState.h"
#include <memory>

// Отвечает за библиотеку Bullet
class Physics {
public:
    Physics();

    void Update(float dt);
    
    void addVehicle(btRaycastVehicle* v);
    void removeVehicle(btRaycastVehicle* v);
    void addRigidBody(btRigidBody* rb);

    std::unique_ptr<btVehicleRaycaster> createVehicleRaycaster();

private:
    std::unique_ptr<btBroadphaseInterface>               broadphase;
    std::unique_ptr<btDefaultCollisionConfiguration>     config;
    std::unique_ptr<btCollisionDispatcher>               dispatcher;
    std::unique_ptr<btSequentialImpulseConstraintSolver> solver;

    std::unique_ptr<btDiscreteDynamicsWorld> world;

    std::unique_ptr<btCollisionShape>     groundShape;
    std::unique_ptr<btDefaultMotionState> groundMotion;
    std::unique_ptr<btRigidBody>          groundBody;
};

#endif