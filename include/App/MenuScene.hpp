#ifndef APP_MENU_SCENE_HPP
#define APP_MENU_SCENE_HPP

#include "App/IScene.hpp"
#include "Network/NetworkStatus.hpp"

struct GameConfig {
    NetworkStatus mode = NetworkStatus::OFFLINE;
    int  music = 0;
    int  track = 0;
    int  env   = 0;
    int  car   = 0;
    char server_ip[64] = "127.0.0.1";
};

class MenuScene : public IScene {
public:
    virtual void        Load()           override;
    virtual SceneSwitch Update(float dt) override;
    virtual void        Render() const   override;
    virtual void        Unload()         override;

private:
    mutable GameConfig config;
};

void DrawOwnerMenu(GameConfig& config);
void DrawClientMenu(GameConfig& config);

#endif