#include <gtc/matrix_transform.hpp>
#include "camera.h"

// Declare currentCamera
Camera * Camera::currentCamera = NULL;
// Declare activeCameras
std::list<Camera*> Camera::activeCameras;

Camera::Camera()
{
    // Add to list of active cameras
    activeCameras.push_back(this);

    // If no camera is being used, use this one
    if(!currentCamera)
        use();
}
Camera::~Camera()
{
    // Remove from list of active cameras
    activeCameras.remove(this);
}

Camera * Camera::getCurrentCamera() { return currentCamera; }
Camera * Camera::use()
{
    // Make current camera
    currentCamera = this;

    // Return for chaining
    return this;
}

glm::mat4 Camera::getViewMatrix() { return viewMatrix; }

glm::vec3 Camera::move(glm::vec3 translation)
{
   // Move the world to effectively move camera
   translation *= -1;
   viewMatrix *= glm::translate(viewMatrix, translation);

   return Entity::move(translation);
}

glm::vec3 Camera::setPosition(glm::vec3 newPosition)
{
    // TODO: Check if this actually works. May need to generate new matrix
    for(int i = 0; i < newPosition.length(); i++)
        viewMatrix[i][i] = -(newPosition[i]);

    return Entity::setPosition(newPosition);
}
