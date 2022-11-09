//
// Created by marce on 02/11/2022.
//

#ifndef GOLFENGINE_GAMEOBJECT_H
#define GOLFENGINE_GAMEOBJECT_H
#include <string>
#include <vector>

#include "../Components/Component.h"

class GameObject {
private:
    bool _active;
    std::vector<GameObject> _gameObjects;
public:
    std::string name;
    std::string tag;
    std::uint32_t layer;
    bool recordable;
    void addComponent(Component component);
    template<typename C, typename ... args> void addComponent(args...);
    template<typename C> void getComponent() const;
    void removeComponent(Component component);
    bool isActiveInWorld() const;
    bool isActiveSelf() const;
    bool getActive() const;
    void setActive(bool active);
    void onUpdate();

    //Method to use for tree of gameObjects
    void addGameObject(const GameObject &gameObject);
    std::vector<GameObject>& getGameObjects();
};


#endif //GOLFENGINE_GAMEOBJECT_H
