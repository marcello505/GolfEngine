//
// Created by conner on 11/2/2022.
//

#ifndef SPC_PROJECT_RENDERSERVICE_H
#define SPC_PROJECT_RENDERSERVICE_H

// TODO replace with include
//#include "../../Scene/Drawable.h"
class Drawable;

class RenderService{
public:
    virtual void addDrawable(const Drawable& drawable);
    virtual void removeDrawable(const Drawable& drawable) = 0;
    virtual void render() = 0;
    virtual void setScreenSize(int width, int height) = 0;
};


#endif //SPC_PROJECT_RENDERSERVICE_H
