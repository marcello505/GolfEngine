//
// Created by marce on 02/11/2022.
//

#ifndef GOLFENGINE_GAMEOBJECT_H
#define GOLFENGINE_GAMEOBJECT_H

#include <string>
#include <vector>
#include "../Components/Component.h"
#include "../Scene.h"

// Forward declaration
class Scene;

class GameObject {
private:
    bool _active;
    Scene* _scene;
    GameObject* _parent;
    std::vector<GameObject*> _children {};
public:
    std::string name;
    std::string tag;
    std::uint32_t layer;
    bool recordable;

public:
    explicit GameObject(Scene* scene, GameObject* parent = nullptr, const char* name = nullptr, const char* tag = nullptr);
    ~GameObject();
    template<typename C, typename ... args> void addComponent(args...);
    template<typename C> void getComponent() const;
    void removeComponent(Component& component);
    [[nodiscard]] bool isActiveInWorld() const;
    [[nodiscard]] bool isActiveSelf() const;
    [[nodiscard]] bool getActive() const;
    void setActive(bool active);
    void onUpdate();

    //Method to use for tree of gameObjects
    void addChild(GameObject *gameObject);
    std::vector<GameObject*>& children();
    GameObject* childAt(int index);
    [[nodiscard]] GameObject& parent() const;
};


#endif //GOLFENGINE_GAMEOBJECT_H
