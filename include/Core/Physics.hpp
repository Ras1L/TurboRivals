#ifndef CORE_PHYSICS_HPP
#define CORE_PHYSICS_HPP

#include "Core/Transform3D.hpp"

#include "BulletDynamics/Vehicle/btRaycastVehicle.h"
#include "BulletDynamics/Vehicle/btVehicleRaycaster.h"
#include "BulletDynamics/Dynamics/btDiscreteDynamicsWorld.h"
#include "BulletCollision/BroadphaseCollision/btBroadphaseInterface.h"
#include "BulletCollision/CollisionDispatch/btCollisionDispatcher.h"
#include "BulletCollision/CollisionDispatch/btDefaultCollisionConfiguration.h"
#include "BulletCollision/CollisionShapes/btCollisionShape.h"
#include "BulletDynamics/ConstraintSolver/btSequentialImpulseConstraintSolver.h"
#include "BulletDynamics/Dynamics/btDiscreteDynamicsWorld.h"
#include "BulletDynamics/Dynamics/btRigidBody.h"
#include "LinearMath/btDefaultMotionState.h"

// Связывает классы GameWorld и Input, отвечает за библиотеку Bullet
class Physics {
public:
    void Init();
    void Update(char forward, bool brake, char sideway, float dt);
    
    Transform3D GetVehicleTransform();
   
    ~Physics();

private:
    btRaycastVehicle*        vehicle;
    btDiscreteDynamicsWorld* world;

    btBroadphaseInterface*               broadphase;
    btDefaultCollisionConfiguration*     config;
    btCollisionDispatcher*               dispatcher;
    btSequentialImpulseConstraintSolver* solver;

    btCollisionShape*     groundShape;
    btDefaultMotionState* groundMotion;
    btRigidBody*          groundBody;

    btCollisionShape*     chassisShape;
    btDefaultMotionState* motion;
    btRigidBody*          chassis;

    btVehicleRaycaster* raycaster;
};

#endif