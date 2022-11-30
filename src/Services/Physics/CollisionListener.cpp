//
// Created by conner on 11/29/2022.
//

#include "CollisionListener.h"
#include "../../Scene/Components/BehaviourScript.h"

namespace GolfEngine::Services::Physics {
    CollisionListener::CollisionListener(Box2DPhysicsService& box2DPhysicsService) : _physicsService{box2DPhysicsService} {
    }

    void CollisionListener::BeginContact(b2Contact* contact) {
        auto rbA = _physicsService.getRigidBodyWithB2Body(*contact->GetFixtureA()->GetBody());
        auto rbB = _physicsService.getRigidBodyWithB2Body(*contact->GetFixtureB()->GetBody());

        if(rbA && rbB){
            auto gameObjectA = rbA->get().getParentGameObject();
            auto scriptsA = gameObjectA->getComponents<BehaviourScript>();
            for(auto& script : scriptsA){
                script.get().onCollisionEnter(*rbB);
            }

            auto gameObjectB = rbB->get().getParentGameObject();
            auto scriptsB = gameObjectB->getComponents<BehaviourScript>();
            for(auto& script : scriptsB){
                script.get().onCollisionEnter(*rbA);
            }
        }
    }

    void CollisionListener::EndContact(b2Contact* contact) {
        auto rbA = _physicsService.getRigidBodyWithB2Body(*contact->GetFixtureA()->GetBody());
        auto rbB = _physicsService.getRigidBodyWithB2Body(*contact->GetFixtureB()->GetBody());

        if(rbA && rbB){
            auto gameObjectA = rbA->get().getParentGameObject();
            auto scriptsA = gameObjectA->getComponents<BehaviourScript>();
            for(auto& script : scriptsA){
                script.get().onCollisionExit(*rbB);
            }

            auto gameObjectB = rbB->get().getParentGameObject();
            auto scriptsB = gameObjectB->getComponents<BehaviourScript>();
            for(auto& script : scriptsB){
                script.get().onCollisionExit(*rbA);
            }
        }
    }
}