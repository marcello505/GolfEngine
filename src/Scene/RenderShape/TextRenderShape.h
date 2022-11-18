//
// Created by Lucas on 15-11-2022.
//

#ifndef GOLFENGINE_TEXTRENDERSHAPE_H
#define GOLFENGINE_TEXTRENDERSHAPE_H


#include "RenderShape.h"
#include "../Color.h"

class TextRenderShape : public RenderShape {
public:
    TextRenderShape(Vector2 pos, float rotation, std::string text, size_t fontSize, Color color, std::string filePath);
    RenderShapeType getType() override;
    void applyTransform(const Transform& transform) override;
    void setText(std::string &text) ;

    // Getter
    [[nodiscard]] Vector2 position() const;
    [[nodiscard]] float rotation() const;
    [[nodiscard]] std::string text() const;
    [[nodiscard]] Color color() const;
    [[nodiscard]] std::string filePath() const;
    [[nodiscard]] size_t fontSize() const;

    int scale();

private:
    Vector2 _position;
    float _rotation;
    std::string _text;
    Color _color;
    std::string _filePath;
    size_t _fontSize;
    Vector2 _initialPosition;
};

#endif //GOLFENGINE_TEXTRENDERSHAPE_H
