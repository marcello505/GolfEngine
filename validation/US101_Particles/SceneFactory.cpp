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
    go.addComponent<ParticleSystem>(R"(..\..\..\validation\US101_Particles\res\smoke.png)", 50,5, Vector2(30,30));
    go.addComponent<ParticleScript>();


    go.getComponent<ParticleSystem>().setDirection({0,-1});
    go.getComponent<ParticleSystem>().setSpread({180,360});
    go.getComponent<ParticleSystem>().setFade(true);

    go.setWorldTransform(Transform(Vector2(200,200), 0, Vector2(1,1)));


}