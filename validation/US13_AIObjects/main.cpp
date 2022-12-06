#include <Core/GameLoop.h>
#include <Services/SDLRenderService.h>
#include <Services/Singletons/RenderSingleton.h>
#include "Scene/GameObjects/UIObject/Text.h"
#include "Graph.cpp"
#include <utility>
#include <map>


int main(int argc, char* argv[])
{
    //initialize gameloop and renderservice
    GameLoop gameLoop {};
    gameLoop.useDefaultServices();
    RenderService* rs = GolfEngine::Services::Render::getService();

    std::map<int, Text> nodes;
    std::vector<int> nodeIds;
    std::map<int, int> edges;


    int height = 460;
    int width = 620;
    int widthNodeDistance = 15;
    int heightNodeDistance = 15;
    int nodeCounter = 0;

    while (heightNodeDistance < height){
        while(widthNodeDistance < width){
            auto node = new Text(Vector2(widthNodeDistance,heightNodeDistance), 0, "o",
                                      15, Color(),
                                      R"(../../../validation/US08_RenderUIObject/resources/Rubik-VariableFont_wght.ttf)",
                                      Alignment::Center );
            rs->addDrawable(*node);

            nodes.insert(std::make_pair(nodeCounter, *node));
            nodeIds.push_back(nodeCounter);
            widthNodeDistance += 30;
            nodeCounter++;
        }
        widthNodeDistance = 15;
        heightNodeDistance += 30;
    }

    for ( const auto& outerNode : nodes){
            for ( const auto& innerNode : nodes){
                if(outerNode.first != innerNode.first) {
                    if (std::abs(outerNode.second._position.x - innerNode.second._position.x) <= 30 &&
                        std::abs(outerNode.second._position.y - innerNode.second._position.y) <= 30) {
                        edges.insert(std::pair(outerNode.first, innerNode.first));
                    }
                }
            }

    }

    auto graph = new Graph(nodeIds, edges);

    //start gameloop
    gameLoop.start();

    return 0;
}
