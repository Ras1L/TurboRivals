#ifndef CORE_MODELID_HPP
#define CORE_MODELID_HPP

#include <cstdint>

enum class ModelID : uint8_t {
    CAR__PORSCHE_911_CARRERA_993,
    CAR__DODGE_CHARGER_RT_1969,
    CAR__HORAI_BX300_1996,
    
    ENV__SNOW_MOUNTAINS,

    TRK__CIRCUIT8_BRIDGE,

    COUNT,

    NONE = 255
};

#endif