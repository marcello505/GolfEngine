//
// Created by Lucas on 23-11-2022.
//

#ifndef GOLFENGINE_MOVEMENTSCRIPT_H
#define GOLFENGINE_MOVEMENTSCRIPT_H


#include "Scene/Components/BehaviourScript.h"

class MovementScript : public BehaviourScript{
    public:
        virtual void onUpdate() override;

};


#endif //GOLFENGINE_MOVEMENTSCRIPT_H
