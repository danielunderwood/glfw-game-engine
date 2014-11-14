#import "geometry.h"

namespace GGE
{
    // TODO: Template this
    glm::vec3 getAxisVector(AXIS a)
    {
        switch(a)
        {
            case NEGATIVE_X_UNIT:   return glm::vec3(-1.0, 0.0, 0.0);
            case X_UNIT:            return glm::vec3(1.0, 0.0, 0.0);
            case NEGATIVE_Y_UNIT:   return glm::vec3(0.0, -1.0, 0.0);
            case Y_UNIT:            return glm::vec3(0.0, 1.0, 0.0);
            case NEGATIVE_Z_UNIT:   return glm::vec3(0.0, 0.0, -1.0);
            case Z_UNIT:            return glm::vec3(0.0, 0.0, 1.0);
            default:                return glm::vec3(0.0, 0.0, 0.0); // YOU GET NOTHING
        }
    }
}