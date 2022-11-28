//
// Created by conner on 11/23/2022.
//

#include "SceneFactory.h"
#include "Scene/Components/SpriteComponent.h"
#include "Scene/Components/ParticleSystem.h"

void SceneFactory::build(Scene& scene) const {
    auto& go = scene.createNewGameObject<GameObject>();
    go.addComponent<ParticleSystem>(R"(..\..\..\validation\US101_Particles\res\smoke.png)", 1,2, Vector2(30,30));
    go.getComponent<ParticleSystem>().play(true);
    go.setWorldTransform(Transform(Vector2(200,200), 0, Vector2(1,1)));
}