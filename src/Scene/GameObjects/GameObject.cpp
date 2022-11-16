#include "GameObject.h"
#include <algorithm>

GameObject::GameObject(Scene* scene, GameObject* parent, const char* name, const char* tag) : _scene{scene}, _active{true}, layer{0}, recordable{false},
    name{name? name : ""}, tag{tag? tag : "default"}, _parent{parent? parent : scene->getRootGameObject()}, _components{new std::vector<Component*>{}} {
    if(_parent != this && _parent != nullptr)
        _parent->addChild(this);
}

GameObject::~GameObject() {
    if(!_components->empty()){
        // Call on remove function for all components
        for(auto& comp : *_components)
            comp->onRemove();

        // Erase components list
        _components->erase(_components->begin(), _components->end());
    }
    else
        delete _components;

    // Destroy and call destructor for all child game objects
    if(!_children.empty()){
        for(auto* child : _children){
            if(child){
                delete child;
                child = nullptr;
            }
        }
    }
}

GameObject::GameObject(const GameObject& other){
    // copy primitives
    _scene = other._scene;
    _parent = other._parent;
    _active = other._active;
    name = other.name;
    tag = other.tag;
    layer = other.layer;
    recordable = other.recordable;

    // copy components
    _components = new std::vector<Component*>{};
    auto& componentsToCopy = other._components;
    for(auto& comp : *componentsToCopy){
        _components->emplace_back(comp->clone());
    }

    // copy children game objects
    auto& childrenToCopy = other._children;
    for(auto& child : childrenToCopy){
        _children.push_back(new GameObject(*child));
    }
}

GameObject& GameObject::operator=(const GameObject& other){
    if(this != &other){
        // Delete existing pointers
        if(!_components->empty()){
            // Call on remove function for all components
            for(auto& comp : *_components)
                comp->onRemove();

            // Erase components list
            _components->erase(_components->begin(), _components->end());
        }
        else
            delete _components;

        // Destroy all child game objects
        if(!_children.empty()){
            for(auto* child : _children){
                if(child){
                    delete child;
                    child = nullptr;
                }
            }
        }

        // copy primitives
        _scene = other._scene;
        _parent = other._parent;
        _active = other._active;
        name = other.name;
        tag = other.tag;
        layer = other.layer;
        recordable = other.recordable;

        // copy components
        _components = new std::vector<Component*>{};
        auto& componentsToCopy = other._components;
        for(auto& comp : *componentsToCopy){
            _components->emplace_back(comp->clone());
        }

        // copy children game objects
        auto& childrenToCopy = other._children;
        for(auto& child : childrenToCopy){
            _children.push_back(new GameObject(*child));
        }
    }
    return *this;
}

//GameObject::GameObject(GameObject &&other) {
//
//}
//
//GameObject& GameObject::operator=(GameObject&& other){
//
//}

bool GameObject::isActiveInWorld() const {return false;}
bool GameObject::isActiveSelf() const {return false;}

bool GameObject::getActive() const {
    return _active;
}

void GameObject::setActive(bool active){
    // Only continue if changing to new active state
    if(_active == active) {return;}

    // Update state
    _active = active;

    // De/Activate all components
    for(auto& comp : *_components){
        comp->setActive(active);
    }
}

void GameObject::onStart() {
    // Call on start for all components
    if(!_components->empty()){
      for(auto& comp : *_components)
          comp->onStart();
    }

    // Call start for all child game objects
    if(!_children.empty()){
        for(auto& child : _children)
            child->onStart();
    }
}

void GameObject::onUpdate() {
    // Do not update if GameObject is inactive
    if(!_active) {return;}

    // Update all components
    for(auto& comp : *_components){
        comp->onUpdate();
    }

    // Update all children of this gameObject
    for(auto& child : _children){
        child->onUpdate();
    }
}

void GameObject::addChild(GameObject* gameObject) {
    _children.push_back(gameObject);
}

std::vector<GameObject*>& GameObject::children() {
    return _children;
}

GameObject* GameObject::childAt(int index) {
    return _children.at(index);
}

GameObject& GameObject::parent() const {
    return *_parent;
}

void GameObject::removeComponent(Component& component) {
    auto it = std::find(_components->begin(), _components->end(), &component);
    if(it != _components->end()) {
        _components->erase(it);
    }
}
