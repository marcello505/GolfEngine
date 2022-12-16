
// Engine includes
#include "Core/GameLoop.h"
#include "Services/Singletons/RenderSingleton.h"

//TODO find something to fix this
#include <SDL.h>

// Game includes
#include "scenes/PlayerTestScene.h"
#include "scenes/MainMenuScene.h"
#include "scenes/SelectLevelScene.h"
#include "scenes/SettingsScene.h"
#include "Scene/Components/AudioSource.h"


int main(int argc, char* argv[]){
    GameLoop gameLoop {};
    gameLoop.useDefaultServices();

    //Set up controls
    auto* actionMap = ActionMap::getActionMap();
    actionMap->addAction("playerLeft");
    actionMap->addInputKeyToAction("playerLeft", InputKey::Key_A);
    actionMap->addAction("playerRight");
    actionMap->addInputKeyToAction("playerRight", InputKey::Key_D);
    actionMap->addAction("playerUp");
    actionMap->addInputKeyToAction("playerUp", InputKey::Key_W);
    actionMap->addAction("playerDown");
    actionMap->addInputKeyToAction("playerDown", InputKey::Key_S);
    actionMap->addAction("playerShoot");
    actionMap->addInputKeyToAction("playerShoot", InputKey::Mouse_Left);

    //Set up recording controls
    actionMap->addAction("startRecordingReplay");
    actionMap->addInputKeyToAction("startRecordingReplay", InputKey::Key_I);
    actionMap->addAction("stopRecordingReplay");
    actionMap->addInputKeyToAction("stopRecordingReplay", InputKey::Key_O);
    actionMap->addAction("playReplay");
    actionMap->addInputKeyToAction("playReplay", InputKey::Key_P);

    ActionMap::getActionMap()->addAction("clickButton");
    ActionMap::getActionMap()->addInputKeyToAction("clickButton", Mouse_Left);

    //Render initialization
    GolfEngine::Services::Render::getService()->setScreenSize(1920, 1080);

    //Audio initialisation
    GolfEngine::Scene::Components::AudioSource mgsThemeSound {R"(../../game/res/audio/mgs-theme.flac)", true};
/*    mgsThemeSound.play(true);*/


    //Scene initialization
    auto& sceneManager = GolfEngine::SceneManager::GetSceneManager();
    sceneManager.addSceneFactory<PlayerTestScene>("playerTest");
    sceneManager.addSceneFactory<MainMenuScene>("mainMenu");
    sceneManager.addSceneFactory<SelectLevelScene>("selectLevel");
    sceneManager.addSceneFactory<SettingsScene>("settings");
    sceneManager.loadScene("mainMenu");

    gameLoop.start();
    return 0;
}