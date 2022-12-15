//
// Created by marcello on 11/14/22.
//

#include "Services/Singletons/RenderSingleton.h"
#include "BoxCollider.h"
#include "Core/Settings.h"

void BoxCollider::onStart() {
    //Register to Render Service if the PROJECT_SETTINGS_BOOL_RENDER_COLLIDERS key is true in ProjectSettings
    auto& projSett = GolfEngine::Core::getProjectSettings();
    if(projSett.hasBool(PROJECT_SETTINGS_BOOL_RENDER_COLLIDERS) && projSett.getBool(PROJECT_SETTINGS_BOOL_RENDER_COLLIDERS) && GolfEngine::Services::Render::hasService()){
        _isBeingRendered = true;
        GolfEngine::Services::Render::getService()->addDrawable(*this);
    }
}

void BoxCollider::onUpdate() {

}

void BoxCollider::onRemove() {
    if(GolfEngine::Services::Render::hasService() && _isBeingRendered){
        GolfEngine::Services::Render::getService()->removeDrawable(*this);
    }
}

ColliderShapes BoxCollider::getColliderShape() {
    return ColliderShapes::Box;
}

const Vector2& BoxCollider::getShapeExtents() const {
    return _shapeExtents;
}

bool BoxCollider::getActive() {
    return _active;
}

void BoxCollider::setActive(bool active) {
    if(_active == active) return;

    _active = active;
    if(active)
        onStart();
    else
        onRemove();
}

void BoxCollider::setParentGameObject(GameObject& gameObject) {
    _gameObject = gameObject;
}

RenderShape& BoxCollider::getRenderShape() {
    if(_gameObject){
        _rectRenderShape.applyTransform(_gameObject->get().getWorldTransform());
    }
    return _rectRenderShape;
}

void BoxCollider::setColor(Color color) {
    _rectRenderShape.setColor(color);
}

std::unique_ptr<ISnapshot> BoxCollider::saveSnapshot() {
    //Empty implementation on purpose
    return {};
}

void BoxCollider::loadSnapshot(const ISnapshot& rawSnapshot) {
    //Empty implementation on purpose
}
