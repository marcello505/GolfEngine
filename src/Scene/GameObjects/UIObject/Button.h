//
// Created by Lucas on 2-11-2022.
//

#ifndef GOLFENGINE_BUTTON_H
#define GOLFENGINE_BUTTON_H

#include "UIObject.h"

class Button : public UIObject{
public:
    bool interactable() const;
    void onClick();
};


#endif //GOLFENGINE_BUTTON_H
