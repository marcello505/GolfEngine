//
// Created by conner on 11/2/2022.
//

#include "Box2DPhysicsService.h"
#include "Scene/Components/BoxCollider.h"

namespace GolfEngine::Services::Physics{
    Box2DPhysicsService::Box2DPhysicsService() {
    }

    void Box2DPhysicsService::addRigidBody(RigidBody* pRigidBody) {
        // * Error Handling *
        // Check for nullptr
        if(pRigidBody == nullptr){
            return;
        }

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
            //TODO add position
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
                    box.SetAsBox(extents.x / _physicsSpace2WorldSpace, extents.y / _physicsSpace2WorldSpace);
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

    void Box2DPhysicsService::update() {
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

