#pragma once

#import "glm.hpp"

namespace GGE
{
    // Enum for cartesian unit vectors
    typedef enum
    {
        X_UNIT;
        NEGATIVE_X_UNIT;

        Y_UNIT;
        NEGATIVE_Y_UNIT;

        Z_UNIT;
        NEGATIVE_Z_UNIT;

        // Number of axes since first is defined by 0
        NUM_AXES;
    } AXIS;

    // Get Vector of Axis
    glm::vec3 getAxisVector(AXIS a);
}