#ifndef CORE_PLAYER_CONNECTION_DATA_MANAGER_HPP
#define CORE_PLAYER_CONNECTION_DATA_MANAGER_HPP

#include "Core/Session.hpp"
#include <vector>

struct PlayerConnectionData {
    mutable bool is_free;
    SessionPlayerConnection player;
};

class PlayerConnectionDataManager {
public:
    using player_data_type = SessionPlayerConnection;

    std::pair<bool, player_data_type> GetFreeConnectionData() const;
    void ReleaseConnectionData(player_data_type data);

private:
    const std::vector<PlayerConnectionData> players_data = { // явно укажу все, чем в рантайме лаконично заполнять этот вектор
        {true, {0, { -3.f, 2.f, 0.f}}},
        {true, {1, {3.f, 2.f, 0.f}}},
        {true, {2, {9.f, 2.f, 0.f}}},
        {true, {3, {1.f, 2.f, -7.f}}},
        {true, {4, {5.f, 2.f, -7.f}}},
        {true, {5, {-3.f, 2.f, -14.f}}},
        {true, {6, {3.f, 2.f, -14.f}}},
        {true, {7, {9.f, 2.f, -14.f}}}
    };
};

#endif