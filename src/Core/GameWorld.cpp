#include "Core/GameWorld.hpp"
#include "Core/Input.hpp"
#include "Core/ModelID.hpp"
#include "Core/Physics.hpp"
#include <memory>

void GameWorld::Update(const Input& input, float dt)
{
    local_car.get()->vehicle_physics_comp.Update(input, dt);
    local_car.get()->model_comp.transform = local_car.get()->vehicle_physics_comp.GetVehicleTransform();

    Input null_input;
    null_input.returnBack = false;
    for (auto it = cars.begin(); it != cars.end(); ++it) {
        it->get()->vehicle_physics_comp.Update(null_input, dt);
        it->get()->model_comp.transform = it->get()->vehicle_physics_comp.GetVehicleTransform();
    }
    physic_world.Update(dt);
}

Car* GameWorld::CreateCar(float x, float z, ModelID model_id)
{
    auto car = std::make_unique<Car>();

    car->model_comp.mid = model_id;
    car->model_comp.transform.pos = {x, 2.f, z};
    car->vehicle_physics_comp.Init(car->model_comp.transform.pos, physic_world);

    Car* observer = car.get();

    if (!local_car) {
        local_car = std::move(car);
    } else {
        cars.push_back(std::move(car));
    }
    return observer;
}

void GameWorld::DestroyCar(size_t idx)
{
    cars[idx]->vehicle_physics_comp.Destroy(physic_world);
}

size_t GameWorld::GetNumCars() const
{
    return cars.size();
}

Track* GameWorld::CreateTrack(std::span<const CollisionMeshData> mesh_data, ModelID id)
{
    track.model_comp.mid = id;
    track.model_comp.transform.pos = {0.f, 0.f, 0.f};
    track.collision_comp.Init(mesh_data, physic_world);

    return &track;
}

void GameWorld::DestroyTrack()
{
    track.collision_comp.Destroy(physic_world);
}