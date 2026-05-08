#ifndef CORE_GAMEWORLD_HPP
#define CORE_GAMEWORLD_HPP

#include "Core/GameWorldInitData.hpp"
#include "Core/Environment.hpp"
#include "Core/Physics.hpp"
#include "Core/Input.hpp"
#include "Core/Car.hpp"
#include "Core/Track.hpp"
#include "Core/Session.hpp"
#include <memory>
#include <vector>
#include <span>

class GameWorld {
public:
    void Init(const SessionState& session, const GameWorldInitData& init_data);
    void Update(const VehicleInput& input, float dt);

    std::vector<const Car*> GetCars()        const;
    const Track*            GetTrack()       const;
    const Environment*      GetEnvironment() const;

    void CreateCar(float x, float z, ModelID model_id, bool is_local); // Car* - наблюдатель, GameWorld владелец Cars
    void DestroyCar(size_t idx);

    void CreateTrack(std::span<const CollisionMeshData> mesh_data, ModelID id);
    void DestroyTrack();

    void CreateEnvironment(ModelID env);

private:
    Physics     physic_world;
    Track       track;
    Environment env;
    std::unique_ptr<Car> local_car;
    std::vector<std::unique_ptr<Car>> cars;
};

#endif