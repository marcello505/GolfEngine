//
// Created by marce on 02/11/2022.
//

#ifndef GOLFENGINE_GAMEOBJECT_H
#define GOLFENGINE_GAMEOBJECT_H
#include <string>
#include "C.h"
class GameObject {
private:
    bool _active;
public:
    std::string _name;
    std::string _tag;
    std::uint32_t _layer;
    bool recordable;
    /*void addComponent(Component component);*/
/*    template<> void addComponent<C>(Args...);
    template<> void getComponent<C>();*/
/*    void removeComponent(Component
    component);*/
    bool isActiveInWorld();
    bool isActiveSelf();
    bool getActive();
    void setActive(bool active);
    void onUpdate();

};


#endif //GOLFENGINE_GAMEOBJECT_H
