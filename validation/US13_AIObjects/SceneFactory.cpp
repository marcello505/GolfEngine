//
// Created by conner on 11/23/2022.
//

#include "SceneFactory.h"
#include "Scene/Components/RigidBody.h"
#include "Scene/Components/BoxCollider.h"
#include "Services/SDLRenderService.h"
#include "Services/Abstracts/PathfindingService.h"
#include "Services/Singletons/PathfindingSingleton.h"
#include "Scene/Node.h"
#include "Scene/Graph.h"
#include "CreateGraph.h"
#include "Scene/Components/CircleCollider.h"
#include "Scene/Components/SpriteComponent.h"
#include "Scene/Components/Pathfinding.h"
#include <Services/Singletons/RenderSingleton.h>
#include <Scene/GameObjects/UIObject/Text.h>
#include <map>


void SceneFactory::build(Scene& scene) const {

    //PLayer Sprite
    std::vector<Collider*> colliders;

    auto& go = scene.createNewGameObject<GameObject>();
    go.setWorldTransform(Transform(Vector2(250,210 ),0,Vector2(1,1)));
    go.addComponent<RigidBody>(RigidBodyDef{RigidBodyTypes::StaticBody});
    go.addComponent<BoxCollider>(Vector2(100,100));



    auto& go2 = scene.createNewGameObject<GameObject>();
    go2.setWorldTransform(Transform(Vector2(520,350 ),0,Vector2(1,1)));
    go2.addComponent<RigidBody>(RigidBodyDef{RigidBodyTypes::StaticBody});
    go2.addComponent<CircleCollider>(50);

    colliders.emplace_back(&go.getComponent<BoxCollider>());
    colliders.emplace_back(&go2.getComponent<CircleCollider>());

    auto& player = scene.createNewGameObject<GameObject>();
    player.addComponent<SpriteComponent>(R"(..\..\..\validation\US09_Animations\res\player.png)",Vector2(5,5) );
    player.getComponent<SpriteComponent>().setColor(Color(255,255,255,255 ));
    player.setWorldTransform(Transform(Vector2(400,380), 0, Vector2(1,1)));
    player.addComponent<BoxCollider>(Vector2(10,10));
    player.addComponent<RigidBody>(RigidBodyDef{RigidBodyTypes::DynamicBody});
    CreateGraph cp = CreateGraph(colliders, 20);

    auto graph = cp.createGraph();
    auto& enemy = scene.createNewGameObject<GameObject>();

    enemy.addComponent<SpriteComponent>(R"(..\..\..\validation\US09_Animations\res\player.png)",Vector2(5,5) );
    enemy.getComponent<SpriteComponent>().setColor(Color(255,255,255,255 ));
    enemy.setWorldTransform(Transform(Vector2(100,100), 0, Vector2(1,1)));
    enemy.addComponent<BoxCollider>(Vector2(10,10));
    enemy.addComponent<RigidBody>(RigidBodyDef{RigidBodyTypes::DynamicBody});
    enemy.addComponent<Pathfinding>(&player, graph);

    //add colliders to collider list


}
