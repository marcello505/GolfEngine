//
// Created by conner on 11/23/2022.
//

#include "UIScene.h"
#include <Services/SDLRenderService.h>
#include <Services/Singletons/RenderSingleton.h>

#include "ButtonClickScript.h"

void UIScene::build(Scene& scene) const
{
    auto* rs = GolfEngine::Services::Render::getService();
    //create gameobject for button
    auto& root = scene.createNewGameObject<GameObject>();
    auto& GOButton = scene.createNewGameObject<Button>(root,200, 100,
                                                             Vector2(rs->screenSizeWidth() / 2.0,
                                                                     rs->screenSizeHeight() / 3),true,
                                                             "ClickButton", Vector2(0, 0), 0,
                                                             "Click me!", 20, Color(),
                                                             R"(../../game/res/fonts/Rubik-VariableFont_wght.ttf)"
                                                             ,Alignment::Center);

    //bind click logic to button via behavior script
    ButtonClickScript buttonClickScript;
    buttonClickScript.setParentGameObject(GOButton);
    GOButton.addComponent<ButtonClickScript>(buttonClickScript);

    auto& GOButton2 = scene.createNewGameObject<Button>(root,200, 100,
                                                       Vector2(rs->screenSizeWidth() / 2.0,
                                                               rs->screenSizeHeight() / 1.5),true,
                                                       "ClickButton", Vector2(0, 0), 0,
                                                       "And me!", 20, Color(),
                                                       R"(../../game/res/fonts/Rubik-VariableFont_wght.ttf)"
                                                        ,Alignment::Center);



    //create game object for independent piece of text
    auto& GOText = scene.createNewGameObject<Text>(root, Vector2(435, 10), 0, "score: 237",
                                                       30, Color(),
                                                       R"(../../../validation/US08_RenderUIObject/resources/Rubik-VariableFont_wght.ttf)",
                                                       Alignment::Center, false);
}