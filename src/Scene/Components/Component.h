//
// Created by jaaps on 02/11/2022.
//

#ifndef GOLFENGINE_COMPONENT_H
#define GOLFENGINE_COMPONENT_H

#include <optional>

#include "../IPersistable.h"
#include "../GameObjects/GameObject.h"

class GameObject;

//TODO uncomment the following line, after all the components have IPersistable implementations
class Component : public IPersistable{
protected:
    bool _active;
    std::optional<std::reference_wrapper<GameObject>> _gameObject;
public:
    virtual ~Component() = default;
    virtual void onStart() = 0;
    virtual void onUpdate() = 0;
    virtual void onRemove() = 0;
    virtual bool getActive()  = 0;
    virtual void setActive(bool active) = 0;
    virtual void setParentGameObject(GameObject& gameObject) = 0;
};


#endif //GOLFENGINE_COMPONENT_H
