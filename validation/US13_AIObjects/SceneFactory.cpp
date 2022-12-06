//
// Created by conner on 11/23/2022.
//

#include "SceneFactory.h"
#include "Scene/Components/RigidBody.h"
#include "Graph.h"
#include "Scene/Components/BoxCollider.h"
#include "Scene/RenderShape/CircleRenderShape.h"
#include <Services/Singletons/RenderSingleton.h>
#include <Scene/GameObjects/UIObject/Text.h>
#include <map>

void SceneFactory::build(Scene& scene) const {

    //PLayer Sprite

    auto* rs = GolfEngine::Services::Render::getService();

    std::vector<Collider*> colliders;

    auto& go = scene.createNewGameObject<GameObject>();
    go.setWorldTransform(Transform(Vector2(200,200),0,Vector2(1,1)));

    go.addComponent<RigidBody>(RigidBodyDef{RigidBodyTypes::StaticBody});
    go.addComponent<BoxCollider>(Vector2(50,100));
    colliders.emplace_back(&go.getComponent<BoxCollider>());

    std::map<int, Text> nodes;
    std::vector<int> nodeIds;
    std::vector<std::pair<int,int>> edges;


    int height = 460;
    int width = 620;
    int widthNodeDistance = 30;
    int heightNodeDistance = 30;
    int nodeCounter = 0;

    while (heightNodeDistance < height){
        while(widthNodeDistance < width){
            if(isValidSpot(Vector2(widthNodeDistance, heightNodeDistance),colliders)){
                auto node = new Text(Vector2(widthNodeDistance,heightNodeDistance), 0, "o",
                                     15, Color(),
                                     R"(../../../validation/US08_RenderUIObject/resources/Rubik-VariableFont_wght.ttf)",
                                     Alignment::Center );
                rs->addDrawable(*node);

                nodes.insert(std::make_pair(nodeCounter, *node));
                nodeIds.push_back(nodeCounter);
            }

            widthNodeDistance += 30;
            nodeCounter++;
        }
        widthNodeDistance = 30;
        heightNodeDistance += 30;
    }

    for ( const auto& outerNode : nodes){
        for ( const auto& innerNode : nodes){
            if(outerNode.first != innerNode.first) {
                if (std::abs(outerNode.second._position.x - innerNode.second._position.x) <= 30 &&
                    std::abs(outerNode.second._position.y - innerNode.second._position.y) <= 30) {
                    edges.emplace_back(outerNode.first, innerNode.first);
                }
            }
        }
    }

    auto graph = new Graph(nodeIds, edges);
}


bool SceneFactory::isValidSpot(Vector2 pos, std::vector<Collider *> colliders) const {
    for(auto& collider : colliders){
        if(collider->getRenderShape().getType() == RenderShapeType::RectShape){
            auto* rect = (RectRenderShape *) &collider->getRenderShape();
            if(pos.x >= rect->rect().position.x - (rect->rect().size.x / 2) &&
            pos.x <= rect->rect().size.x  + (rect->rect().position.x / 2)
               && pos.y >= rect->rect().position.y - (rect->rect().size.y / 2) &&
               pos.y <= rect->rect().size.y + (rect->rect().position.y / 2) ){
                return false;
            }
        }
    }
    return true;
}
