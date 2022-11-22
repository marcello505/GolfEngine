//
// Created by conner on 11/21/2022.
//

#ifndef GOLFENGINE_GAMEOBJECT_H
#define GOLFENGINE_GAMEOBJECT_H

#include <memory>
#include <optional>
#include <string>
#include <vector>
#include "../Transform.h"
#include "../Components/Component.h"
#include <algorithm>
#include <stdexcept>

// Forward declaration
class Component;

class GameObject {
protected:
    bool _active;
    std::unique_ptr<std::reference_wrapper<GameObject>> _parent;
    std::vector<std::reference_wrapper<GameObject>> _children;
    std::vector<std::unique_ptr<Component>> _components;
    Transform _localTransform {};
public:
    std::string name;
    std::string tag;
    std::uint32_t layer;
    bool recordable;

public:
    /// GameObject constructor
    /// \param name The name of the GameObject (nullptr is results in "")
    /// \param tag The tag of the GameObject (nullptr results in "default")
    GameObject(const char* name = nullptr, const char* tag = nullptr);
    ~GameObject();

    /// Function creates a new Component for the GameObject
    /// \tparam C Component to create
    /// \tparam Args Arguments needed for constructor of C
    /// \return A reference to newly created component
    template<typename C, typename ... Args>
    C& addComponent(Args... args) {
        C& newComp = reinterpret_cast<C&>(*_components.emplace_back(std::make_unique<C>(args...)));
        newComp.setParentGameObject(*this);
        return newComp;
    };

    /// Function retrieves a reference to a component of type C
    /// \tparam C Component to retrieve
    /// \return A reference to the found component, or nullptr when component is not found
    template<typename C>
    C& getComponent() const {
        if(!_components.empty()){
            for(auto& comp : _components){
                // Try to cast to desired component
                auto* castedComp = reinterpret_cast<C*>(comp.get());
                // Return if cast was successful
                if(castedComp)
                    return reinterpret_cast<C&>(*comp.get());
            }
        }
        throw std::runtime_error("No component found of given type in " + name);
    };

    /// Removes component from GameObject
    /// \tparam C Component to remove
    template<typename C>
    void removeComponent(){
        if(!_components.empty()){
            for(auto comp = _components.begin(); comp < _components.end(); comp++){
                // Try to cast to desired component
                auto* castedComp = reinterpret_cast<C*>((*comp).get());
                // Return if cast was successful
                if(castedComp)
                    _components.erase(comp);
            }
        }
    }

    /// Checks if the GameObject has a component of type C
    /// \tparam C The type of component to check
    /// \return true if component is present in GameObject
    template<typename C>
    bool hasComponent(){
        if(!_components.empty()){
            for(auto& comp : _components){
                // Try to cast to desired component
                auto* castedComp = reinterpret_cast<C*>(comp.get());
                // Return if cast was successful
                if(castedComp)
                    return true;
            }
        }
        return false;
    }

    [[nodiscard]] bool isActiveInWorld() const;
    [[nodiscard]] bool isActiveSelf() const;
    [[nodiscard]] bool getActive() const;
    void setActive(bool active);
    void onStart();
    void onUpdate();

    std::vector<std::reference_wrapper<GameObject>>& children();
    GameObject& childAt(int index);
    [[nodiscard]] GameObject& parent() const;
    void setParent(GameObject& parent);
    void addChild(GameObject &object);

    /// Return the local transform
    /// \return const Transform reference to the local transform
    const Transform& getLocalTransform() const;
    void setLocalTransform(const Transform& rTransform);
    void setLocalPosition(const Vector2& rPosition);
    /// Calculates the current world transform and returns it
    /// \return A Transform instance which is the current world transform
    Transform getWorldTransform() const;

    /// Sets the current local transform so that it matches the given world transform
    /// \param rTransform the world transform that should be set
    void setWorldTransform(const Transform& rTransform);
};


#endif //GOLFENGINE_GAMEOBJECT_H
