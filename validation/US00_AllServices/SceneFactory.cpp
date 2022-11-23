//
// Created by conner on 11/23/2022.
//

#include "SceneFactory.h"
#include "Scene/Components/SpriteComponent.h"
#include "Scene/Components/RigidBody.h"
#include "Scene/Components/CircleCollider.h"
#include "Scene/Components/BoxCollider.h"
#include "Scene/Components/BehaviourScript.h"
#include "MovementScript.h"

void SceneFactory::build(Scene& scene) const {



    //PLayer Sprite
    auto& go = scene.createNewGameObject<GameObject>();
    go.addComponent<SpriteComponent>(R"(..\..\..\validation\US09_Animations\res\player.png)");
    go.setWorldTransform(Transform(Vector2(200,200), 0, Vector2(0.5f,0.1f)));
    go.addComponent<CircleCollider>(25);
    go.addComponent<RigidBody>(RigidBodyDef{RigidBodyTypes::DynamicBody});

//    auto script = MovementScript();
//    script.setParentGameObject(go);
//    script.setActive(true);
    go.addComponent<MovementScript>();





    //Ground
    auto& groundObject = scene.createNewGameObject<GameObject>();
    groundObject.addComponent<BoxCollider>(Vector2{400.0f, 20.0f});
    groundObject.addComponent<RigidBody>(RigidBodyDef{RigidBodyTypes::StaticBody});
    groundObject.setLocalPosition({320, 450});



}