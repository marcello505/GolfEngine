//
// Created by conner on 11/23/2022.
//

#include "SpriteComponent.h"
#include "../../Services/Singletons/RenderSingleton.h"

namespace GolfEngine::Scene::Components {
    SpriteComponent::SpriteComponent(const std::string &path, Vector2 pixelScale, Rect2 imageSource,
                                     Vector2 offsetPosition,
                                     float startingRotation, Vector2 pivotPoint, Color color) : _sortingLayer{0},
                                                                                                _orderInLayer{0},
                                                                                                _renderShape{
                                                                                                        Render::SpriteRenderShape(
                                                                                                                path,
                                                                                                                offsetPosition,
                                                                                                                startingRotation,
                                                                                                                pixelScale,
                                                                                                                imageSource,
                                                                                                                pivotPoint,
                                                                                                                color)} {
    }

    void SpriteComponent::onStart() {
        if (Services::Render::hasService())
            if (!Services::Render::getService()->isRegistered(*this))
                Services::Render::getService()->addDrawable(*this);
    }

    void SpriteComponent::onUpdate() {
    }

    void SpriteComponent::onRemove() {
        if (Services::Render::hasService() &&
            Services::Render::getService()->isRegistered(*this))
            Services::Render::getService()->removeDrawable(*this);
    }

    bool SpriteComponent::getActive() {
        return _active;
    }

    void SpriteComponent::setActive(bool active) {
        if (_active == active) return;

        if (active)
            onStart();
        else
            onRemove();

        _active = active;
    }

    void SpriteComponent::setParentGameObject(GameObject &gameObject) {
        _gameObject = gameObject;
    }

    Render::RenderShape &SpriteComponent::getRenderShape() {
        if (_gameObject) {
            auto transform = _gameObject->get().getWorldTransform();
            transform.rotation += _rotation; //Offset with own rotation
            _renderShape.applyTransform(transform);
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

    void SpriteComponent::setPath(const std::string &path) {
        _renderShape.setPath(path);
    }

    void SpriteComponent::setImageSource(Rect2 imageSource) {
        _renderShape.setImageSource(imageSource);
    }

    void SpriteComponent::setColor(Color color) {
        _renderShape.setColor(color);
    }

    void SpriteComponent::setRotation(float degrees) {
        _rotation = degrees;
    }

    float SpriteComponent::getRotation() const {
        return _rotation;
    }

    std::unique_ptr<ISnapshot> SpriteComponent::saveSnapshot() {
        auto result = std::make_unique<Snapshot>();
        result->rotation = getRotation();
        result->path = path();
        result->color = color();
        result->imageSource = imageSource();
        return result;
    }

    void SpriteComponent::loadSnapshot(const ISnapshot &rawSnapshot) {
        auto &snapshot = (Snapshot &) rawSnapshot;

        setRotation(snapshot.rotation);
        setImageSource(snapshot.imageSource);
        setPath(snapshot.path);
        setColor(snapshot.color);
    }
}
