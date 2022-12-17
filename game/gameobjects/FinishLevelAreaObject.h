//
// Created by marcello on 12/17/22.
//

#ifndef GOLFENGINE_FINISHLEVELAREAOBJECT_H
#define GOLFENGINE_FINISHLEVELAREAOBJECT_H


#include "Scene/GameObjects/GameObject.h"

#define TAG_FINISH "finish"

class FinishLevelAreaObject : public GameObject{
public:
    explicit FinishLevelAreaObject(const Vector2& position, const Vector2& extents);

};


#endif //GOLFENGINE_FINISHLEVELAREAOBJECT_H
