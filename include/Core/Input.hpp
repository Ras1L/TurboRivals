#ifndef UI_INPUT_HPP
#define UI_INPUT_HPP

#include <string>

struct VehicleInput {
    char forward;
    bool brake;
    char sideway;

    bool returnBack;
};

struct CameraInput {
    bool cameraLookBack;
    char cameraRight;
};

struct ConsoleInput {
    std::string command;
};

struct PlayerInput {
    VehicleInput vehicle;
    CameraInput  camera;
};

#endif