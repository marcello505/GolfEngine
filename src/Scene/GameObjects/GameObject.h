//
// Created by marce on 02/11/2022.
//

#ifndef GOLFENGINE_GAMEOBJECT_H
#define GOLFENGINE_GAMEOBJECT_H

#include <string>
#include <vector>
#include "../Components/Component.h"
#include "../Scene.h"
#include <algorithm>

// Forward declaration
class Scene;
class Component;

class GameObject {
private:
    bool _active;
    GameObject* _parent;
    std::vector<std::unique_ptr<GameObject>> _children;
    std::vector<Component*>* _components;
public:
    std::string name;
    std::string tag;
    std::uint32_t layer;
    bool recordable;

public:
    /// GameObject constructor
    /// \param scene The scene the GameObject belongs to, if nullptr this object will be seen as a prefab and developer is responsible for its deletion
    /// \param parent The parent of the GameObject (when nullptr, root GameObject of scene will become partner)
    /// \param name The name of the GameObject (nullptr is results in "")
    /// \param tag The tag of the GameObject (nullptr results in "default")
    explicit GameObject(GameObject* parent = nullptr, const char* name = nullptr, const char* tag = nullptr);
    ~GameObject();
    explicit GameObject(const GameObject& other);
    GameObject& operator=(const GameObject& other);
    explicit GameObject(GameObject&& other) = delete;
    GameObject& operator=(GameObject&& other) = delete;

    /// Function creates a new Component for the GameObject
    /// \tparam C Component to create
    /// \tparam Args Arguments needed for constructor of C
    /// \return A reference to newly created component
    template<typename C, typename ... Args>
    C* addComponent(Args... args) {
        auto* newComp = _components->emplace_back(new C(std::forward<Args>(args)...));
        newComp->setParentGameObject(this);
        return reinterpret_cast<C*>(newComp);
    };

    /// Function retrieves a reference to a component of type C
    /// \tparam C Component to retrieve
    /// \return A reference to the found component, or nullptr when component is not found
    template<typename C>
    C* getComponent() const {
        if(!_components->empty()){
            for(auto* comp : *_components){
                // Try to cast to desired component
                auto castedComp = dynamic_cast<C*>(comp);
                // Return if cast was successful
                if(castedComp)
                    return castedComp;
            }
        }
        return nullptr;
    };

    /// Removes component from GameObject
    /// \param component a reference to the component that needs to be removed
    void removeComponent(Component& component);

    [[nodiscard]] bool isActiveInWorld() const;
    [[nodiscard]] bool isActiveSelf() const;
    [[nodiscard]] bool getActive() const;
    void setActive(bool active);
    void onStart();
    void onUpdate();

    GameObject* createChildGameObject(GameObject& gameObject);
    GameObject* createChildGameObject(GameObject* gameObject);
    std::vector<std::unique_ptr<GameObject>>& children();
    GameObject* childAt(int index);
    [[nodiscard]] GameObject& parent() const;
};


#endif //GOLFENGINE_GAMEOBJECT_H
