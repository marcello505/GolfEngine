//
// Created by Lucas on 12-12-2022.
//

#ifndef GOLFENGINE_ENEMYMOVEMENTSCRIPT_H
#define GOLFENGINE_ENEMYMOVEMENTSCRIPT_H


#include "Scene/Components/BehaviourScript.h"

class EnemyMovementScript : public BehaviourScript{
public:
    virtual void onUpdate() override;
};


#endif //GOLFENGINE_ENEMYMOVEMENTSCRIPT_H
