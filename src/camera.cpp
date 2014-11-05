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
        currentCamera = this;
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