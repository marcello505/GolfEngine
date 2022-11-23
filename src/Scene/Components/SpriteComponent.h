//
// Created by conner on 02/11/2022.
//

#ifndef GOLFENGINE_SPRITE_H
#define GOLFENGINE_SPRITE_H

#include <string>
#include "../Color.h"
#include "../Rect2.h"
#include "Component.h"
#include "Drawable.h"
#include "../RenderShape/SpriteRenderShape.h"

class SpriteComponent : public Component, public Drawable {
public:
    /// A Sprite component renders an sprite on the screen
    /// \param path Path to the image (png or jpg)
    /// \param pixelScale Amount of pixels in image used per 1 pixel on screen (value of 2 will half the image size on screen)
    /// \param imageSource Selection of image to render (default uses entire image (Rect2(Vector2(0,0), Vector2(0,0)))
    /// \param offsetPosition A starting value to offset the sprite position
    /// \param startingRotation A starting rotation applied to the sprite
    /// \param pivotPoint Custom pivot point in raw pixel value of point in image (default uses center of image (Vector2(0,0))
    /// \param color Color used to blend with image (default white with no effect)
    explicit SpriteComponent(const std::string& path, Vector2 pixelScale = Vector2(1,1), Rect2 imageSource = Rect2(), Vector2 offsetPosition = Vector2(), float startingRotation = 0, Vector2 pivotPoint = Vector2(), Color color = Color());

    // Component overrides
    void onStart() override;
    void onUpdate() override;
    void onRemove() override;
    bool getActive() override;
    void setActive(bool active) override;
    void setParentGameObject(GameObject &gameObject) override;

    // Drawable override
    RenderShape& getRenderShape() override;

    // Getters
    [[nodiscard]] std::string path() const;
    [[nodiscard]] Rect2 imageSource() const;
    [[nodiscard]] Color color() const;

    // Setters
    void setPath(const std::string& path);
    void setImageSource(Rect2 imageSource);
    void setColor(Color color);

private:
    SpriteRenderShape _renderShape;
    int _sortingLayer;
    int _orderInLayer;
};


#endif //GOLFENGINE_SPRITE_H
