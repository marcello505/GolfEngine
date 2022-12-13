//
// Created by conner on 11/23/2022.
//

#include "UIScene.h"
#include <Services/SDLRenderService.h>
#include <Services/Singletons/RenderSingleton.h>

#include "ButtonClickScript.h"

void UIScene::build(Scene& scene) const
{
    //setup text for button
    auto text = new Text(Vector2(0, 0), 0, "Click me!",
                         20, Color(),
                         R"(../../../validation/US08_RenderUIObject/resources/Rubik-VariableFont_wght.ttf)",
                         Alignment::Center, true);

    auto text2 = new Text(Vector2(0, 0), 0, "And me!",
                         20, Color(),
                         R"(../../../validation/US08_RenderUIObject/resources/Rubik-VariableFont_wght.ttf)",
                         Alignment::Center, true);


    //create gameobject for button
    auto& root = scene.createNewGameObject<GameObject>();
    auto& GOButton = scene.createNewGameObject<Button>(root, 100, 60, Vector2(50, 30), true, text, "ClickButton");
    auto& GOButton2 = scene.createNewGameObject<Button>(root, 100, 60, Vector2(200, 30), true, text2,  "ClickButton");

    //bind click logic to button via behavior script
    ButtonClickScript script;
    script.setParentGameObject(GOButton);
    GOButton.addComponent<ButtonClickScript>(script);
    GOButton2.addComponent<ButtonClickScript>(script);

    //create game object for independent piece of text
    auto& GOText = scene.createNewGameObject<Text>(root, Vector2(535, 10), 0, "score: 237",
                                                       40, Color(),
                                                       R"(../../../validation/US08_RenderUIObject/resources/Rubik-VariableFont_wght.ttf)",
                                                       Alignment::Center, false);
}