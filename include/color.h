#pragma once

#include "glm.hpp"

// This file defines a color typedef to be used for colors
// TODO: Clean this up
namespace GGE
{
    // RGBA Colors
    typedef glm::vec4 Color4;
    typedef glm::vec3 Color3;

    namespace Color
    {
        // Common color definitions
        static const Color4 RED = Color4(1.0f, 0.0f, 0.0f, 1.0f);
        static const Color4 BLUE = Color4(0.0f, 1.0f, 0.0f, 1.0f);
        static const Color4 GREEN = Color4(0.0f, 0.0f, 1.0f, 1.0f);
        static const Color4 WHITE = Color4(1.0f, 1.0f, 1.0f, 1.0f);
        static const Color4 BLACK = Color4(0.0f, 0.0f, 0.0f, 1.0f);
        static const Color4 NONE = Color4(0.0f, 0.0f, 0.0f, 0.0f);
        static const Color4 TRANSPARENT = NONE;
    }
}