//
// Created by Lucas on 2-11-2022.
//

#ifndef GOLFENGINE_BUTTON_H
#define GOLFENGINE_BUTTON_H

#include "UIObject.h"
#include "Scene/RenderShape/ButtonRenderShape.h"
#include <memory>


class Button : public UIObject{

public:
    Button(int width, int height, Vector2 position, bool interactable);
    void setShape(ButtonRenderShape* buttonRenderShape);

    bool interactable() const;
    RenderShape* getRenderShape() override;
    void onClick();

private:
    bool _interactable;
    std::unique_ptr<ButtonRenderShape> _buttonRenderShape;
};


#endif //GOLFENGINE_BUTTON_H
