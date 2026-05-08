#ifndef APP_MENU_SCENE_HPP
#define APP_MENU_SCENE_HPP

#include "App/IScene.hpp"

class MenuScene : public IScene {
public:
    virtual void Load() override;
    virtual void Update(float dt) override;
    virtual void Render() const override;
    virtual void Unload() override;
};

#endif