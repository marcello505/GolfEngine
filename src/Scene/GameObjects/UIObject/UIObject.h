//
// Created by Lucas on 2-11-2022.
//

#ifndef GOLFENGINE_UIOBJECT_H
#define GOLFENGINE_UIOBJECT_H
#include "../GameObject.h"
#include "Scene/Components/Drawable.h"

namespace GolfEngine::Scene::UI {
    class UIObject : public GameObject, public Components::Drawable {
    public:
        float _width;
        float _height;
        Vector2 _position;
    };
}


#endif //GOLFENGINE_UIOBJECT_H
