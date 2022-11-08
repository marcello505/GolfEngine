//
// Created by marce on 02/11/2022.
//

#include "GameObject.h"
bool GameObject::isActiveInWorld() const {return false;};
bool GameObject::isActiveSelf() const {return false;};
bool GameObject::getActive() const {return false;};
void GameObject::setActive(bool active){};
void GameObject::onUpdate(){}

/// Method used to add object  to gameObjects tree;
/// \param gameObject
void GameObject::addGameObject(const GameObject& gameObject) {
    _gameObjects.push_back(gameObject);
}

/// return tree of game objects
/// \return
std::vector<GameObject>& GameObject::getGameObjects() {
    return _gameObjects;
};



