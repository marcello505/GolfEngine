//
// Created by conner on 11/2/2022.
//

#ifndef SPC_PROJECT_RENDERSERVICE_H
#define SPC_PROJECT_RENDERSERVICE_H

#include "../../Scene/Components/Drawable.h"
#include "../../Scene/GameObjects/Camera.h"


class RenderService {
public:
    virtual void setWindowTitle(const std::string& title) = 0;
    virtual void addDrawable(Drawable& drawable) = 0;
    virtual void removeDrawable(Drawable& drawable) = 0;
    virtual bool isRegistered(Drawable& drawable) = 0;
    virtual void render() = 0;

    virtual void setScreenSize(int width, int height) = 0;
    [[nodiscard]] virtual int getScreenSizeWidth() const = 0;
    [[nodiscard]] virtual int getScreenSizeHeight() const = 0;
    virtual Vector2 getCameraOffset() const = 0;
    virtual void setFullScreen(bool fullScreen) = 0;
    [[nodiscard]] virtual int screenSizeHeight() const = 0;
    [[nodiscard]] virtual int screenSizeWidth() const = 0;
    [[nodiscard]] virtual bool fullScreen() const = 0;
    [[nodiscard]] virtual std::optional<std::reference_wrapper<Camera>> getMainCamera() const = 0;
    virtual void setMainCamera(const std::optional<std::reference_wrapper<Camera>>& camera) = 0;

    // Virtual Destructors
    virtual ~RenderService() = default;
};
#endif //SPC_PROJECT_RENDERSERVICE_H
