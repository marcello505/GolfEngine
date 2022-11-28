//
// Created by conner on 11/23/2022.
//

#include "SceneFactory.h"
#include "Scene/Components/SpriteComponent.h"
#include "Scene/Components/ParticleSystem.h"
#include "ParticleScript.h"
#include "Scene/Components/RigidBody.h"
#include "Scene/Components/CircleCollider.h"

void SceneFactory::build(Scene& scene) const {
    auto& go = scene.createNewGameObject<GameObject>();
    go.addComponent<ParticleSystem>(R"(..\..\..\validation\US101_Particles\res\smoke.png)", 10,2, Vector2(30,30));
    go.addComponent<ParticleScript>();
    go.addComponent<RigidBody>();
//    go.addComponent<CircleCollider>(10);

    go.getComponent<ParticleSystem>().setDirection({-1,1});

    go.setWorldTransform(Transform(Vector2(200,200), 0, Vector2(1,1)));
}