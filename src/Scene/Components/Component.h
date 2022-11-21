//
// Created by jaaps on 02/11/2022.
//

#ifndef GOLFENGINE_COMPONENT_H
#define GOLFENGINE_COMPONENT_H

#include "../GameObjects/GameObject.h"

// Forward declaration
class GameObject;

class Component {
protected:
    bool _active;
    GameObject* _gameObject;
public:
    virtual void onStart() = 0;
    virtual void onUpdate() = 0;
    virtual void onRemove() = 0;
    virtual bool getActive()  = 0;
    virtual void setActive(bool active) = 0;
    virtual void setParentGameObject(GameObject* gameObject) = 0;
    /// Function used in GameObject to copy another GameObject
    /// \return A copy of the component
    virtual Component* clone() const = 0;
};


#endif //GOLFENGINE_COMPONENT_H
