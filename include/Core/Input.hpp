#ifndef UI_INPUT_HPP
#define UI_INPUT_HPP

struct Input {
    char forward;
    bool brake;
    char sideway;

    bool returnBack;

    bool cameraLookBack;
    char cameraRight;
};

#endif