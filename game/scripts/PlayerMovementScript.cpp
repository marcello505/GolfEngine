//
// Created by marcello on 11/29/22.
//

#include "PlayerMovementScript.h"

void PlayerMovementScript::onStart() {
    _sprite = &_gameObject.value().get().getComponent<SpriteComponent>();
    _rb = &_gameObject.value().get().getComponent<RigidBody>();
    _actionMap = ActionMap::getActionMap();

    if(_gameObject.value().get().hasComponent<Animator>())
        _animator = &_gameObject.value().get().getComponent<Animator>();
        _animator->play("idle", true);
}

void PlayerMovementScript::onUpdate() {

    //Player movement logic
    {
        Vector2 inputDirection {};
        if(_actionMap->isPressed("playerLeft")){
            inputDirection.x -= 1.0f;
        }
        if(_actionMap->isPressed("playerRight")){
            inputDirection.x += 1.0f;
        }
        if(_actionMap->isPressed("playerUp")){
            inputDirection.y -= 1.0f;
        }
        if(_actionMap->isPressed("playerDown")){
            inputDirection.y += 1.0f;
        }

        _rb->applyWorldForceToCenter(inputDirection.normalized() * playerSpeed);
    }

    //Point to mouse logic
    {
        float angleToMouse = _gameObject->get().getWorldTransform().position.angleToDegrees(_actionMap->getMousePosition()) - rotationOffset;
        _sprite->setRotation(angleToMouse); //angle to mouse + offset
    }
}

std::unique_ptr<ISnapshot> PlayerMovementScript::saveSnapshot() {
    auto snapshot = std::make_unique<Snapshot>();
    snapshot->active = _active;
    return std::move(snapshot);
}

void PlayerMovementScript::loadSnapshot(const ISnapshot &rawSnapshot) {
    auto& snapshot = (Snapshot&)rawSnapshot;
    BehaviourScript::setActive(snapshot.active);
}
