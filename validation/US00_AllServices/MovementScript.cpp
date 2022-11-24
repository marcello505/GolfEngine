//
// Created by Lucas on 23-11-2022.
//

#include <iostream>
#include "MovementScript.h"
#include "Input/ActionMap.h"
#include "Scene/Components/RigidBody.h"

void MovementScript::onUpdate() {
    _gameObject->get().getComponent<RigidBody>().applyForceToCenter(Vector2(0,0));

    auto lt = _gameObject->get().getLocalTransform();
    auto wt = _gameObject->get().getWorldTransform();

//TODO check if possible to set two same components on one GameObject
//TODO check if possible to just change position  on one GameObject
   if(ActionMap::getActionMap()->isPressed("Left")){
       std::cout << "Left" << std::endl;
   }
    if(ActionMap::getActionMap()->isPressed("Right")){
        std::cout << "Right" << std::endl;

    }
    if(ActionMap::getActionMap()->isPressed("Up")){
        std::cout << "Up" << std::endl;

    }
    if(ActionMap::getActionMap()->isPressed("Down")){
        std::cout << "Down" << std::endl;

    } if(ActionMap::getActionMap()->isPressed("Jump")){
//             wt.position.y =  wt.position.y -100;
//        _gameObject->get().setWorldTransform(wt );
//
//        lt.position.y =  lt.position.y -100;
//        _gameObject->get().setLocalTransform(lt );
        _gameObject->get().setLocalPosition(wt.position );
        _gameObject->get().getComponent<RigidBody>().applyForceToCenter(Vector2(0.4f,0));


        std::cout << "Jump" << std::endl;

    }

}
