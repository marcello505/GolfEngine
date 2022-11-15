//
// Created by Lucas on 15-11-2022.
//

#ifndef GOLFENGINE_TEXTRENDERSHAPE_H
#define GOLFENGINE_TEXTRENDERSHAPE_H


#include "RenderShape.h"
#include "../Color.h"

class TextRenderShape : public RenderShape {
public:
    TextRenderShape(Vector2 pos, std::string text,int fontSize, Color color);
    RenderShapeType getType() override;
    void applyTransform(const Transform& transform) override;

    // Getter
    [[nodiscard]] Vector2 position() const;
    [[nodiscard]] std::string text() const;
    [[nodiscard]] Color color() const;
private:
    Vector2 _position;
    std::string _text;
    Color _color;
};

#endif //GOLFENGINE_TEXTRENDERSHAPE_H
