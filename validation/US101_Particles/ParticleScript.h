//
// Created by Lucas on 28-11-2022.
//

#ifndef GOLFENGINE_PARTICLESCRIPT_H
#define GOLFENGINE_PARTICLESCRIPT_H


#include "Scene/Components/BehaviourScript.h"

class ParticleScript : public BehaviourScript{
public:
    virtual void onUpdate() override;

};


#endif //GOLFENGINE_PARTICLESCRIPT_H
