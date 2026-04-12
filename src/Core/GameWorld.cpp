#include "Core/GameWorld.hpp"
#include "Core/Input.hpp"
#include "Core/ModelID.hpp"
#include "Core/Physics.hpp"
#include <memory>

void GameWorld::Update(Input input, float dt)
{
    for (auto it = cars.begin(); it != cars.end(); ++it) {
        it->get()->physic_model.Update(input, dt);
        it->get()->transform = it->get()->physic_model.GetVehicleTransform();
    }
    physic_world.Update(dt);
}

Car* GameWorld::CreateCar(float x, float z, ModelID model_id)
{
    auto car = std::make_unique<Car>();

    car->model_id = model_id;
    car->transform.pos = {x, 5.f, z};
    car->physic_model.Init(physic_world);

    Car* observer = car.get();

    cars.push_back(std::move(car));

    return observer;
}

void GameWorld::DestroyCar(size_t idx)
{
    cars[idx]->physic_model.Destroy(physic_world);
}

size_t GameWorld::GetNumCars() const
{
    return cars.size();
}