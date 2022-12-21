//
// Created by user on 12/16/2022.
//

#include "BloodSplatterParticleEffect.h"

using namespace GolfEngine::Scene::Components;

BloodSplatterParticleEffect::BloodSplatterParticleEffect() {
    name = "blood splatter";

    auto& bloodParticleSystem = addComponent<ParticleSystem>("res/sprites/blood_splatter.png", 15, 1.0f, Vector2{4.0f, 4.0f});
    bloodParticleSystem.setSpread({0, 359});
    bloodParticleSystem.setRandomVelocity({1.5f, 4.0f});
    bloodParticleSystem.setFade(true);
    bloodParticleSystem.setRandomStartRotation(true);
}
