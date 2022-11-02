//
// Created by marce on 02/11/2022.
//

#ifndef GOLFENGINE_GAMEOBJECT_H
#define GOLFENGINE_GAMEOBJECT_H
#include <string>

//TODO replace this with include
class Component;

class GameObject {
private:
    bool _active;
public:
    std::string _name;
    std::string _tag;
    std::uint32_t _layer;
    bool recordable;
    void addComponent(Component component);
    template<typename C, typename ... args> void addComponent(args...);
    template<typename C> void getComponent();
    void removeComponent(Component component);
    bool isActiveInWorld();
    bool isActiveSelf();
    bool getActive();
    void setActive(bool active);
    void onUpdate();
};


#endif //GOLFENGINE_GAMEOBJECT_H
