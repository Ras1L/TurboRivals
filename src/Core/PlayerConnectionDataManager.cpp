#include "Core/PlayerConnectionDataManager.hpp"
#include "Core/Session.hpp"

std::pair<bool, PlayerConnectionDataManager::player_data_type>
PlayerConnectionDataManager::GetFreeConnectionData() const
{
    std::pair<bool, player_data_type> p;
    for (auto& player_data : players_data) {
        if (player_data.is_free) {
            player_data.is_free = false;
            p.first = true;
            p.second = player_data.player;
            return p;
        }
    }
    p.first = false;
    p.second = {0, {0.f, 0.f, 0.f}};
    return p;
}

void PlayerConnectionDataManager::ReleaseConnectionData(player_data_type data)
{
    for (auto& player_data : players_data) {
        if (player_data.player.id == data.id) {
            player_data.is_free = true;
        }
    }
}