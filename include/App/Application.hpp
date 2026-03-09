#ifndef APP_APPLICATION_HPP
#define APP_APPLICATION_HPP

#include "Render/CarCamera.hpp"
#include "Render/Level.hpp"
#include "UI/Window.hpp"

class Application {
    Window window;
    Level level;
    CarCamera car_camera;

public:
    Application();
    void exec();
};

#endif