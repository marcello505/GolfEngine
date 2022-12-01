//
// Created by conner on 11/29/2022.
//

#include "CollisionListener.h"
#include "../../Scene/Components/BehaviourScript.h"

namespace GolfEngine::Services::Physics {
    CollisionListener::CollisionListener(Box2DPhysicsService& box2DPhysicsService) : _physicsService{box2DPhysicsService} {
    }

    void CollisionListener::BeginContact(b2Contact* contact) {
        auto rbA {_physicsService.getRigidBodyWithB2Body(*contact->GetFixtureA()->GetBody())};
        auto rbB {_physicsService.getRigidBodyWithB2Body(*contact->GetFixtureB()->GetBody())};

        if(rbA && rbB){
            // Get all attached script components from Object A and B
            auto gameObjectA {rbA->get().getParentGameObject()};
            auto scriptsA {gameObjectA->getComponents<BehaviourScript>()};
            auto gameObjectB {rbB->get().getParentGameObject()};
            auto scriptsB {gameObjectB->getComponents<BehaviourScript>()};

            // Check if one of the two rigidbodies is an areabody type
            bool isArea {contact->GetFixtureA()->IsSensor() || contact->GetFixtureB()->IsSensor()};

            // Call area or collision methods on all attached scripts
            if(isArea){
                for(auto& script : scriptsA){
                    script.get().onAreaEnter(*rbB);
                }

                for(auto& script : scriptsB){
                    script.get().onAreaEnter(*rbA);
                }
            }
            else {
                for(auto& script : scriptsA){
                    script.get().onCollisionEnter(*rbB);
                }

                for(auto& script : scriptsB){
                    script.get().onCollisionEnter(*rbA);
                }
            }
        }
    }

    void CollisionListener::EndContact(b2Contact* contact) {
        auto rbA {_physicsService.getRigidBodyWithB2Body(*contact->GetFixtureA()->GetBody())};
        auto rbB {_physicsService.getRigidBodyWithB2Body(*contact->GetFixtureB()->GetBody())};

        if(rbA && rbB){
            // Get all attached script components from Object A and B
            auto gameObjectA {rbA->get().getParentGameObject()};
            auto scriptsA {gameObjectA->getComponents<BehaviourScript>()};
            auto gameObjectB {rbB->get().getParentGameObject()};
            auto scriptsB {gameObjectB->getComponents<BehaviourScript>()};

            // Check if one of the two rigidbodies is an areabody type
            bool isArea {contact->GetFixtureA()->IsSensor() || contact->GetFixtureB()->IsSensor()};

            // Call area or collision methods on all attached scripts
            if(isArea){
                for(auto& script : scriptsA){
                    script.get().onAreaExit(*rbB);
                }

                for(auto& script : scriptsB){
                    script.get().onAreaExit(*rbA);
                }
            }
            else {
                for(auto& script : scriptsA){
                    script.get().onCollisionExit(*rbB);
                }

                for(auto& script : scriptsB){
                    script.get().onCollisionExit(*rbA);
                }
            }
        }
    }
}