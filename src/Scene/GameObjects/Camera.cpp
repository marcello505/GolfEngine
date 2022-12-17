//
// Created by conner on 12/8/2022.
//

#include "Camera.h"
#include "Services/Singletons/RenderSingleton.h"

Camera::Camera(Color backgroundColor) : _aspectWidth{0}, _aspectHeight{0}, _backgroundColor{backgroundColor}{
    // If this is the first camera created in the scene set it as main camera by default
    if(GolfEngine::Services::Render::hasService())
        if(!GolfEngine::Services::Render::getService()->getMainCamera())
            GolfEngine::Services::Render::getService()->setMainCamera(*this);
}

Camera::Camera(float aspectWidth, float aspectHeight, Color backgroundColor) : _aspectWidth{aspectWidth}, _aspectHeight{aspectHeight},
                                                                               _backgroundColor{backgroundColor}{
    // If this is the first camera created in the scene set it as main camera by default
    if(GolfEngine::Services::Render::hasService())
        if(!GolfEngine::Services::Render::getService()->getMainCamera())
            GolfEngine::Services::Render::getService()->setMainCamera(*this);
}

void Camera::setMainCamera(Camera& camera) {
    if(GolfEngine::Services::Render::hasService())
        GolfEngine::Services::Render::getService()->setMainCamera(camera);
}

std::optional<std::reference_wrapper<Camera>> Camera::getMainCamera() {
    if(GolfEngine::Services::Render::hasService())
        return GolfEngine::Services::Render::getService()->getMainCamera()->get();
    else
        return std::nullopt;
}

float Camera::aspectWidth() const {
    return _aspectWidth;
}

float Camera::aspectHeight() const {
    return _aspectHeight;
}

Color Camera::backgroundColor() const {
    return _backgroundColor;
}

Vector2 Camera::screenToWorldSpace(Vector2 screenPos) {
    if(GolfEngine::Services::Render::hasService()){
        return screenPos + GolfEngine::Services::Render::getService()->getCameraOffset();
    }

    throw std::runtime_error("World space requested without active RenderService");
}

Vector2 Camera::worldToScreenSpace(Vector2 worldPos) {
    if(GolfEngine::Services::Render::hasService()){
        return worldPos - GolfEngine::Services::Render::getService()->getCameraOffset();
    }

    throw std::runtime_error("Screen space requested without active RenderService");
}


