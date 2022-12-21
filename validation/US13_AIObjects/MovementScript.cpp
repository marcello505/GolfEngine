//
// Created by Lucas on 23-11-2022.
//

#include <iostream>
#include "MovementScript.h"
#include "Input/ActionMap.h"
#include "Scene/Components/RigidBody.h"
#include "Scene/Components/SpriteComponent.h"

using namespace GolfEngine::Input;
using namespace GolfEngine::Scene::Components;

void MovementScript::onUpdate() {

    auto lt = _gameObject->get().getLocalTransform();

   if(ActionMap::getActionMap()->isPressed("Left")){
       lt.position.x  = lt.position.x - 1;
       _gameObject->get().getComponent<RigidBody>().setTransform(lt);

   }
    if(ActionMap::getActionMap()->isPressed("Right")){
        lt.position.x  = lt.position.x + 1;
        _gameObject->get().getComponent<RigidBody>().setTransform(lt);

    }
    if(ActionMap::getActionMap()->isPressed("Up")){
        lt.position.y  = lt.position.y - 1;
        _gameObject->get().getComponent<RigidBody>().setTransform(lt);

    }
    if(ActionMap::getActionMap()->isPressed("Down")){
        lt.position.y  = lt.position.y + 1;
        _gameObject->get().getComponent<RigidBody>().setTransform(lt);

    }

}
