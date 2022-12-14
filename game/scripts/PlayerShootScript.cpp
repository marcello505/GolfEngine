//
// Created by conner on 12/13/2022.
//

#include "PlayerShootScript.h"
#include "Input/ActionMap.h"
#include "Core/Time.h"

void PlayerShootScript::onStart() {
    _audioSource = &_gameObject.value().get().getComponent<GolfEngine::Scene::Components::AudioSource>();

    if (_gameObject.value().get().hasComponent<Animator>())
        _animator = &_gameObject.value().get().getComponent<Animator>();
}

void PlayerShootScript::onUpdate() {
    //Handle shooting
    if(ActionMap::getActionMap()->isJustPressed("playerShoot")){
        if(_currentAmmo > 0 && !_reloading){
            _currentAmmo--;

            _audioSource->play("shoot");
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

    // Handle reloading
    if(ActionMap::getActionMap()->isJustPressed("playerReload")){
        reloadWeapon();
    }
    if(_reloading){
        _timePassedReloading += GolfEngine::Time::getPhysicsDeltaTime();
        if(_timePassedReloading >= _reloadTime){
            _timePassedReloading = 0.0f;
            _reloading = false;
        }
    }
}

void PlayerShootScript::reloadWeapon() {
    if(!_reloading){
        _reloading = true;
        _audioSource->play("reload");
        _currentAmmo = _maxAmmo;
    }
}

std::unique_ptr<ISnapshot> PlayerShootScript::saveSnapshot() {
    auto snapshot = std::make_unique<SnapShot>();
    snapshot->active = _active;
    snapshot->currentAmmo = _currentAmmo;
    return std::move(snapshot);
}

void PlayerShootScript::loadSnapshot(const ISnapshot &rawSnapshot) {
    auto& snapshot = (SnapShot&)rawSnapshot;
    BehaviourScript::setActive(snapshot.active);
    _currentAmmo = snapshot.currentAmmo;
}
