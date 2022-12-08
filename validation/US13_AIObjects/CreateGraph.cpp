//
// Created by Lucas on 7-12-2022.
//

#include <map>
#include <utility>
#include <valarray>
#include "CreateGraph.h"
#include "Services/Singletons/RenderSingleton.h"
#include "Scene/RenderShape/RectRenderShape.h"
#include "Scene/RenderShape/CircleRenderShape.h"
#include "Scene/GameObjects/UIObject/Text.h"
#include "Scene/Node.h"
#include "Services/Abstracts/PathfindingService.h"
#include "Services/Singletons/PathfindingSingleton.h"
#include "../US00_Rendering/RectDrawable.h"


CreateGraph::CreateGraph(std::vector<Collider *> colliders, int nodeDistance): _nodeDistance{nodeDistance}, colliders{colliders} {
}


std::shared_ptr<Graph> CreateGraph::createGraph(){
    auto* rs = GolfEngine::Services::Render::getService();

    std::map<int, RectDrawable*> drawables;

    std::vector<Node> nodeList;

    std::vector<int> nodeIds;
    std::vector<std::pair<int,int>> edges;


    int height = rs->screenSizeHeight();
    int width = rs->screenSizeWidth();
    int widthNodeDistance = _nodeDistance;
    int heightNodeDistance = _nodeDistance;
    int nodeCounter = 0;

    while (heightNodeDistance < height){
        while(widthNodeDistance < width){
            if(isValidSpot(Vector2(widthNodeDistance, heightNodeDistance),colliders)){
                auto* rect = new RectDrawable(Rect2(Vector2(widthNodeDistance,heightNodeDistance), Vector2(5,5)),
                                              Transform(Vector2(0,0), 0, Vector2(1,1)),
                                              Vector2(),
                                              Color());


                rs->addDrawable(*rect);
                drawables.insert(std::make_pair(nodeCounter, rect));
                nodeIds.push_back(nodeCounter);

                auto node = Node(nodeCounter,Vector2(widthNodeDistance, heightNodeDistance));
                nodeList.emplace_back(node);
                nodeCounter++;

            }

            widthNodeDistance += _nodeDistance;
        }
        widthNodeDistance = _nodeDistance;
        heightNodeDistance += _nodeDistance;
    }

    for ( auto& outerNode : nodeList){
        for ( auto& innerNode : nodeList){
            if(outerNode.id != innerNode.id) {
                if (std::abs(outerNode.position.x - innerNode.position.x) <= _nodeDistance &&
                    std::abs(outerNode.position.y - innerNode.position.y) <= _nodeDistance) {
                    outerNode.edges.emplace_back(innerNode.id);
                }
            }
        }
    }


    // Set wall of weigted nodes
    nodeList[7].weight = 500;
    nodeList[38].weight = 500;
    nodeList[69].weight = 500;
    nodeList[100].weight = 500;
    nodeList[131].weight = 500;

    auto graph = std::make_shared<Graph>(nodeList);

    PathfindingService* ps = GolfEngine::Services::Pathfinding::getService();

    auto path =  ps->findPath(graph->nodes[0],graph->nodes[270], *graph);

    //Display Visited
    for (const auto& visited :  graph->nodes ) {
            if(visited.tag == NodeTags::Visited){
               drawables.at(visited.id)->setColor(Color(0,0,255));
            }
    }
    // Display weigted nodes
    drawables.at(nodeList[131].id)->setColor(Color(255,0,0));
    drawables.at(nodeList[100].id)->setColor(Color(255,0,0));
    drawables.at(nodeList[69].id)->setColor(Color(255,0,0));
    drawables.at(nodeList[38].id)->setColor(Color(255,0,0));
    drawables.at(nodeList[7].id)->setColor(Color(255,0,0));



    for (const auto& node : path) {
        drawables.at(node.id)->setColor(Color(0,255,0));
    }
    return graph;

}

bool CreateGraph::isValidSpot(Vector2 pos, std::vector<Collider *> colliders) const {
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
        }else{
            auto* circle = (CircleRenderShape *) &collider->getRenderShape();
            auto x = pow((pos.x - circle->position().x),2);
            auto y = pow((pos.y - circle->position().y),2);
            auto r = pow(circle->radius(),2);
            if(x+y <= r){
                return false;
            }
        }
    }
    return true;
}

