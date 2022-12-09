//
// Created by conner on 11/2/2022.
//

#ifndef SPC_PROJECT_RENDERSERVICE_H
#define SPC_PROJECT_RENDERSERVICE_H

#include "../../Scene/Components/Drawable.h"
#include "../../Scene/GameObjects/Camera.h"

class RenderService{
public:
    virtual void addDrawable(Drawable& drawable) = 0;
    virtual void removeDrawable(Drawable& drawable) = 0;
    virtual void render() = 0;
    virtual void setScreenSize(int width, int height) = 0;
    virtual void setFullScreen(bool fullScreen) = 0;
    [[nodiscard]] virtual std::optional<std::reference_wrapper<Camera>> getMainCamera() const = 0;
    virtual void setMainCamera(Camera& camera) = 0;
};


#endif //SPC_PROJECT_RENDERSERVICE_H
