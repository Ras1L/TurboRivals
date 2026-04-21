#include "Core/VehiclePhysicsComponent.hpp"
#include "BulletCollision/CollisionShapes/btBoxShape.h"
#include "BulletDynamics/Vehicle/btRaycastVehicle.h"

#include "LinearMath/btVector3.h"
#include "raymath.h"
#include <memory>

const float engineAccel = 5000.0f;
const float engineDecay = 3000.0f;

const float steerSpeed  = 1.f;
const float steerReturn = 2.f;

const float maxEngine = 7000.0f;
const float maxSteer  = 0.5f;

void VehiclePhysicsComponent::Init(Vector3 pos, Physics& physic_world)
{
    // CHASSIS
    chassisShape = std::make_unique<btBoxShape>(btVector3{1.f, 0.5f, 2.f});

    btTransform startTransform;
    startTransform.setIdentity();
    startTransform.setOrigin({pos.x, pos.y, pos.z});

    btScalar  mass = 1100.f;
    btVector3 inertia{0.f, 0.f, 0.f};
    chassisShape->calculateLocalInertia(mass, inertia);

    motion = std::make_unique<btDefaultMotionState>(startTransform);
    btRigidBody::btRigidBodyConstructionInfo chassisCI(mass, motion.get(), chassisShape.get(), inertia);
    chassis = std::make_unique<btRigidBody>(chassisCI);
    chassis->setActivationState(DISABLE_DEACTIVATION); // Если это не выкл. короче машина вырубается сама по себе и не едет

    physic_world.addRigidBody(chassis.get());

    // VEHICLE SYSTEM
    btRaycastVehicle::btVehicleTuning tuning;
    raycaster = physic_world.createVehicleRaycaster();
    vehicle = std::make_unique<btRaycastVehicle>(tuning, chassis.get(), raycaster.get());

    vehicle->setCoordinateSystem(0, 1, 2);
    physic_world.addVehicle(vehicle.get());

    float wheelRadius = 0.6f;
    float suspension = 0.8f;

    vehicle->addWheel(btVector3(1.f, 0.2f, 2.f), btVector3(0.f,-1.f,0.f), btVector3(1.f,0.f,0.f), suspension, wheelRadius, tuning, true);
    vehicle->addWheel(btVector3(-1.f, 0.2f, 2.f), btVector3(0.f,-1.f,0.f), btVector3(1.f,0.f,0.f), suspension, wheelRadius, tuning, true);
    vehicle->addWheel(btVector3(1.f, 0.2f, -2.f), btVector3(0.f,-1.f,0.f), btVector3(1.f,0.f,0.f), suspension, wheelRadius, tuning, false);
    vehicle->addWheel(btVector3(-1.f, 0.2f, -2.f), btVector3(0.f,-1.f,0.f), btVector3(1.f,0.f,0.f), suspension, wheelRadius, tuning, false);
    
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

void VehiclePhysicsComponent::Update(Input input, float dt)
{
    // ДВИЖЕНИЕ
    if (input.forward)
        engine += input.forward * engineAccel * dt;
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
    if (input.brake) { brakeForce = 100.f; }
    else       { brakeForce = 10.f; }

    // ПОВОРОТ
    if (input.sideway)
        steering += input.sideway * steerSpeed * dt;
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
    if (speed > 240.f) { engine = 0.f; }

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
}

Transform3D VehiclePhysicsComponent::GetVehicleTransform()
{
    auto t = vehicle->getChassisWorldTransform();
    Transform3D tr;

    auto o = t.getOrigin();
    tr.pos = { o.x(), o.y(), o.z() };

    auto r = t.getRotation();
    tr.rot = { r.x(), r.y(), r.z(), r.w() };

    return tr;
}

void VehiclePhysicsComponent::Destroy(Physics& physic_world)
{
    physic_world.removeVehicle(vehicle.get());
}