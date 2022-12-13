//
// Created by conner on 12/13/2022.
//

#include "PlayerShootScript.h"
#include "Input/ActionMap.h"

void PlayerShootScript::onStart() {
    _gunShotAudio = &_gameObject.value().get().getComponent<GolfEngine::Scene::Components::AudioSource>();

    if (_gameObject.value().get().hasComponent<Animator>())
        _animator = &_gameObject.value().get().getComponent<Animator>();
}

void PlayerShootScript::onUpdate() {
    //Handle shooting
    if(ActionMap::getActionMap()->isJustPressed("playerShoot")){
        if(_currentAmmo > 0){
            _currentAmmo--;

            _gunShotAudio->play();
            _animator->play("shoot");

            auto projectile = _projectilePool->getProjectile();
            if(projectile){
                Transform projectileTransform {_gameObject->get().getWorldTransform()};
                projectileTransform.rotation = _gameObject->get().getWorldTransform().position.angleToDegrees(ActionMap::getActionMap()->getMousePosition());
                auto directionToMouse = _gameObject->get().getWorldTransform().position.directionTo(ActionMap::getActionMap()->getMousePosition());
                projectileTransform.position += directionToMouse * 80.0f;

                projectile.value().get().shoot(projectileTransform, directionToMouse);
            }
        }
    }
    if(ActionMap::getActionMap()->isJustPressed("playerReload")){
        reloadWeapon();
    }
}

void PlayerShootScript::reloadWeapon() {
    // TODO add some kind of reload timer
    _currentAmmo = _maxAmmo;
}
