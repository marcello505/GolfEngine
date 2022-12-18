//
// Created by jaaps on 02/11/2022.
//

#ifndef GOLFENGINE_BEHAVIOURSCRIPT_H
#define GOLFENGINE_BEHAVIOURSCRIPT_H

#include "Component.h"
#include "RigidBody.h"

class BehaviourScript : public Component {
public:
    ~BehaviourScript() override = default;
    void onStart() override {}
    void onUpdate() override {}
    void onRemove() override {}
    bool getActive() override { return _active; }
    void setActive(bool active) override { _active = active; }
    void setParentGameObject(GameObject& gameObject) override { _gameObject = gameObject; }
    template<typename C>
    C& getParentGameObject() {return dynamic_cast<C&>(_gameObject->get()); }
    virtual void onCollisionEnter(RigidBody& other) {}
    virtual void onCollisionExit(RigidBody& other) {}
    virtual void onAreaEnter(RigidBody& other) {}
    virtual void onAreaExit(RigidBody& other) {}
    std::unique_ptr<ISnapshot> saveSnapshot() override { return {};}
    void loadSnapshot(const ISnapshot& rawSnapshot) override {}
};


#endif //GOLFENGINE_BEHAVIOURSCRIPT_H
