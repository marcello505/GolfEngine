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
    /// @param imageSource Selection of image to render, give a Rect with size values 0 to select entire image
    explicit SpriteRenderShape(std::string path, Vector2 position = Vector2(), Vector2 pixelScale = Vector2(1,1), Rect2 imageSource = Rect2(), Vector2 pivotPointOffset = Vector2(), float rotation = 0, Color color = Color(255,255,255));
    RenderShapeType getType() override;
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
