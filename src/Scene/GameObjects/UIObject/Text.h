//
// Created by Lucas on 2-11-2022.
//

#ifndef GOLFENGINE_TEXT_H
#define GOLFENGINE_TEXT_H


#include <string>
#include "Alignment.h"
#include "UIObject.h"
#include <Scene/RenderShape/TextRenderShape.h>
#include "../../Color.h"
#include <memory>

class Text : public UIObject {
public:
    /// Text object used to render text on screen
    /// \param pos position of text on screen
    /// \param rotation rotation of text on screen
    /// \param text starting text
    /// \param fontSize of text
    /// \param color of text
    /// \param filePath of font
    /// \param alignment of text
    /// \param isButtonPart is part of a button or not
    Text(Vector2 pos, float rotation, std::string text, size_t fontSize, Color color, std::string filePath,
         Alignment alignment, bool isButtonPart);
   ~Text() override;

    RenderShape& getRenderShape() override;
    Alignment _alignment;
    TextRenderShape _renderShape;
};


#endif //GOLFENGINE_TEXT_H
