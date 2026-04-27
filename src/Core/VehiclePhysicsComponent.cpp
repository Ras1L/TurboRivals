#include "Core/VehiclePhysicsComponent.hpp"
#include "BulletCollision/CollisionShapes/btBoxShape.h"
#include "BulletCollision/CollisionShapes/btCompoundShape.h"
#include "BulletDynamics/Vehicle/btRaycastVehicle.h"

#include "LinearMath/btTransform.h"
#include "LinearMath/btVector3.h"
#include "raymath.h"
#include <memory>

const float engineAccel = 2500.0f;
const float engineDecay = 5000.0f;

const float steerSpeed  = 3.f;
const float steerReturn = 5.f;

const float maxEngine = 7000.0f;
const float maxSteer  = 0.3f;

void VehiclePhysicsComponent::Init(Vector3 pos, Physics& physic_world)
{
    // CHASSIS
    chassisShape = std::make_unique<btBoxShape>(btVector3{2.f, 0.2f, 4.f});
    
    btTransform startTransform;
    startTransform.setIdentity();
    startTransform.setOrigin({pos.x, pos.y, pos.z}); // где спавнится машина

    btScalar  mass = 1500.f;
    btVector3 inertia{0.f, 0.f, 0.f};
    chassisShape->calculateLocalInertia(mass, inertia);

    compound = std::make_unique<btCompoundShape>();

    btTransform localTransform;
    localTransform.setIdentity();
    localTransform.setOrigin({0.f, 1.5f, 0.f});

    compound->addChildShape(localTransform, chassisShape.get());

    motion = std::make_unique<btDefaultMotionState>(startTransform);
    btRigidBody::btRigidBodyConstructionInfo chassisCI(mass, motion.get(), chassisShape.get(), inertia);
    chassis = std::make_unique<btRigidBody>(chassisCI);
    chassis->setActivationState(DISABLE_DEACTIVATION); // Если это не выкл. короче машина вырубается сама по себе и не едет
    chassis->setDamping(0.05f, 0.2f);
    chassis->setFriction(0.2f);

    physic_world.addRigidBody(chassis.get());

    // VEHICLE SYSTEM
    btRaycastVehicle::btVehicleTuning tuning;
    raycaster = physic_world.createVehicleRaycaster();
    vehicle = std::make_unique<btRaycastVehicle>(tuning, chassis.get(), raycaster.get());

    vehicle->setCoordinateSystem(0, 1, 2);
    physic_world.addVehicle(vehicle.get());

    float wheelRadius = 0.2f;
    float suspension = 0.8f;

    vehicle->addWheel(btVector3(0.9f, 0.2f, 1.5f), btVector3(0.f,-1.f,0.f), btVector3(1.f,0.f,0.f), suspension, wheelRadius, tuning, true);
    vehicle->addWheel(btVector3(-0.9f, 0.2f, 1.5f), btVector3(0.f,-1.f,0.f), btVector3(1.f,0.f,0.f), suspension, wheelRadius, tuning, true);
    vehicle->addWheel(btVector3(0.9f, 0.2f, -1.5f), btVector3(0.f,-1.f,0.f), btVector3(1.f,0.f,0.f), suspension, wheelRadius, tuning, false);
    vehicle->addWheel(btVector3(-0.9f, 0.2f, -1.5f), btVector3(0.f,-1.f,0.f), btVector3(1.f,0.f,0.f), suspension, wheelRadius, tuning, false);
    
    for (int i = 0; i < vehicle->getNumWheels(); ++i) {
        vehicle->getWheelInfo(i).m_suspensionStiffness = 30.f;
        vehicle->getWheelInfo(i).m_wheelsDampingRelaxation = 6.f;
        vehicle->getWheelInfo(i).m_wheelsDampingCompression = 3.f;
        vehicle->getWheelInfo(i).m_frictionSlip = 6.f; // сцепление с дорогой
        vehicle->getWheelInfo(i).m_rollInfluence = 0.1f; // поменьше чтоб машина не переворачивалась
        vehicle->getWheelInfo(i).m_maxSuspensionTravelCm = 80.f;
        vehicle->getWheelInfo(i).m_maxSuspensionForce = 40000.f;
    }
}

void VehiclePhysicsComponent::Update(const VehicleInput& input, float dt)
{
    float speed = fabsf(vehicle->getCurrentSpeedKmHour());
    speed = Clamp(speed / 200.f, 0.f, 1.f);

    // ДВИЖЕНИЕ
    float rateEngine = 1.f - 0.75f * speed;
    if (input.forward)
        engine += input.forward * engineAccel * rateEngine * dt;
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
    if (input.brake) { brakeForce = 500.f; }
    else       { brakeForce = 0.f; }

    // ПОВОРОТ
    float rateSteer = 1.f - 0.65f * speed;
    float targetSteer = input.sideway * maxSteer * rateSteer;
    float rate = (targetSteer != 0.f) ? steerSpeed : steerReturn;
    steering += (targetSteer - steering) * rate * dt;

    // ВОЗВРАТ
    if (input.returnBack) {
        chassis->setWorldTransform(btTransform::getIdentity());
    }

    // Ограничение максимальной скорости
    if (speed > 200.f) { engine = 0.f; }

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