#include "shape.h"

namespace GGE
{
    Shape::Shape(CoordinateSet * coordinates, Material * material) :
            coordinates(coordinates),
            material(material)
    {}

    Shape::~Shape()
    {
    }
}