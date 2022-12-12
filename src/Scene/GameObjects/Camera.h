//
// Created by conner on 11/2/2022.
//

#ifndef SPC_PROJECT_CAMERA_H
#define SPC_PROJECT_CAMERA_H

#include "GameObject.h"
#include "../Color.h"

class Camera : public GameObject {
public:
    /// Camera object controls what gets displayed on the screen. (First camera created in the scene will be the main camera by default.)
    /// \param aspectWidth width of the camera display
    /// \param aspectHeight height of the camera display
    /// \param backgroundColor color used on the background where no sprites are present
    Camera(float aspectWidth, float aspectHeight, float zoom = 1.0f, Color backgroundColor = Color{50, 50, 50, 255});

    /// Sets the main camera in the render service
    /// \param camera reference to the camera to be set
    static void setMainCamera(Camera& camera);

    /// Returns a reference to the current main camera if there is one present
    /// \return reference to current main camera
    static std::optional<std::reference_wrapper<Camera>> getMainCamera();

    /// Sets the zoom factor of the camera
    /// \param zoom Amount of zoom in percent. (1.0f is a standard zoom of 100%)
    void setZoom(float zoom);

    // Getters
    [[nodiscard]] float aspectWidth() const;
    [[nodiscard]] float aspectHeight() const;
    [[nodiscard]] Color backgroundColor() const;
    [[nodiscard]] float zoom() const;
private:
    Color _backgroundColor;
    float _aspectWidth;
    float _aspectHeight;
    float _zoom;
};


#endif //SPC_PROJECT_CAMERA_H
