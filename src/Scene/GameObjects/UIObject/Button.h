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
    Button(ButtonRenderShape* buttonRenderShape);


    bool interactable() const;
    RenderShape* getRenderShape() override;
    void onClick();

private:

    std::unique_ptr<ButtonRenderShape> _buttonRenderShape;
};


#endif //GOLFENGINE_BUTTON_H
