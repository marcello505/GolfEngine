//
// Created by Lucas on 15-11-2022.
//

#ifndef GOLFENGINE_TEXTRENDERSHAPE_H
#define GOLFENGINE_TEXTRENDERSHAPE_H


#include "RenderShape.h"
#include "../Color.h"
#include <string>

namespace GolfEngine::Scene::Render {
    class TextRenderShape : public RenderShape {
    public:
        /// RenderShape used to render text
        /// \param pos position of text
        /// \param rotation rotation of text
        /// \param text text to render
        /// \param fontSize fontSize of text
        /// \param color color of text
        /// \param filePath path to font
        TextRenderShape(const Vector2 &pos, float rotation, std::string text, size_t fontSize,
                        const Color &color, std::string filePath);

        RenderShapeType getType() override;
        void applyTransform(const Transform &transform) override;
        void setText(const std::string &text);
        void setPosition(Vector2 pos);

        // Getter
        [[nodiscard]] Vector2 position() const;
        [[nodiscard]] float rotation() const;
        [[nodiscard]] std::string text() const;
        [[nodiscard]] Color color() const;
        [[nodiscard]] std::string filePath() const;
        [[nodiscard]] size_t fontSize() const;

    private:
        Vector2 _position;
        float _rotation;
        std::string _text;
        Color _color;
        std::string _filePath;
        size_t _fontSize;
        Vector2 _initialPosition;
    };
}

#endif //GOLFENGINE_TEXTRENDERSHAPE_H
