#include "Core/GameWorld.hpp"
#include "Core/Environment.hpp"
#include "Core/ModelID.hpp"
#include "Core/Physics.hpp"
#include "Core/Session.hpp"
#include "raylib.h"
#include <memory>

void GameWorld::Init(const SessionState& session, const GameWorldInitData& init_data)
{
    CreateTrack(init_data.track_col_mesh, session.track);
    CreateEnvironment(session.env);
    CreateCars(session.players, session.my_id);
}

void GameWorld::Update(const SessionStateRuntime& session, float dt) // TODO: здесь world из network должен получить пакеты об инпуте остальных игроков
{
    for (auto& player : session.players) {
        auto id = player.info.id;
        if (session.my_id == id)
        {
            auto my_car = local_car.get();
            my_car -> vehicle_physics_comp.Update(player.input, dt);
            my_car -> model_comp.transform = my_car -> vehicle_physics_comp.GetVehicleTransform(); // TODO: стоит ли вообще
        }
        else
        {
            auto car = cars[id].get();
            car -> vehicle_physics_comp.Update(player.input, dt);
            car -> model_comp.transform = car -> vehicle_physics_comp.GetVehicleTransform();
        }
    }
    physic_world.Update(dt);
}

void GameWorld::ApplyShapshot(const SessionStateRuntime& session) // TODO
{

}

void GameWorld::CreateCars(std::span<const SessionPlayer> players, id_type local_car_id)
{
    cars.reserve(MAX_PLAYERS);
    for (auto& player : players) {
        if (player.is_active) {
            CreateCar(player.spawn, player.car, player.id == local_car_id);
        }
    }
}

void GameWorld::CreateCar(Vector3 pos, ModelID model_id, bool is_local)
{
    auto car = std::make_unique<Car>();

    car->model_comp.mid = model_id;
    car->model_comp.transform.pos = pos;
    car->vehicle_physics_comp.Init(car->model_comp.transform.pos, physic_world);

    if (is_local) { // TODO: сравнить id с id игрока
        local_car = std::move(car);
    } else {
        cars.push_back(std::move(car));
    }
}

void GameWorld::DestroyCar(id_type id)
{
    cars[id]->vehicle_physics_comp.Destroy(physic_world);
}

void GameWorld::CreateTrack(std::span<const CollisionMeshData> mesh_data, ModelID mid)
{
    track.model_comp.mid = mid;
    track.model_comp.transform.pos = {0.f, 0.f, 0.f};
    track.collision_comp.Init(mesh_data, physic_world);
}

void GameWorld::DestroyTrack()
{
    track.collision_comp.Destroy(physic_world);
}

void GameWorld::CreateEnvironment(ModelID mid) {
    env = {{mid}};
}

std::vector<const Car*> GameWorld::GetCars() const
{
    std::vector<const Car*> all_cars;
    all_cars.reserve(MAX_PLAYERS);

    all_cars.push_back(local_car.get());
    for (auto& car : cars) {
        all_cars.push_back(car.get());
    }
    return all_cars;
}

const Track* GameWorld::GetTrack() const {
    return &track;
}

const Environment* GameWorld::GetEnvironment() const {
    return &env;
}