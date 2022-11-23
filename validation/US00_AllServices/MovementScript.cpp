//
// Created by Lucas on 23-11-2022.
//

#include <iostream>
#include "MovementScript.h"

void MovementScript::onUpdate() {
    std::cout << "Test";
    _gameObject->get().name = "MovementScript";


}
