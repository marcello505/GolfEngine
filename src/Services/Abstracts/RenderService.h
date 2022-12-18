//
// Created by conner on 11/2/2022.
//

#ifndef SPC_PROJECT_RENDERSERVICE_H
#define SPC_PROJECT_RENDERSERVICE_H

#include "../../Scene/Components/Drawable.h"
#include "../../Scene/GameObjects/Camera.h"


class RenderService {
public:
    /// Sets the title of the window
    /// \param title new title of window
    virtual void setWindowTitle(const std::string& title) = 0;

    /// Adds a drawable to the list of registered drawables
    /// \param drawable to be added
    virtual void addDrawable(Drawable& drawable) = 0;

    /// Removes a drawable from the list of registered drawables
    /// \param drawable to be removed
    virtual void removeDrawable(Drawable& drawable) = 0;

    /// Checks whether a drawable is registered
    /// \param drawable to be checked
    /// \return True if it is registered
    virtual bool isRegistered(Drawable& drawable) = 0;

    /// Renders all drawables in registered drawable list
    virtual void render() = 0;

    /// Sets the window size to the given sizes
    /// \param width new width of window
    /// \param height new height of window
    virtual void setScreenSize(int width, int height) = 0;

    /// Sets the window to fullscreen
    /// \param fullScreen true is fullscreen
    virtual void setFullScreen(bool fullScreen) = 0;

    /// Gets the current registered Camera
    /// \return A reference to the currently registered Camera
    [[nodiscard]] virtual std::optional<std::reference_wrapper<Camera>> getMainCamera() const = 0;

    /// Registers a camera to be used in the scene
    /// \param camera reference to camera, can be null to clear any camera
    virtual void setMainCamera(const std::optional<std::reference_wrapper<Camera>>& camera) = 0;

    /// Gets the offset created by the currently registered camera
    /// \return Vector2 of main camera offset
    [[nodiscard]] virtual Vector2 getCameraOffset() const = 0;

    /// Gets the screen size height
    /// \return Height of window in pixels
    [[nodiscard]] virtual int screenSizeHeight() const = 0;

    /// Gets the screen size width
    /// \return Width of window in pixels
    [[nodiscard]] virtual int screenSizeWidth() const = 0;

    /// Is the window in fullscreen mode
    /// \return true if window is in fullscreen mode
    [[nodiscard]] virtual bool fullScreen() const = 0;

    // Virtual Destructors
    virtual ~RenderService() = default;
};
#endif //SPC_PROJECT_RENDERSERVICE_H
