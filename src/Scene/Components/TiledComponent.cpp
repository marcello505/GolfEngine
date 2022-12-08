//
// Created by conner on 12/5/2022.
//

#include "TiledComponent.h"
#include "Services/Singletons/TileMapParserSingleton.h"
#include "Services/Singletons/RenderSingleton.h"
#include "Core/SceneManager.h"
#include "Scene/Components/RigidBody.h"
#include "Scene/Components/BoxCollider.h"

TiledComponent::TiledComponent(const std::string& mapPath, Vector2 pixelScale)
: _renderShape{GolfEngine::Services::TileMapParser::getService().loadMap(mapPath)} {
    _renderShape.setPixelScale(pixelScale);
}

void TiledComponent::onStart() {
    if(GolfEngine::Services::Render::hasService())
        GolfEngine::Services::Render::getService()->addDrawable(*this);
}

void TiledComponent::onUpdate() {}

void TiledComponent::onRemove() {
    if(GolfEngine::Services::Render::hasService())
        GolfEngine::Services::Render::getService()->removeDrawable(*this);
}

bool TiledComponent::getActive() {
    return _active;
}

void TiledComponent::setActive(bool active) {
    _active = active;
}

void TiledComponent::setParentGameObject(GameObject& gameObject) {
    _gameObject = gameObject;
}

RenderShape& TiledComponent::getRenderShape() {
    if(_gameObject){
        _renderShape.applyTransform(_gameObject->get().getWorldTransform());
    }
    return _renderShape;
}

void TiledComponent::initColliders() {
    // Create a GameObject with an BoxCollider for each collider Tile in the map
    auto& scene = GolfEngine::SceneManager::GetSceneManager().getCurrentScene();
    auto& map = _renderShape.map().map;
    auto& colliderTiles = _renderShape.tileSet().colliderTiles;
    float tileWidth {(float)_renderShape.map().tileWidth};
    float tileHeight {(float)_renderShape.map().tileHeight};
    Vector2 scale {_renderShape.scale()};
    uint8_t rowIndex = 0;
    for(auto& row : map){
        uint8_t columnIndex = 0;
        for(auto& tile : row){
            // Check if tile is a collider tile
            auto result = std::find(colliderTiles.begin(), colliderTiles.end(), tile-1);
            if(result != colliderTiles.end()){
                // If so, create a GameObject with a solid rigid body
                auto& go = scene.createNewGameObject<GameObject>(_gameObject->get());
                go.addComponent<RigidBody>(RigidBodyDef{RigidBodyTypes::StaticBody});
                go.addComponent<BoxCollider>(Vector2{tileWidth, tileHeight});
                go.setLocalTransform(Transform{Vector2{(columnIndex * (tileWidth * scale.x)) + ((tileWidth*scale.x)/2), (rowIndex * (tileHeight * scale.y)) + ((tileHeight*scale.y)/2)}, 0, Vector2{1,1}});
            }
            columnIndex++;
        }
        rowIndex++;
    }
}
