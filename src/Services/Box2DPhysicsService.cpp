//
// Created by conner on 11/2/2022.
//

#include <cmath>
#include "Box2DPhysicsService.h"
#include "Scene/Components/BoxCollider.h"


namespace GolfEngine::Services::Physics{
    void Box2DPhysicsService::addRigidBody(RigidBody* pRigidBody) {
        // * Error Handling *
        // Check for nullptr
        if(pRigidBody == nullptr){
            return;
        }

        Transform worldTransform {};
        auto& rigidDef = pRigidBody->getRigidBodyDef();
        b2Body* pBody;

        // * Create Box2D Body *
        {
            b2BodyDef bodyDef {};
            //Set box2d equivalent of RigidBodyTypes
            switch(rigidDef.bodyType){
                case RigidBodyTypes::DynamicBody:
                    bodyDef.type = b2_dynamicBody;
                    break;
                case RigidBodyTypes::AreaBody:
                    //TODO figure out how to handle AreaBodies
                    break;
                case RigidBodyTypes::KinematicBody:
                    bodyDef.type = b2_kinematicBody;
                    break;
                case RigidBodyTypes::StaticBody:
                    bodyDef.type = b2_staticBody;
                    break;
            }
            bodyDef.linearDamping = rigidDef.linearDamping;
            bodyDef.angularDamping = rigidDef.angularDamping;
            bodyDef.fixedRotation = rigidDef.fixedRotation;
            bodyDef.gravityScale = rigidDef.gravityScale;

            GameObject* parentGameObject = pRigidBody->getParentGameObject();
            if(parentGameObject != nullptr){
                worldTransform = parentGameObject->getWorldTransform();
                bodyDef.position = {worldTransform.position.x / PhysicsSpaceToWorldSpace, worldTransform.position.y / PhysicsSpaceToWorldSpace};
                bodyDef.angle = worldTransform.rotation * (M_PI / 180.0f);
            }
            //bodyDef.position = pRigidBody->getPosition()
            pBody = _world.CreateBody(&bodyDef);
        }

        // Create Fixtures
        auto colliders = pRigidBody->getColliders();
        for(auto item : colliders){
            b2FixtureDef fixtureDef {};
            fixtureDef.friction = rigidDef.friction;
            fixtureDef.restitution = rigidDef.restitution;
            fixtureDef.density = rigidDef.density;

            b2PolygonShape box {};

            switch(item->getColliderShape()){
                case ColliderShapes::Box:
                    auto* boxItem = (BoxCollider*)item;
                    auto extents = boxItem->getShapeExtents();
                    box.SetAsBox(extents.x / PhysicsSpaceToWorldSpace * worldTransform.scale.x, extents.y / PhysicsSpaceToWorldSpace * worldTransform.scale.y);
                    fixtureDef.shape = &box;
                    break;
            }

            pBody->CreateFixture(&fixtureDef);
        }
    }

    void Box2DPhysicsService::removeRigidBody(RigidBody* pRigidBody) {
        // Is rigidbody registered?
        auto rbIt = _rigidBodies.find(pRigidBody);
        if(rbIt != _rigidBodies.end()){
            _world.DestroyBody(rbIt->second);
            _rigidBodies.erase(rbIt);
        }

    }

    void Box2DPhysicsService::update(GameTic timeStep) {
        // Advance Physics World
        _world.Step(timeStep, _velocityIterations, _positionIterations);

        // Update Rigidbodies
        for(auto item = _rigidBodies.begin(); item != _rigidBodies.end(); ++item){
            b2Body* body = item->second;
            GameObject* parent = item->first->getParentGameObject();

            //Update position and rotation
            if(parent != nullptr){
                auto& position = body->GetPosition();
                float rotation = body->GetAngle() * (M_PI / 180.0f);
                parent->setWorldTransform({
                    {position.x, position.y},
                    rotation,
                    {1.f, 1.f}
                });
            }
        }

    }

    void Box2DPhysicsService::setGravity(const Vector2& vec2) {
        _world.SetGravity({vec2.x, vec2.y});
    }

    std::optional<b2Body*> Box2DPhysicsService::getB2Body(RigidBody* rigidBody) const {
        auto rbIt = _rigidBodies.find(rigidBody);
        if(rbIt != _rigidBodies.end()){
            return rbIt->second;
        }

        return std::nullopt;
    }

    int Box2DPhysicsService::getBodyCount() const {
        return _world.GetBodyCount();
    }
}

