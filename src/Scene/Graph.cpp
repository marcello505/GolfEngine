//
// Created by marcello on 12/16/22.
//
#include "Core/Settings.h"
#include "Services/Singletons/RenderSingleton.h"

#include "Graph.h"

RenderShape& Graph::getRenderShape() {
    return _renderShape;
}

Graph::Graph(std::vector<Node> nodes, std::vector<std::unique_ptr<RectRenderShape>> drawables) : nodes{std::move(nodes)} {
    _renderShape.nodes = std::move(drawables);

    //Register to RenderService
    if(GolfEngine::Services::Render::hasService()){
        auto& settings = GolfEngine::Core::getProjectSettings();
        if(settings.hasBool(PROJECT_SETTINGS_BOOL_RENDER_PATHFINDING) && settings.getBool(PROJECT_SETTINGS_BOOL_RENDER_PATHFINDING)){
            GolfEngine::Services::Render::getService()->addDrawable(*this);
        }
    }
}

Graph::~Graph() {
    if(GolfEngine::Services::Render::hasService()){
        auto& service = *GolfEngine::Services::Render::getService();
        if(service.isRegistered(*this)) service.removeDrawable(*this);
    }

}

void Graph::updateGraphColors() {
    auto& settings = GolfEngine::Core::getProjectSettings();
    if(settings.hasBool(PROJECT_SETTINGS_BOOL_RENDER_PATHFINDING) && settings.getBool(PROJECT_SETTINGS_BOOL_RENDER_PATHFINDING)){

        for(int i = 0; i < nodes.size(); ++i){
            auto& node = nodes[i];
            auto& renderShape = _renderShape.nodes[i];

            if(node.tag == NodeTags::None)
                renderShape->setColor(Color{});
            else if(node.tag == NodeTags::Visited)
                renderShape->setColor(Color{0, 0, 255});
            else if(node.tag == NodeTags::Path)
                renderShape->setColor(Color{0, 255, 0});
        }

    }
}

