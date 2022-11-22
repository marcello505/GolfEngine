//
// Created by conner on 11/21/2022.
//

#include "GameObject.h"

GameObject::GameObject(const char* name, const char* tag) :_active{true}, layer{0}, recordable{false},
    name{name? name : ""}, tag{tag? tag : "default"}{
}

GameObject::~GameObject() {
    if(!_components.empty()) {
        // Call on remove function for all components
        for (auto &comp: _components)
            comp->onRemove();
    }
}


bool GameObject::isActiveInWorld() const {return false;}
bool GameObject::isActiveSelf() const {return _active;}

bool GameObject::getActive() const {
    return _active;
}

void GameObject::setActive(bool active){
    // Only continue if changing to new active state
    if(_active == active) {return;}

    // Update state
    _active = active;

    // De/Activate all components
    for(auto& comp : _components){
        comp->setActive(active);
    }
}

void GameObject::onStart() {
    // Call on start for all components
    if(!_components.empty()){
        for(auto& comp : _components)
            comp->onStart();
    }
}

void GameObject::onUpdate() {
    // Update all components
    for(auto& comp : _components){
        if(comp->getActive())
            comp->onUpdate();
    }
}

std::vector<std::reference_wrapper<GameObject>>& GameObject::children() {
    return _children;
}

GameObject& GameObject::childAt(int index) {
    return _children.at(index);
}

GameObject& GameObject::parent() const {
    return _parent->get();
}

void GameObject::setParent(GameObject& parent) {
    _parent = std::make_unique<std::reference_wrapper<GameObject>>(parent);
}

void GameObject::addChild(GameObject& child) {
    _children.emplace_back(child);
}

const Transform& GameObject::getLocalTransform() const {
    return _localTransform;
}

void GameObject::setLocalTransform(const Transform& rTransform) {
    _localTransform = rTransform;
}

void GameObject::setLocalPosition(const Vector2& rPosition) {
    _localTransform.position = rPosition;
}

Transform GameObject::getWorldTransform() const {
    Transform result {_localTransform};

    if(_parent != nullptr){
        auto world = _parent->getWorldTransform();
        result.position += world.position;
        result.rotation += world.rotation;
        result.scale *= world.scale;
    }

    return result;
}

void GameObject::setWorldTransform(const Transform& rTransform) {
    //Get World Offset
    Transform worldOffset {};
    if(_parent){
        worldOffset = _parent->getWorldTransform();
    }

    //Get new local by taking off the offset from rTransform
    Transform localNew {};
    {
        localNew.position = rTransform.position - worldOffset.position;
        localNew.rotation = rTransform.rotation - worldOffset.rotation;
        localNew.scale = rTransform.scale / worldOffset.scale;
    }
    setLocalTransform(localNew);
}