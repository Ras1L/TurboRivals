#ifndef APP_APPLICATION_HPP
#define APP_APPLICATION_HPP

#include "App/SceneManager.hpp"
#include "App/ApplicationContext.hpp"
#include "UI/Window.hpp"

class Application {
public:
    void exec();

private:
    Window             window;
    SceneManager       scene_manager {context };
    ApplicationContext context;
};

#endif