//
// Created by conner on 11/23/2022.
//

#include <iostream>
#include "SpriteComponent.h"
#include "../../Services/Singletons/RenderSingleton.h"


SpriteComponent::SpriteComponent(const std::string &path, Vector2 pixelScale, Rect2 imageSource, Vector2 offsetPosition,
                                 float startingRotation, Vector2 pivotPoint, Color color) : _sortingLayer{0}, _orderInLayer{0},
                                 _renderShape{SpriteRenderShape(path, offsetPosition, startingRotation, pixelScale, imageSource, pivotPoint, color)} {
}

void SpriteComponent::onStart() {
    GolfEngine::Services::Render::getService()->addDrawable(*this);
}

void SpriteComponent::onUpdate() {
    std::cout << "hey";
}

void SpriteComponent::onRemove() {
    auto renderService = GolfEngine::Services::Render::getService();
    if(renderService)
        renderService->removeDrawable(*this);
}

bool SpriteComponent::getActive() {
    return _active;
}

void SpriteComponent::setActive(bool active) {
    if(_active == active) return;

    if(active)
        onStart();
    else
        onRemove();

    _active = active;
}

void SpriteComponent::setParentGameObject(GameObject& gameObject) {
    _gameObject = gameObject;
}

RenderShape& SpriteComponent::getRenderShape() {
    if(_gameObject){
        _renderShape.applyTransform(_gameObject->get().getWorldTransform());
    }
    return _renderShape;
}

std::string SpriteComponent::path() const {
    return _renderShape.path();
}

Rect2 SpriteComponent::imageSource() const {
    return _renderShape.imageSource();
}

Color SpriteComponent::color() const {
    return _renderShape.color();
}

void SpriteComponent::setPath(const std::string& path) {
    _renderShape.setPath(path);
}

void SpriteComponent::setImageSource(Rect2 imageSource) {
    _renderShape.setImageSource(imageSource);
}

void SpriteComponent::setColor(Color color) {
    _renderShape.setColor(color);
}
