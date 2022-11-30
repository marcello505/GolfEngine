//
// Created by conner on 11/23/2022.
//

#include "SceneFactory.h"
#include <Services/SDLRenderService.h>
#include <Services/Singletons/RenderSingleton.h>

#include "ButtonClickScript.h"

void SceneFactory::build(Scene& scene) const {

    auto* rs = GolfEngine::Services::Render::getService();

    //setup text for button
    auto text = new Text(Vector2(0, 0), 0, "Click me!",
                         20, Color(),
                         R"(../../../validation/US08_RenderUIObject/resources/Rubik-VariableFont_wght.ttf)",
                         Alignment::Center);
    //setup button
    auto btn = new Button(100, 60, Vector2(50, 30), true, text);


    //setup text
    auto scoreText = new Text(Vector2(480, 10), 0, "score: 237",
                              30, Color(),
                              R"(../../../validation/US08_RenderUIObject/resources/Rubik-VariableFont_wght.ttf)",
                              Alignment::Center);

    //add drawables to renderservice
    rs->addDrawable(*btn);
    rs->addDrawable(*scoreText);


    auto& root = scene.createNewGameObject<GameObject>();

    auto& GOButton = scene.createNewGameObject<Button>(root, btn->_width, btn->_height, btn->_position, true, text);
    ButtonClickScript script;
    script.setParentGameObject(GOButton);
    GOButton.addComponent<ButtonClickScript>(script);

}