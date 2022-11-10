#include "GameObject.h"
bool GameObject::isActiveInWorld() const {return false;};
bool GameObject::isActiveSelf() const {return false;};
bool GameObject::getActive() const {return false;};
void GameObject::setActive(bool active){};
void GameObject::onUpdate(){}

void GameObject::addGameObject(const GameObject& gameObject) {
    _gameObjects.push_back(gameObject);
}

std::vector<GameObject>& GameObject::getGameObjects() {
    return _gameObjects;
};



