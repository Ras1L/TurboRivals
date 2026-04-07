#ifndef APP_APPLICATION_HPP
#define APP_APPLICATION_HPP

#include "Core/Car.hpp"
#include "Core/Physics.hpp"
#include "Render/CarCamera.hpp"
#include "Render/LevelRenderer.hpp"
#include "Render/ResourceManager.hpp"
#include "Render/CarRenderer.hpp"
#include "UI/InputManager.hpp"
#include "UI/Window.hpp"

class Application {
public:
    void exec();

private:
    Window        window;
    InputManager  input_manager;
    Physics       physics;
    Car           player;
    CarCamera     car_camera;
    CarRenderer   car_renderer;
    LevelRenderer level_renderer;

    ResourceManager res_manager;
};

#endif