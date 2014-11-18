#pragma once

#include "glm.hpp"

namespace GGE
{
    // Unit vector defines
    #define X_UNIT_VECTOR           glm::vec3(1.0, 0.0, 0.0)
    #define NEGATIVE_X_UNIT_VECTOR  glm::vec3(-1.0, 0.0, 0.0)
    #define Y_UNIT_VECTOR           glm::vec3(0.0, 1.0, 0.0)
    #define NEGATIVE_Y_UNIT_VECTOR  glm::vec3(0.0, -1.0, 0.0)
    #define Z_UNIT_VECTOR           glm::vec3(0.0, 0.0, 1.0)
    #define NEGATIVE_Z_UNIT_VECTOR  glm::vec3(0.0, 0.0, -1.0)
}