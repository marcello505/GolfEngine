//
// Created by conner on 12/13/2022.
//

#ifndef GOLFENGINE_PLAYERSHOOTSCRIPT_H
#define GOLFENGINE_PLAYERSHOOTSCRIPT_H

#include "Scene/Components/BehaviourScript.h"
#include "ProjectilePoolScript.h"
#include "Scene/Components/Animator.h"
#include "Scene/Components/AudioSource.h"

class PlayerShootScript : public BehaviourScript {
public:
    explicit PlayerShootScript(ProjectilePoolScript* projectilePoolScript, int maxAmmo) : _projectilePool{projectilePoolScript}, _maxAmmo{maxAmmo}, _currentAmmo{maxAmmo} {}
    void onStart() override;
    void onUpdate() override;

private:
    void reloadWeapon();

private:
    Animator* _animator {};
    ProjectilePoolScript* _projectilePool {};
    GolfEngine::Scene::Components::AudioSource* _gunShotAudio {};

    int _currentAmmo;
    int _maxAmmo;
};


#endif //GOLFENGINE_PLAYERSHOOTSCRIPT_H
