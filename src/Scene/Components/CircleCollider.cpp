#include "CircleCollider.h"
#include "Services/Singletons/RenderSingleton.h"
#include "Core/Settings.h"

namespace GolfEngine::Scene::Components {
    ColliderShapes CircleCollider::getColliderShape() {
        return ColliderShapes::Circle;
    }

    void CircleCollider::onStart() {
        //Register to Render Service if the PROJECT_SETTINGS_BOOL_RENDER_COLLIDERS key is true in ProjectSettings
        auto &projectSettings = GolfEngine::Core::getProjectSettings();
        if (projectSettings.hasBool(PROJECT_SETTINGS_BOOL_RENDER_COLLIDERS) &&
            projectSettings.getBool(PROJECT_SETTINGS_BOOL_RENDER_COLLIDERS) &&
            GolfEngine::Services::Render::hasService() &&
            !GolfEngine::Services::Render::getService()->isRegistered(*this)) {
            GolfEngine::Services::Render::getService()->addDrawable(*this);
        }
    }

    void CircleCollider::onRemove() {
        if (GolfEngine::Services::Render::hasService() &&
            GolfEngine::Services::Render::getService()->isRegistered(*this)) {
            GolfEngine::Services::Render::getService()->removeDrawable(*this);
        }
    }

    bool CircleCollider::getActive() {
        return _active;
    }

    void CircleCollider::setActive(bool active) {
        if (_active == active) return;

        _active = active;
        if (active)
            onStart();
        else
            onRemove();
    }

    void CircleCollider::setParentGameObject(GameObject &gameObject) {
        _gameObject = gameObject;
    }


    Render::RenderShape &CircleCollider::getRenderShape() {
        if (_gameObject) {
            _renderShape.applyTransform(_gameObject->get().getWorldTransform());
        }
        return _renderShape;
    }

    float CircleCollider::getRadius() const {
        return _radius;
    }

    std::unique_ptr<ISnapshot> CircleCollider::saveSnapshot() {
        //Empty on purpose
        return {};
    }

    void CircleCollider::loadSnapshot(const ISnapshot &rawSnapshot) {
        //Empty on purpose
    }

    void CircleCollider::onUpdate() {}
}
