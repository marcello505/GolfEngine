//
// Created by conner on 11/21/2022.
//

#include "Scene.h"
#include "GameObjects/GameObject.h"
#include "Input/ActionMap.h"
#include "Core/SceneManager.h"

//Add a max replay length so it doesn't keep growing. 36000 frames = 10 minutes
#define MAX_REPLAY_LENGTH 36000

Scene::Scene() {
    _gameObjects.push_back(std::make_unique<GameObject>());
    _rootGameObject = std::make_unique<std::reference_wrapper<GameObject>>(*_gameObjects.back());
}

void Scene::startScene() {
    for(auto& go : _gameObjects)
        if(go->getActive())
            go->onStart();
}

void Scene::updateScene() {
    //Update scene
    for(auto& go : _gameObjects)
        if(go->getActive()){
            go->onUpdate();
            if(&GolfEngine::SceneManager::GetSceneManager().getCurrentScene() != this)
                return;
        }
}



void Scene::startRecordingReplay(const std::vector<std::string>& actionsToLock, bool recordMouse) {
    _replayState = ReplayState::InitializeRecording;
    _replay = Replay{};
    _replay.lockedActions = actionsToLock;
    //If recordMouse is true, initialize the list
    if(recordMouse) _replay.mousePositions = std::vector<std::pair<int, int>>{};
}

void Scene::stopRecordingReplay(){
    _replayState = ReplayState::Idle;
}
void Scene::playReplay(){
    _replayState = ReplayState::InitializePlaying;
}

GameObject& Scene::getRootGameObject() const{
    return _rootGameObject->get();
}

void Scene::saveCurrentState(std::vector<std::unique_ptr<ISnapshot>>& list) {
    list.clear();
    for(int i = 0; i < _gameObjects.size(); ++i){
        if(_gameObjects[i]->isRecordable())
            list.push_back(_gameObjects[i]->saveSnapshot());
    }
}

void Scene::loadCurrentState(std::vector<std::unique_ptr<ISnapshot>>& list) {
    for(int i = 0; i < list.size(); ++i){
        if(_gameObjects[i]->isRecordable())
            _gameObjects[i]->loadSnapshot(*list[i]);
    }
}

void Scene::updateReplay() {
    switch(_replayState){
        //Save current state in replay
        case ReplayState::InitializeRecording:{
            _replayState = ReplayState::Recording;
            saveCurrentState(std::ref(_replay.startingState));
        }

        //Record inputs for replay
        case ReplayState::Recording:{
            auto& actionMap = *ActionMap::getActionMap();
            std::vector<std::pair<bool, bool>> actionsSnapshots {};

            for(auto& actionToLock : _replay.lockedActions){
                actionsSnapshots.emplace_back(actionMap.isPressed(actionToLock), actionMap.isJustPressed(actionToLock));
            }

            if(_replay.mousePositions){
                auto mousePosition = actionMap.getMousePosition();
                _replay.mousePositions.value().emplace_back(mousePosition.x, mousePosition.y);
            }

            _replay.inputs.push_back(actionsSnapshots);

            //Stop recording if recorded inputs exceeds MAX_REPLAY_LENGTH
            if(_replay.inputs.size() >= MAX_REPLAY_LENGTH){
                stopReplay();
            }
            break;
        }

        //Load state from replay
        case ReplayState::InitializePlaying:{
            _replayState = ReplayState::Playing;
            loadCurrentState(std::ref(_replay.startingState));
            _replayFrame = 0;
        }

        //Load inputs from replay
        case ReplayState::Playing:{
            //Check if at the end of the replay
            if(_replayFrame >= _replay.inputs.size()){
                stopReplay();
                break;
            }

            auto& actionMap = *ActionMap::getActionMap();

            //Get inputs of the current frame and then set them
            auto& inputs = _replay.inputs[_replayFrame];
            for(int i = 0; i < inputs.size(); ++i){
                actionMap.setActionPressed(_replay.lockedActions[i], inputs[i].first, inputs[i].second);
            }

            if(_replay.mousePositions){
                auto& mousePos = _replay.mousePositions->at(_replayFrame);
                actionMap.setMousePosition(mousePos.first, mousePos.second);
            }

            //Increase replayFrame
            _replayFrame++;
            break;
        }
        case ReplayState::Idle:
            break;
    }

}

void Scene::stopReplay() {
    _replayState = ReplayState::Idle;

    //Reset inputs
    auto& actionMap = *ActionMap::getActionMap();
    for(auto& actionToLock : _replay.lockedActions){
        actionMap.setActionPressed(actionToLock, false, false);
    }

}

void Scene::saveCurrentSceneState(int slot) {
    auto savedState = _saveStates.find(slot);
    if(savedState != _saveStates.end()){
        _saveStates.erase(savedState);
    }

    std::vector<std::unique_ptr<ISnapshot>> currentState{};
    saveCurrentState(currentState);
    _saveStates.insert({slot, std::move(currentState)});
}

void Scene::loadCurrentSceneState(int slot) {
    auto savedState = _saveStates.find(slot);
    if(savedState != _saveStates.end()){
        loadCurrentState(savedState->second);
    }
}

GameObject& Scene::getGameObjectWithTag(const std::string& tag) const{
    for(auto& go : _gameObjects){
        if(go->tag == tag)
            return *go;
    }
    throw std::runtime_error("No GameObject found with tag: " + tag);
}

std::vector<std::reference_wrapper<GameObject>> Scene::getGameObjectsWithTag(const std::string &tag) {
    std::vector<std::reference_wrapper<GameObject>> foundGameObjects;
    for(auto& go : _gameObjects){
        if(go->tag == tag)
            foundGameObjects.emplace_back(*go);
    }
    return foundGameObjects;
}
