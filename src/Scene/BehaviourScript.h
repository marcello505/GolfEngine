//
// Created by jaaps on 02/11/2022.
//

#ifndef GOLFENGINE_BEHAVIOURSCRIPT_H
#define GOLFENGINE_BEHAVIOURSCRIPT_H
#include "Collider.h"

class BehaviourScript : public Collider {
public:
    virtual void onStart();
    virtual void onUpdate();
};


#endif //GOLFENGINE_BEHAVIOURSCRIPT_H