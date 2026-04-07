#include "Core/Physics.hpp"


#include "BulletCollision/BroadphaseCollision/btDbvtBroadphase.h"
#include "BulletCollision/CollisionShapes/btBoxShape.h"
#include "BulletCollision/CollisionShapes/btStaticPlaneShape.h"
#include "Core/Transform3D.hpp"
#include "LinearMath/btScalar.h"
#include "LinearMath/btTransform.h"
#include "LinearMath/btVector3.h"

#include "raymath.h"


void Physics::Init()
{
    // WORLD
    broadphase = new btDbvtBroadphase();
    config     = new btDefaultCollisionConfiguration();
    dispatcher = new btCollisionDispatcher(config);
    solver     = new btSequentialImpulseConstraintSolver();
    world      = new btDiscreteDynamicsWorld(dispatcher, broadphase, solver, config);

    world->setGravity({0.f, -9.8f, 0.f});

    // GROUND
    groundShape  = new btStaticPlaneShape({0.f, 1.f, 0.f}, 0.f);
    groundMotion = new btDefaultMotionState(btTransform::getIdentity());
    btRigidBody::btRigidBodyConstructionInfo groundCI(0.f, groundMotion, groundShape);
    groundBody   = new btRigidBody(groundCI);

    world->addRigidBody(groundBody);

    // CHASSIS
    chassisShape = new btBoxShape({1.f, 0.5f, 2.f});

    btTransform startTransform;
    startTransform.setIdentity();
    startTransform.setOrigin({0.f, 0.5f, 0.f});

    btScalar  mass = 800.f;
    btVector3 inertia{0.f, 0.f, 0.f};
    chassisShape->calculateLocalInertia(mass, inertia);

    motion = new btDefaultMotionState(startTransform);
    btRigidBody::btRigidBodyConstructionInfo chassisCI(mass, motion, chassisShape, inertia);
    chassis = new btRigidBody(chassisCI);
    chassis->setActivationState(DISABLE_DEACTIVATION); // Машина без этого вырубается сама по себе и не едет

    world->addRigidBody(chassis);

    // VEHICLE SYSTEM
    btRaycastVehicle::btVehicleTuning tuning;
    raycaster = new btDefaultVehicleRaycaster(world);
    vehicle = new btRaycastVehicle(tuning, chassis, raycaster);

    vehicle->setCoordinateSystem(0, 1, 2);
    world->addVehicle(vehicle);

    float wheelRadius = 0.6f;
    float suspension = 0.8f;

    vehicle->addWheel(btVector3(1, 0.2, 2), btVector3(0,-1,0), btVector3(1,0,0), suspension, wheelRadius, tuning, true);
    vehicle->addWheel(btVector3(-1, 0.2, 2), btVector3(0,-1,0), btVector3(1,0,0), suspension, wheelRadius, tuning, true);
    vehicle->addWheel(btVector3(1, 0.2, -2), btVector3(0,-1,0), btVector3(1,0,0), suspension, wheelRadius, tuning, false);
    vehicle->addWheel(btVector3(-1, 0.2, -2), btVector3(0,-1,0), btVector3(1,0,0), suspension, wheelRadius, tuning, false);
    
    for (int i = 0; i < vehicle->getNumWheels(); ++i) {
        vehicle->getWheelInfo(i).m_suspensionStiffness = 40.f;
        vehicle->getWheelInfo(i).m_wheelsDampingRelaxation = 2.f;
        vehicle->getWheelInfo(i).m_wheelsDampingCompression = 4.f;
        vehicle->getWheelInfo(i).m_frictionSlip = 6.f; // сцепление с дорогой
        vehicle->getWheelInfo(i).m_rollInfluence = 0.05f; // поменьше чтоб машина не переворачивалась
        vehicle->getWheelInfo(i).m_maxSuspensionTravelCm = 500;
        vehicle->getWheelInfo(i).m_maxSuspensionForce = 6000.f;
    }
}

const float engineAccel = 5000.0f;
const float engineDecay = 3000.0f;

const float steerSpeed  = 1.f;
const float steerReturn = 2.f;

const float maxEngine = 5000.0f;
const float maxSteer  = 0.5f;

void Physics::Update(char forward, bool brake, char sideway, float dt)
{
    static float engine     = 0.f;
    static float steering   = 0.f;
    static float brakeForce = 0.f;

    // ДВИЖЕНИЕ
    if (forward)
        engine += forward * engineAccel * dt;
    else
    {
        // плавное затухание
        if (engine > 0)
            engine = fmaxf(0.0f, engine - engineDecay * dt);
        else
            engine = fminf(0.0f, engine + engineDecay * dt);
    }
    engine = Clamp(engine, -maxEngine, maxEngine);

    // ТОРМОЗ
    if (brake) { brakeForce = 100.f; }
    else       { brakeForce = 10.f; }

    // ПОВОРОТ
    if (sideway)
        steering += sideway * steerSpeed * dt;
    else
    {
        // возврат руля к центру
        if (steering > 0)
            steering = fmaxf(0.0f, steering - steerReturn * dt);
        else
            steering = fminf(0.0f, steering + steerReturn * dt);
    }
    steering = Clamp(steering, -maxSteer, maxSteer);

    // Ограничения
    float speed = vehicle->getCurrentSpeedKmHour();

    // Ограничение максимальной скорости
    if (speed > 120.f) { engine = 0; }

    // Стабилизация заноса
    btVector3 vel = chassis->getLinearVelocity();
    btVector3 f = chassis->getWorldTransform().getBasis().getColumn(2); // f - forward но уже занято имя
    btVector3 lateral = vel - f * vel.dot(f);
    chassis->applyCentralForce(-lateral * 2.0f);

    // Применение к машине
    vehicle->applyEngineForce(engine, 2);
    vehicle->applyEngineForce(engine, 3);

    vehicle->setBrake(brakeForce, 0);
    vehicle->setBrake(brakeForce, 1);
    vehicle->setBrake(brakeForce, 2);
    vehicle->setBrake(brakeForce, 3);

    vehicle->setSteeringValue(steering, 0);
    vehicle->setSteeringValue(steering, 1);

    world->stepSimulation(dt);
}

Transform3D Physics::GetVehicleTransform()
{
    auto t = vehicle->getChassisWorldTransform();
    Transform3D tr;

    auto o = t.getOrigin();
    tr.pos = { o.x(), o.y(), o.z() };

    auto r = t.getRotation();
    tr.rot = { r.x(), r.y(), r.z(), r.w() };

    return tr;
}

Physics::~Physics()
{
    delete groundShape;
    delete groundMotion;
    delete groundBody;

    delete chassisShape;
    delete motion;
    delete chassis;

    delete world;
    delete vehicle;

    delete raycaster;

    delete broadphase;
    delete config;
    delete dispatcher;
    delete solver;
}