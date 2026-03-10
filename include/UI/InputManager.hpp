#ifndef UI_INPUTMANAGER_HPP
#define UI_INPUTMANAGER_HPP

#include "UI/Input.hpp"

class InputManager {
public:
    Input GetInput();

private:
    Input input;
};

#endif