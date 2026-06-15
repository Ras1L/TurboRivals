#include "Core/GameWorld.hpp"
#include "Core/Environment.hpp"
#include "Core/ModelID.hpp"
#include "Core/Physics.hpp"
#include "Core/Session.hpp"
#include "raylib.h"

void GameWorld::Init(const SessionState& session, const GameWorldInitData& init_data)
{
    CreateTrack(init_data.track_col_mesh, session.track);
    CreateEnvironment(session.env);
    CreateCars(session.players, session.my_id);
}

void GameWorld::ApplyShapshot(const SessionStateRuntime& session)
{
    for (auto& player : session.players) {
        if (player.info.is_active) {
            auto& car = cars[player.info.id];
            car.vehicle_physics_comp.SetVehicleTransform(player.trans);
            car.model_comp.transform = car.vehicle_physics_comp.GetVehicleTransform();
        }
    }
}

void GameWorld::Update(SessionStateRuntime& session, float dt)
{
    for (auto& player : session.players) {
        if (player.info.is_active) {
            auto& car = cars[player.info.id];
            auto trans = car.vehicle_physics_comp.GetVehicleTransform();

            car.vehicle_physics_comp.Update(player.input, dt);
            car.model_comp.transform = trans;
            player.trans = trans;
        }
    }
    physic_world.Update(dt);
}

void GameWorld::CreateCars(std::span<const SessionPlayer> players, id_type local_car_id)
{
    for (auto& player : players) {
        if (player.is_active) {
            CreateCar(player, local_car_id);
        }
    }
}

void GameWorld::CreateCar(const SessionPlayer& player, id_type local_car_id)
{
    Car car;
    car.model_comp.mid = player.car;
    car.model_comp.transform.pos = player.spawn;
    car.vehicle_physics_comp.Init(car.model_comp.transform.pos, physic_world);

    cars[player.id] = std::move(car);

    if (local_car_id == player.id) {
        local_car = &cars[player.id];
    }
}

void GameWorld::DestroyCar(id_type id)
{
    cars[id].vehicle_physics_comp.Destroy(physic_world);
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

    for (id_type i = 0; i < MAX_PLAYERS; ++i) {
        auto& car = cars[i];
        if (car.vehicle_physics_comp.IsValid()) {
            all_cars.push_back(&car);
        }
    }
    return all_cars;
}

const Car* GameWorld::GetLocalCar() const
{
    return local_car;
}

const Track* GameWorld::GetTrack() const {
    return &track;
}

const Environment* GameWorld::GetEnvironment() const {
    return &env;
}