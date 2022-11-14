#include "GameObject.h"
#include <algorithm>

GameObject::GameObject(Scene* scene, GameObject* parent, const char* name, const char* tag) : _scene{scene}, _active{true}, layer{0}, recordable{false},
    name{name? name : ""}, tag{tag? tag : ""}, _parent{parent? parent : scene->getRootGameObject()} {

}

GameObject::~GameObject() {
    if(!_components.empty())
        _components.erase(_components.begin(), _components.end());

    if(!_children.empty()){
        for(auto* child : _children){
            delete child;
        }
    }
}

bool GameObject::isActiveInWorld() const {return false;}
bool GameObject::isActiveSelf() const {return false;}

bool GameObject::getActive() const {
    return _active;
}

void GameObject::setActive(bool active){
    _active = active;

    // TODO de/activate all components
}

void GameObject::onUpdate() {
    // TODO update all components

    // Update all children of this gameObject
    for(auto* child : _children){
        child->onUpdate();
    }
}

void GameObject::addChild(GameObject *gameObject) {
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
    auto it = std::find(_components.begin(), _components.end(), &component);
    if(it != _components.end())
        _components.erase(it);
}
