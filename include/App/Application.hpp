#ifndef APP_APPLICATION_HPP
#define APP_APPLICATION_HPP

#include "Core/GameWorld.hpp"
#include "Network/NetworkManager.hpp"
#include "Render/CarCamera.hpp"
#include "Render/RenderSystem.hpp"
#include "Sound/SoundManager.hpp"
#include "UI/InputManager.hpp"
#include "UI/Window.hpp"

class Application {
public:
    void exec();

private:
    Window          window;
    InputManager    input_manager;
    CarCamera       car_camera;
    ResourceManager res_manager;
    NetworkManager  network;
    SoundManager    sound_manager;
    RenderSystem    render;

    GameWorld world;
};

#endif