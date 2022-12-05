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
    go.addComponent<SpriteComponent>("res/player.png");
    go.getComponent<SpriteComponent>().setColor(Color(255,255,255,255 ));

    go.setWorldTransform(Transform(Vector2(200,200), 0, Vector2(1,1)));

    go.addComponent<BoxCollider>(Vector2(50,100));
    go.addComponent<RigidBody>(RigidBodyDef{RigidBodyTypes::DynamicBody});
    go.addComponent<MovementScript>();




}