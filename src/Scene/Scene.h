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

    /// Gets the root gameObject of the scene
    /// \return reference to root gameObject
    [[nodiscard]] GameObject& getRootGameObject() const;

    /// Starts a recording of the scene
    /// \param actionsToLock actions that get recorded and are locked when recording is played back
    /// \param recordMouse boolean for recording the mouse or not
    void startRecordingReplay(const std::vector<std::string>& actionsToLock, bool recordMouse = false);

    /// Stops the recording of the scene
    void stopRecordingReplay();

    /// Play the saved recording
    void playReplay();

    /// Stop playing the saved recording
    void stopReplay();

    /// Save a state of the scene
    /// \param slot slot used to save the state to (used to later reference in load function)
    void saveCurrentSceneState(int slot);

    /// Load a saved state of the scene
    /// \param slot slot used to specify which save state to be loaded
    void loadCurrentSceneState(int slot);

    /// Calls onStart on all gameObjects in the scene
    virtual void startScene();

    /// Calls onUpdate on all gameObjects in the scene
    virtual void updateScene();

    /// Executes all the steps needed to handle recordings, wether it is playing a recording or making one.
    /// Should be executed before `updateScene()`
    void updateReplay();

    /// Retrieves a gameObject with the corresponding tag
    /// \param tag to be searched with
    /// \return a reference to a gameObject
    [[nodiscard]] GameObject& getGameObjectWithTag(const std::string& tag) const;

    /// Retrieves a list of gameObjects with the corresponding tag
    /// \param tag to be searched with
    /// \return List of gameObjects reference_wrappers
    std::vector<std::reference_wrapper<GameObject>> getGameObjectsWithTag(const std::string& tag);

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
    /// Creates a new GameObject (with the root gameObject of the scene as parent)
    /// \tparam GO Type of GameObject to be created
    /// \return A reference to the newly created GameObject
    template<typename GO, typename ... Args>
    GO& createNewGameObject(Args ... args){
        return createNewGameObject<GO>(_rootGameObject->get(), std::forward<Args>(args)...);
    }
};


#endif //GOLFENGINE_SCENE_H
