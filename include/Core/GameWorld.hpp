#ifndef CORE_GAMEWORLD_HPP
#define CORE_GAMEWORLD_HPP

#include "Core/ModelID.hpp"
#include "Core/Physics.hpp"
#include "Core/Input.hpp"
#include <Core/Car.hpp>
#include <Core/Track.hpp>
#include <memory>
#include <vector>
#include <span>

class GameWorld {
public:
    void Update(const Input& input, float dt);

    Car*   CreateCar(float x, float z, ModelID model_id); // Car* - наблюдатель, GameWorld владелец Cars
    void   DestroyCar(size_t idx);
    size_t GetNumCars() const;

    Track* CreateTrack(std::span<const CollisionMeshData> mesh_data, ModelID id);
    void   DestroyTrack();

private:
    Physics physic_world;
    Track   track;
    std::unique_ptr<Car> local_car;
    std::vector<std::unique_ptr<Car>> cars;
};

#endif