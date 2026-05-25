#include "Core/GameWorld.hpp"
#include "Core/Environment.hpp"
#include "Core/Input.hpp"
#include "Core/ModelID.hpp"
#include "Core/Physics.hpp"
#include <memory>

const size_t MAX_PLAYERS_CNT = 8;

void GameWorld::Init(const SessionState& session, const GameWorldInitData& init_data)
{
    CreateTrack(init_data.track_col_mesh, session.track);
    CreateEnvironment(session.env);
    cars.reserve(MAX_PLAYERS_CNT);
    for (auto& player : session.players) {
        CreateCar(player.spawn.x, player.spawn.z, player.car, player.id == 0);
    }
}

void GameWorld::Update(const VehicleInput& input, float dt) // TODO: здесь world из network должен получить пакеты об инпуте остальных игроков
{
    local_car.get()->vehicle_physics_comp.Update(input, dt);
    local_car.get()->model_comp.transform = local_car.get()->vehicle_physics_comp.GetVehicleTransform();

    VehicleInput null_input;
    null_input.returnBack = false;
    for (auto it = cars.begin(); it != cars.end(); ++it) {
        it->get()->vehicle_physics_comp.Update(null_input, dt);
        it->get()->model_comp.transform = it->get()->vehicle_physics_comp.GetVehicleTransform();
    }
    physic_world.Update(dt);
}

void GameWorld::CreateCar(float x, float z, ModelID model_id, bool is_local)
{
    auto car = std::make_unique<Car>();

    car->model_comp.mid = model_id;
    car->model_comp.transform.pos = {x, 2.f, z};
    car->vehicle_physics_comp.Init(car->model_comp.transform.pos, physic_world);

    if (is_local) {
        local_car = std::move(car);
    } else {
        cars.push_back(std::move(car));
    }
}

void GameWorld::DestroyCar(size_t idx)
{
    cars[idx]->vehicle_physics_comp.Destroy(physic_world);
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