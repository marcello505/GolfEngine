//
// Created by conner on 12/5/2022.
//

#include "TiledComponent.h"
#include "Services/Singletons/TileMapParserSingleton.h"
#include "Services/Singletons/RenderSingleton.h"

TiledComponent::TiledComponent(const std::string& mapPath, const std::string& tileSetPath, Vector2 pixelScale)
: _renderShape{GolfEngine::Services::TileMapParser::getService().loadMap(mapPath, tileSetPath)} {
    _renderShape.setPixelScale(pixelScale);
    // TODO create collider gameObjects
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
