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
    Text(Vector2 pos, float rotation, std::string text, size_t fontSize, Color color, std::string filePath,
         Alignment alignment, bool isButtonPart);
    ~Text() override;

    RenderShape& getRenderShape() override;
    Alignment _alignment;
    TextRenderShape _renderShape;

};


#endif //GOLFENGINE_TEXT_H
