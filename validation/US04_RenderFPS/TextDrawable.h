//
// Created by Lucas on 17-11-2022.
//

#ifndef GOLFENGINE_TEXTDRAWABLE_H
#define GOLFENGINE_TEXTDRAWABLE_H


#include <memory>
#include "Scene/Components/Drawable.h"
#include "Scene/RenderShape/TextRenderShape.h"
#include "Scene/Rect2.h"

class TextDrawable : public Drawable {
public:
    TextDrawable(Vector2 pos, Transform transform ,std::string text, size_t fontSize, Color color,  std::string filePath);
    RenderShape* getRenderShape() override;

    void rotate(float amount);
    void move(int x, int y);
private:
    std::unique_ptr<TextRenderShape> _renderShape;
    Transform _transform;

};


#endif //GOLFENGINE_TEXTDRAWABLE_H
