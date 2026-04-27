#ifndef UI_INPUTMANAGER_HPP
#define UI_INPUTMANAGER_HPP

#include "Core/Input.hpp"

class InputManager {
public:
    PlayerInput GetInput();

private:
    PlayerInput input;
};

#endif