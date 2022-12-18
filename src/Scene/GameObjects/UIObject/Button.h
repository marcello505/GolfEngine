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
    ///
    /// \param width
    /// \param height
    /// \param position
    /// \param interactable
    /// \param onClickActionName
    /// \param textPosition
    /// \param textRotation
    /// \param textValue
    /// \param textFontSize
    /// \param textColor
    /// \param textFilePath
    /// \param textAlignment
    explicit Button(int width, int height, Vector2 position, bool interactable, std::string onClickActionName,
                    Vector2 textPosition, float textRotation, std::string textValue, size_t textFontSize, Color textColor,
                    std::string textFilePath, Alignment textAlignment);
    ~Button() override;

    /// Checks whether the button is interactable or not
    [[nodiscard]] bool interactable() const;

    // overrides
    RenderShape& getRenderShape() override;
    void onUpdate() override;

    /// Sets the button to clicked
    void onClick();

    /// Checks whether the button is clicked
    bool isClicked();

    struct {
        Vector2 position;
        float rotation;
        std::string value;
        size_t fontSize;
        Color color;
        std::string filePath;
        Alignment alignment;
    } _text;
private:
    bool _isClicked;
    bool _interactable;
    std::string _onClickActionName;
    void setShape();
    std::unique_ptr<ButtonRenderShape> _buttonRenderShape {};
};


#endif //GOLFENGINE_BUTTON_H
