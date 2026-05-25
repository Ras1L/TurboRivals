#ifndef UI_WINDOW_HPP
#define UI_WINDOW_HPP

constexpr int SCREEN_WIDTH  = 1920;
constexpr int SCREEN_HEIGHT = 1080;
constexpr int TARGET_FPS    = 60;

class Window {
public:
    void Create();
    void Close();
};

#endif