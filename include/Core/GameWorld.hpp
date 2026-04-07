#ifndef CORE_GAMEWORLD_HPP
#define CORE_GAMEWORLD_HPP

#include <vector>
#include <Core/Car.hpp>

class GameWorld {
public:
    void Init();
    
private:
    std::vector<Car> cars;
};

#endif