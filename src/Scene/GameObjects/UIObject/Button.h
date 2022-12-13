//
// Created by Lucas on 2-11-2022.
//

#ifndef GOLFENGINE_BUTTON_H
#define GOLFENGINE_BUTTON_H

#include "UIObject.h"
#include "Scene/RenderShape/ButtonRenderShape.h"
#include "Text.h"
#include <memory>


class Button : public UIObject{

public:
    explicit Button(int width, int height, Vector2 position, bool interactable, Text *text, std::string onClickActionName);
    ~Button() override;

    bool interactable() const;
    RenderShape& getRenderShape() override;
    void onUpdate() override;
    void onClick();
    bool isClicked();
    Text* _text;
private:
    bool _isClicked;
    bool _interactable;
    std::string _onClickActionName;
    void setShape();
    std::unique_ptr<ButtonRenderShape> _buttonRenderShape {};
};


#endif //GOLFENGINE_BUTTON_H
