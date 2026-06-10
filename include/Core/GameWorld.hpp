#ifndef CORE_GAMEWORLD_HPP
#define CORE_GAMEWORLD_HPP

#include "Core/GameWorldInitData.hpp"
#include "Core/Environment.hpp"
#include "Core/Physics.hpp"
#include "Core/Car.hpp"
#include "Core/Track.hpp"
#include "Core/Session.hpp"
#include <vector>
#include <span>

class GameWorld {
public:
    void Init(const SessionState& session, const GameWorldInitData& init_data);
    void Update(const SessionStateRuntime& session, float dt);
    void ApplyShapshot(const SessionStateRuntime& session);

    std::vector<const Car*> GetCars()        const; // для рендера, это не тот же самый вектор cars
    const Car*              GetLocalCar()    const;
    const Track*            GetTrack()       const;
    const Environment*      GetEnvironment() const;

    void CreateCars(std::span<const SessionPlayer> players, id_type local_car_id);
    void CreateCar(const SessionPlayer& player, id_type local_car_id); // Car* - наблюдатель, GameWorld владелец Cars
    void DestroyCar(uint8_t id);

    void CreateTrack(std::span<const CollisionMeshData> mesh_data, ModelID id);
    void DestroyTrack();

    void CreateEnvironment(ModelID env);

private:
    Physics     physic_world;
    Track       track;
    Environment env;
    const Car*  local_car;
    std::vector<Car> cars{ MAX_PLAYERS };
};

#endif