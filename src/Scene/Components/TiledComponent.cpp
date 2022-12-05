//
// Created by conner on 12/5/2022.
//

#include "TiledComponent.h"

void TiledComponent::onStart() {}

void TiledComponent::onUpdate() {}

void TiledComponent::onRemove() {}

bool TiledComponent::getActive() {
    return _active;
}

void TiledComponent::setActive(bool active) {
    _active = active;
}

void TiledComponent::setParentGameObject(GameObject& gameObject) {
    _gameObject = gameObject;
}