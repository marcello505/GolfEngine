//
// Created by Lucas on 4-12-2022.
//
#include <iostream>
#include <vector>
#include <valarray>
#include "AStarPathfindingService.h"
namespace GolfEngine::Services::Pathfinding {
    AStarPathfindingService::AStarPathfindingService()  {

    }

    void AStarPathfindingService::findPathEveryTick(){
        for (auto& pathfindingComponent : _pathfindingComponents) {
            if(pathfindingComponent.get().countedFrames > 119){
                auto& startNode = pathfindingComponent.get().covertPosToNode(pathfindingComponent.get().getParentGameObjectPosition());
                auto& targetnode = pathfindingComponent.get().covertPosToNode(pathfindingComponent.get().getTargetPosition());
                auto& graph = pathfindingComponent.get().getGraph();

                auto path = findPath(startNode,targetnode, graph);
            }

        }

    }


    std::vector<Node> AStarPathfindingService::findPath(Node& start, Node& target, Graph& graph) {

        std::map<int, heuristicValues> weights;
        for (auto &node : graph.nodes) {
            weights[node.id] = {};
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

    int AStarPathfindingService::calculateHeuristic(Node start, Node target) {
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



}