#ifndef CORE_GAMEWORLD_HPP
#define CORE_GAMEWORLD_HPP

#include "Core/ModelID.hpp"
#include "Core/Physics.hpp"
#include "Core/Input.hpp"
#include <memory>
#include <vector>
#include <Core/Car.hpp>

class GameWorld {
public:
    void Update(Input input, float dt);

    Car* CreateCar(float x, float z, ModelID model_id); // Car* - наблюдатель, GameWorld владелец Cars
    void DestroyCar(size_t idx);
    size_t GetNumCars() const;

private:
    Physics physic_world;
    std::vector<std::unique_ptr<Car>> cars;
};

#endif