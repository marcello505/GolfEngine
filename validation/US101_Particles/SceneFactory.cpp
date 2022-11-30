//
// Created by conner on 11/23/2022.
//

#include "SceneFactory.h"
#include "Scene/Components/SpriteComponent.h"
#include "Scene/Components/ParticleSystem.h"
#include "ParticleScript.h"
#include "Scene/Components/RigidBody.h"
#include "Scene/Components/CircleCollider.h"
#include "Scene/Components/BoxCollider.h"

void SceneFactory::build(Scene& scene) const {
    auto& go = scene.createNewGameObject<GameObject>();
    go.addComponent<ParticleSystem>(R"(..\..\..\validation\US101_Particles\res\smoke.png)", 5,5, Vector2(20,20),Vector2(0,0), 0);
    go.addComponent<ParticleScript>();


    go.getComponent<ParticleSystem>().setSpread({0,360});
    go.getComponent<ParticleSystem>().setFade(true);
    go.getComponent<ParticleSystem>().setRotationsPerSecond(2);
    go.getComponent<ParticleSystem>().setRandomVelocity({0.5,2});


    go.setWorldTransform(Transform(Vector2(200,200), 0, Vector2(1,1)));


}