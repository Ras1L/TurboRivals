#ifndef APP_ISCENE_HPP
#define APP_ISCENE_HPP

#include "App/SceneSwitch.hpp"

class IScene {
public:
    virtual void        Load()           = 0;
    virtual SceneSwitch Update(float dt) = 0;
    virtual void        Render() const   = 0;
    virtual void        Unload()         = 0;

    virtual ~IScene() = default;

protected:
    mutable bool should_switch = false;
    mutable Scene next_scene;
};

#endif