//
// Created by jaaps on 02/11/2022.
//

#ifndef GOLFENGINE_BEHAVIOURSCRIPT_H
#define GOLFENGINE_BEHAVIOURSCRIPT_H
#include "Component.h"

class BehaviourScript : public Component {
public:
    virtual void onStart() override {};
    virtual void onUpdate() override {};
    virtual void onRemove() override {};
    virtual bool getActive() override {return _active;};
    virtual void setActive(bool active) override {_active = active;};
    void setParentGameObject(GameObject* gameObject) override {_gameObject = gameObject;};
};


#endif //GOLFENGINE_BEHAVIOURSCRIPT_H
