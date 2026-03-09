#ifndef UI_WINDOW_HPP
#define UI_WINDOW_HPP

const int SCREEN_WIDTH  = 1920;
const int SCREEN_HEIGHT = 1080;
const int TARGET_FPS    = 60;

class Window {
public:
    void create();
    void close();
};

#endif