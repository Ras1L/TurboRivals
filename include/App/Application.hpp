#ifndef APP_APPLICATION_HPP
#define APP_APPLICATION_HPP

#include "Core/Body.hpp"
#include "Core/Physics.hpp"
#include "Render/CarCamera.hpp"
#include "Render/Level.hpp"
#include "UI/InputManager.hpp"
#include "UI/Window.hpp"

class Application {
public:
    void exec();

private:
    Window       window;
    Level        level;
    CarCamera    car_camera;
    InputManager input_manager;
    Physics      physics;
    Body         player;
};

#endif