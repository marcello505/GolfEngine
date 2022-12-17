//
// Created by conner on 12/15/2022.
//

#include "HUD.h"
#include "Services/Singletons/RenderSingleton.h"
#include "../scripts/HUDScript.h"
#include <Scene/GameObjects/UIObject/Text.h>

HUD::HUD(Scene &scene) {
    Vector2 windowSize {(float)GolfEngine::Services::Render::getService()->getScreenSizeWidth(), (float)GolfEngine::Services::Render::getService()->getScreenSizeHeight()};

    auto& fpsText = scene.createNewGameObject<Text>((GameObject&)*this, Vector2{windowSize.x * 0.925f, 0}, 0, "",
                                                              20, Color(),
                                                              "res/fonts/Rubik-VariableFont_wght.ttf",
                                                              Alignment::Center, false);

    auto& timeText = scene.createNewGameObject<Text>((GameObject&)*this, Vector2{windowSize.x * 0.025f, 0}, 0, "00:00:00",
                                                    20, Color(),
                                                    "res/fonts/Rubik-VariableFont_wght.ttf",
                                                    Alignment::Center, false);

    auto& highScoreTimeText = scene.createNewGameObject<Text>((GameObject&)*this, Vector2{windowSize.x * 0.025f, windowSize.y * 0.025f}, 0, "00:00:00",
                                                             20, Color(0, 155, 255, 255),
                                                             "res/fonts/Rubik-VariableFont_wght.ttf",
                                                             Alignment::Center, false);

    auto& quitConfirmationText = scene.createNewGameObject<Text>((GameObject&)*this, Vector2{windowSize.x * 0.275f, windowSize.y * 0.4f}, 0, "",
                                                              32, Color(255, 20, 20, 255),
                                                              "res/fonts/Rubik-VariableFont_wght.ttf",
                                                              Alignment::Center, false);

    auto& levelCompleteText = scene.createNewGameObject<Text>((GameObject&)*this, Vector2{windowSize.x * 0.35f, windowSize.y * 0.95f}, 0, "",
                                                                 32, Color(20, 255, 20, 255),
                                                                 "res/fonts/Rubik-VariableFont_wght.ttf",
                                                                 Alignment::Center, false);

    // Add HUB script to update text
    addComponent<HUDScript>(&fpsText, &timeText, &highScoreTimeText, &quitConfirmationText, &levelCompleteText);
}
