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
    /// Leave imageSource empty to select entire image
    SpriteRenderShape(Rect2 rect, std::string path, Rect2 imageSource = Rect2(), float rotation = 0, Color color = Color(255,255,255));
    RenderShapeType getType() override;
    void applyTransform(const Transform& transform) override;

    [[nodiscard]] Rect2 rect() const;
    [[nodiscard]] float rotation() const;
    [[nodiscard]] std::string path() const;
    [[nodiscard]] Rect2 imageSource() const;
    [[nodiscard]] Color color() const;
private:
    Rect2 _rect;
    float _rotation;
    std::string _path;
    Rect2 _imageSource;
    Color _color;
    Vector2 _initialSize;
};


#endif //SPC_PROJECT_SPRITERENDERSHAPE_H
