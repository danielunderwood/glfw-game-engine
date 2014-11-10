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

glm::vec4 Camera::move(glm::vec4 translation)
{
   // Move the world to effectively move camera
   translation *= -1;
   viewMatrix *= translation;

   return Entity::move(translation);
}

glm::vec4 Camera::setPosition(glm::vec4 newPosition)
{
    for(int i = 0; i < newPosition.length(); i++)
        viewMatrix[i][i] = -(newPosition[i]);

    return Entity::setPosition(newPosition);
}
