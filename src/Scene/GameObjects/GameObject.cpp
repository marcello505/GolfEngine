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

/// Method used to remove object from gameObjects tree;
/// \param gameObject
void GameObject::removeGameObject(const GameObject& gameObject) {
    //TODO fix FIND_IF
   // auto objectToRemove = std::find_if(_gameObjects.begin(), _gameObjects.end(), [gameObject] (GameObject& g)  {g == gameObject});
    //_gameObjects.erase(objectToRemove);

}

/// return tree of game objects
/// \return
std::vector<GameObject>& GameObject::getGameObjects() {
    return _gameObjects;
};



