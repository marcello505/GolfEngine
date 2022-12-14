//
// Created by conner on 11/21/2022.
//

#ifndef GOLFENGINE_SCENE_H
#define GOLFENGINE_SCENE_H

#include <string>
#include <optional>
#include <vector>

#include "Replay.h"
#include "GameObjects/GameObject.h"

class Scene {
private:
    enum class ReplayState{
        Idle,
        InitializeRecording,
        Recording,
        InitializePlaying,
        Playing
    };

    void saveCurrentState(std::vector<std::unique_ptr<ISnapshot>>& list);
    void loadCurrentState(std::vector<std::unique_ptr<ISnapshot>>& list);

    std::map<int, std::vector<std::unique_ptr<ISnapshot>>> _saveStates;
protected:
    std::vector<std::unique_ptr<GameObject>> _gameObjects;
    std::unique_ptr<std::reference_wrapper<GameObject>> _rootGameObject;

    //Recording fields
    ReplayState _replayState {ReplayState::Idle};
    Replay _replay {};
    int _replayFrame {};
public:
    Scene();

    GameObject& getRootGameObject() const;

    void startRecordingReplay(const std::vector<std::string>& actionsToLock, bool recordMouse = false);
    void stopRecordingReplay();
    void playReplay();
    void stopReplay();

    void saveCurrentSceneState(int slot);
    void loadCurrentSceneState(int slot);

    virtual void startScene();

    /// Executes all the steps needed to handle recordings, wether it is playing a recording or making one.
    /// Should be executed before `updateScene()`
    void updateReplay();
    virtual void updateScene();

    /// Creates a new GameObject
    /// \tparam GO Type of GameObject to be created
    /// \param parent The parent of the GameObject
    /// \return A reference to the newly created GameObject
    template<typename GO, typename ... Args>
    GO& createNewGameObject(GameObject& parent, Args ... args){
        _gameObjects.emplace_back(std::make_unique<GO>(args...));
        GO& newGO = reinterpret_cast<GO&>(*_gameObjects.back());
        newGO.setParent(parent);
        parent.addChild(newGO);
        return newGO;
    }
    template<typename GO, typename ... Args>
    GO& createNewGameObject(Args ... args){
        return createNewGameObject<GO>(_rootGameObject->get(), std::forward<Args>(args)...);
    }
};


#endif //GOLFENGINE_SCENE_H
