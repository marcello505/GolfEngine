//
// Created by Lucas on 4-12-2022.
//
#include <iostream>
#include <vector>
#include <valarray>
#include "AStarPathfindingService.h"
#include "Services/Singletons/PathfindingSingleton.h"
#include "Services/Singletons/RenderSingleton.h"
#include "Scene/Components/Collider.h"
#include "Scene/RenderShape/CircleRenderShape.h"
#include "Services/Singletons/PhysicsSingleton.h"

namespace GolfEngine::Services::Pathfinding {
    void AStarPathfindingService::findPathEveryTick(){
        for (auto& pathfindingComponent : _pathfindingComponents) {
            if(pathfindingComponent.get().needsNewPath() && !_graph->nodes.empty()){
                auto startNode = covertPosToNode(pathfindingComponent.get().getParentGameObjectPosition());
                auto targetNode = covertPosToNode(pathfindingComponent.get().getTargetPosition());
                pathfindingComponent.get().setPath(findPath(startNode,targetNode, *_graph));
            }
        }
    }

    std::vector<Node> AStarPathfindingService::findPath(Node& start, Node& target, Graph& graph) {
        std::map<int, heuristicValues> weights;
        for (auto &node : graph.nodes) {
            weights[node.id] = {};
            node.tag = NodeTags::None;
        }

        node_priority_queue priority_list(
                [&weights](const Node &lhs, const Node &rhs) {
                    if (weights[lhs.id].f == weights[rhs.id].f) {
                        return weights[lhs.id].h > weights[rhs.id].h;
                    } else {
                        return weights[lhs.id].f > weights[rhs.id].f;
                    }
                });


        weights[start.id].f = 0;
        priority_list.push(start);

        while (!priority_list.empty()){
            // get estimated shortest route
           Node fNode = priority_list.top();
            priority_list.pop();

           if(fNode.id == target.id){
               //Trace back Path
               std::vector<Node> path;

               auto& parent = target;
               path.emplace_back(parent);
               parent.tag = NodeTags::Path;

               while(weights[parent.id].parent != -1){
                   parent = graph.nodes[weights.at(parent.id).parent];
                   path.emplace_back(parent);
                   parent.tag = NodeTags::Path;
               }
               path.pop_back();
               //Display Visited
               return path;
           }

            //if not at end check edges
            for (auto edge : graph.nodes[fNode.id].edges) {
                auto& n = graph.nodes[edge];


                if(n.tag == NodeTags::None){
                    n.tag = NodeTags::Visited;
                }

                int g = weights[fNode.id].f + n.weight;
                int h = calculateHeuristic(n, target);
                int f = g + h;

                if(f < weights[n.id].f){
                    weights[n.id].h = h;
                    weights[n.id].f = f;
                    weights[n.id].parent = fNode.id;

                    priority_list.push(n);
                }

            }
        }
        return {};
    }

    int AStarPathfindingService::calculateHeuristic(const Node& start, const Node& target) {
        int x = start.position.x - target.position.x;
        int y = start.position.y - target.position.y;
        int res = sqrt(pow(x, 2) + pow(y, 2)) / 10;

        if(x ==0)
            res -= 1;
        if(y == 0)
            res -= 1;

        return res;
    }

    void AStarPathfindingService::removePathfinding(class Pathfinding &pathfinding) {
        _pathfindingComponents.erase(std::find_if(_pathfindingComponents.begin(), _pathfindingComponents.end(), [&](const std::reference_wrapper<class Pathfinding> &d) {
            return &d.get() == &pathfinding;
        }));
    }

    void AStarPathfindingService::addPathfinding(class Pathfinding &pathfinding) {
        _pathfindingComponents.emplace_back(std::ref(pathfinding));
    }


    void AStarPathfindingService::createGraph(){
        auto* rs = GolfEngine::Services::Render::getService();
        std::map<int, PathDrawable*> drawables;

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
                if(isValidSpot(Vector2(widthNodeDistance, heightNodeDistance))){
                    auto* rect = new PathDrawable(Rect2(Vector2(widthNodeDistance,heightNodeDistance), Vector2(5,5)),
                                                                                                    Color());


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

       _graph = std::make_unique<Graph>(nodeList);
        _graph->drawables = drawables;
    }

    bool AStarPathfindingService::isValidSpot(Vector2 pos) const {
        auto* ps = GolfEngine::Services::Physics::getService();

        auto colliders = ps->getStaticColliders();

        for(auto& collider : colliders){
            if(collider->getRenderShape().getType() == RenderShapeType::RectShape){
                //TODO add var to use as margin

                auto* rect = (RectRenderShape *) &collider->getRenderShape();
                auto LX = rect->rect().position.x - (rect->rect().size.x /2) - rectMargin ;
                auto RX = rect->rect().position.x + (rect->rect().size.x/2 )+ rectMargin;
                auto LY = rect->rect().position.y - (rect->rect().size.y/2) - rectMargin;
                auto RY =  rect->rect().position.y + (rect->rect().size.y /2) + rectMargin;
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
                auto r = pow(circle->radius()+10,2);
                if(x+y <= r){
                    return false;
                }
            }
        }
        return true;
    }

    Node& AStarPathfindingService::covertPosToNode(Vector2 position){
        const auto dist = [position](const auto& p){
            // Change the following to your needs
            return std::pow((p.position.x - position.x), 2) + std::pow((p.position.y - position.y), 2);
        };

        const auto& closest = std::min_element(_graph->nodes.cbegin(), _graph->nodes.cend(),
                                               [&dist](const auto& p1, const auto& p2)
                                               { return dist(p1) < dist(p2); });

        auto& node = *(closest);

        return const_cast<Node &>(node);
    }

    Graph& AStarPathfindingService::getGraph() {
        return *_graph;
    }

    void AStarPathfindingService::setNodeDistance(int nodeDistance) {
        _nodeDistance = nodeDistance;
    }

    void AStarPathfindingService::setMarginAroundRectColliders(int margin) {
        rectMargin = margin;
    }
}
