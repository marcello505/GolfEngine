//
// Created by Lucas on 23-11-2022.
//

#include <iostream>
#include "ButtonClickScript.h"
#include "Input/ActionMap.h"
#include "Scene/GameObjects/UIObject/Button.h"
#include <utility>

void ButtonClickScript::onUpdate() {

      auto& btn = getParentGameObject<Button>();

      std::pair<int, int> buttonXRange(btn._position.x,btn._position.x + btn._width );

      std::pair<int, int> buttonYRange(btn._position.y,btn._position.y + btn._height );


      if( ActionMap::getActionMap()->isJustPressed("ClickButton")) {

          auto mousePos = ActionMap::getActionMap()->getMousePosition();
          mousePos.x += buttonXRange.first;
          mousePos.y += buttonYRange.first;

          if( mousePos.x >= buttonXRange.first && mousePos.x <= buttonXRange.second &&
          mousePos.y >= buttonYRange.first &&mousePos.y <= buttonYRange.second){
              btn.onClick();
          }

      }


}


