//
// Created by conner on 11/2/2022.
//

#ifndef SPC_PROJECT_SPRITERENDERSHAPE_H
#define SPC_PROJECT_SPRITERENDERSHAPE_H

#include "RenderShape.h"
#include "../Rect2.h"
#include "../Color.h"

class SpriteRenderShape : public RenderShape {
public:
    /// \param path Path to the image (png or jpg)
    /// \param position Position at which the sprite should be drawn (center of image)
    /// \param rotation Angle of sprite in degrees
    /// \param pixelScale Amount of pixels in image used per 1 pixel on screen (value of 2 will half the image size on screen)
    /// \param imageSource Selection of image to render (default uses entire image (Rect2(Vector2(0,0), Vector2(0,0)))
    /// \param pivotPoint Custom pivot point in raw pixel value of point in image (default uses center of image (Vector2(0,0))
    /// \param color Color used to blend with image (default white with no effect)
    explicit SpriteRenderShape(std::string path, Vector2 position = Vector2(), float rotation = 0, Vector2 pixelScale = Vector2(1,1), Rect2 imageSource = Rect2(), Vector2 pivotPoint = Vector2(), Color color = Color(255,255,255));

    RenderShapeType getType() override;

    /// Applies a transform to the RenderShape properties
    /// \param transform Transform to be applied
    void applyTransform(const Transform& transform) override;

    [[nodiscard]] Vector2 position() const;
    [[nodiscard]] Vector2 pixelScale() const;
    [[nodiscard]] float rotation() const;
    [[nodiscard]] std::string path() const;
    [[nodiscard]] Rect2 imageSource() const;
    [[nodiscard]] Color color() const;
    [[nodiscard]] Vector2 pivotPoint() const;
private:
    Vector2 _position;
    Vector2 _pixelScale;
    float _rotation;
    std::string _path;
    Rect2 _imageSource;
    Color _color;
    Vector2 _initialPixelScale;
    Vector2 _pivotPoint;
};


#endif //SPC_PROJECT_SPRITERENDERSHAPE_H
