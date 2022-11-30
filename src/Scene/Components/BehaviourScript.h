//
// Created by jaaps on 02/11/2022.
//

#ifndef GOLFENGINE_BEHAVIOURSCRIPT_H
#define GOLFENGINE_BEHAVIOURSCRIPT_H

#include "Component.h"

class BehaviourScript : public Component {
public:
    ~BehaviourScript() override = default;
    virtual void onStart() override {}
    virtual void onUpdate() override {};
    virtual void onRemove() override {}
    virtual bool getActive() override { return _active; }
    virtual void setActive(bool active) override { _active = active; }
    void setParentGameObject(GameObject& gameObject) override { _gameObject = gameObject; }
    template<typename C>
    C& getParentGameObject() {return reinterpret_cast<C&>(_gameObject->get()); }
};


#endif //GOLFENGINE_BEHAVIOURSCRIPT_H
