//
// Created by conner on 12/5/2022.
//

#include "TiledComponent.h"
#include "Services/Singletons/TileMapParserSingleton.h"
#include "Services/Singletons/RenderSingleton.h"

TiledComponent::TiledComponent(const std::string& mapPath, const std::string& tileSetPath)
: _renderShape{GolfEngine::Services::TileMapParser::getService().loadMap(mapPath, tileSetPath)} {
    auto image = _renderShape.imagePath();
}

void TiledComponent::onStart() {
    GolfEngine::Services::Render::getService()->addDrawable(*this);
}

void TiledComponent::onUpdate() {}

void TiledComponent::onRemove() {}

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
