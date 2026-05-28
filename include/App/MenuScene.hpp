#ifndef APP_MENU_SCENE_HPP
#define APP_MENU_SCENE_HPP

#include "App/IScene.hpp"
#include "Core/Log.hpp"
#include "Network/NetworkManager.hpp"
#include "Network/NetworkRole.hpp"

enum class MenuMode : uint8_t {
    MAIN,
    LOBBY
};

struct GameConfig {
    NetworkRole mode = NetworkRole::OFFLINE;
    int  track = 0;
    int  env   = 0;
    int  car   = 0;
    char server_ip[64] = "127.0.0.1";
};

class MenuScene : public IScene {
public:
    MenuScene(NetworkManager& network);

    virtual void        Load()           override;
    virtual SceneSwitch Update(float dt) override;
    virtual void        Render() const   override;
    virtual void        Unload()         override;

private:
    void DrawMain() const;
    void DrawLobby() const;

    void DrawOwnerMenu(GameConfig& config) const;
    void DrawClientMenu(GameConfig& config) const;

    void SwitchToLobby() const;
    void SwitchToGame() const;

private:
    mutable MenuMode   mode = MenuMode::MAIN;
    mutable GameConfig config;

    NetworkManager&    network;
    SessionState       session;

    mutable Log log;
};

#endif