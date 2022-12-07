//
// Created by conner on 11/23/2022.
//

#include "SceneFactory.h"
#include "Scene/Components/RigidBody.h"
#include "Graph.h"
#include "Scene/Components/BoxCollider.h"
#include "Scene/RenderShape/CircleRenderShape.h"
#include "Services/SDLRenderService.h"
#include "Services/Abstracts/PathfindingService.h"
#include "Services/Singletons/PathfindingSingleton.h"
#include "Scene/Node.h"
#include "Scene/Graph.h"
#include <Services/Singletons/RenderSingleton.h>
#include <Scene/GameObjects/UIObject/Text.h>
#include <map>

static const int _nodeDistance = 20;


void SceneFactory::build(Scene& scene) const {

    //PLayer Sprite
    auto* rs = GolfEngine::Services::Render::getService();

    std::vector<Collider*> colliders;

    auto& go = scene.createNewGameObject<GameObject>();
    go.setWorldTransform(Transform(Vector2(250,210 ),0,Vector2(1,1)));

    go.addComponent<RigidBody>(RigidBodyDef{RigidBodyTypes::StaticBody});

    go.addComponent<BoxCollider>(Vector2(100,100));

    auto& go2 = scene.createNewGameObject<GameObject>();
    go2.setWorldTransform(Transform(Vector2(500,350 ),0,Vector2(1,1)));

    go2.addComponent<RigidBody>(RigidBodyDef{RigidBodyTypes::StaticBody});
    go2.addComponent<BoxCollider>(Vector2(50,100));

    colliders.emplace_back(&go.getComponent<BoxCollider>());
    colliders.emplace_back(&go2.getComponent<BoxCollider>());

    std::map<int, Text*> drawables;

    std::vector<Node> nodeList;

    std::vector<int> nodeIds;
    std::vector<std::pair<int,int>> edges;


    int height = rs->screenSizeHeight();
    int width = rs->screenSizeWidth();
    int widthNodeDistance = 0;
    int heightNodeDistance = 0;
    int nodeCounter = 0;

    while (heightNodeDistance < height){
        while(widthNodeDistance < width){
            if(isValidSpot(Vector2(widthNodeDistance, heightNodeDistance),colliders)){


                auto* text = new Text(Vector2(widthNodeDistance,heightNodeDistance), 0, "o",
                                     15, Color(),
                                     R"(../../../validation/US08_RenderUIObject/resources/Rubik-VariableFont_wght.ttf)",
                                     Alignment::Center );
                rs->addDrawable(*text);
                drawables.insert(std::make_pair(nodeCounter, text));
                nodeIds.push_back(nodeCounter);

                auto node = Node(nodeCounter,Vector2(widthNodeDistance, heightNodeDistance));
                nodeList.emplace_back(node);

            }

            widthNodeDistance += _nodeDistance;
            nodeCounter++;
        }
        widthNodeDistance = 0;
        heightNodeDistance += _nodeDistance;
    }

    for ( auto& outerNode : nodeList){
        for ( auto& innerNode : nodeList){
            if(outerNode.id != innerNode.id) {
                if (std::abs(outerNode.position.x - innerNode.position.x) <= _nodeDistance &&
                    std::abs(outerNode.position.y - innerNode.position.y) <= _nodeDistance) {
                    outerNode.edges.emplace_back(innerNode.id);
//                    edges.emplace_back(innerNode);
                }
            }
        }
    }

    auto graph = new Graph(nodeList);

    PathfindingService* ps = GolfEngine::Services::Pathfinding::getService();
   auto path =  ps->findPath(graph->nodes[0],graph->nodes[18], *graph);

    for (auto node : path) {
        drawables.at(node.id)->_renderShape.setText("-");
    }


}


bool SceneFactory::isValidSpot(Vector2 pos, std::vector<Collider *> colliders) const {
    auto* rs = GolfEngine::Services::Render::getService();

    for(auto& collider : colliders){
        if(collider->getRenderShape().getType() == RenderShapeType::RectShape){
            auto* rect = (RectRenderShape *) &collider->getRenderShape();
            auto LX = rect->rect().position.x - rect->rect().size.x /2;
            auto RX = rect->rect().position.x + rect->rect().size.x/2;
            auto LY = rect->rect().position.y - rect->rect().size.y/2;
            auto RY =  rect->rect().position.y + rect->rect().size.y /2;
            if( pos.x >=  LX &&
                pos.x <=  RX &&
                pos.y >= LY &&
                pos.y <= RY)
            {
                return false;
            }
        }
    }
    return true;
}
