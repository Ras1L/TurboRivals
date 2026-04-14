#include "Core/GameWorld.hpp"
#include "Core/Input.hpp"
#include "Core/ModelID.hpp"
#include "Core/Physics.hpp"
#include <memory>

void GameWorld::Update(Input input, float dt)
{
    for (auto it = cars.begin(); it != cars.end(); ++it) {
        it->get()->vehicle_physics_comp.Update(input, dt);
        it->get()->model_comp.transform = it->get()->vehicle_physics_comp.GetVehicleTransform();
    }
    physic_world.Update(dt);
}

Car* GameWorld::CreateCar(float x, float z, ModelID model_id)
{
    auto car = std::make_unique<Car>();

    car->model_comp.mid = model_id;
    car->model_comp.transform.pos = {x, 5.f, z};
    car->vehicle_physics_comp.Init(car->model_comp.transform.pos, physic_world);

    Car* observer = car.get();

    cars.push_back(std::move(car));

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