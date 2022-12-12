//
// Created by conner on 11/21/2022.
//

#ifndef GOLFENGINE_SCENE_H
#define GOLFENGINE_SCENE_H

#include <string>
#include "GameObjects/GameObject.h"
#include <optional>

class Scene {
protected:
    std::vector<std::unique_ptr<GameObject>> _gameObjects;
    std::unique_ptr<std::reference_wrapper<GameObject>> _rootGameObject;
public:
    Scene();

    GameObject& getRootGameObject() const;

    virtual void startRecording(const std::string& actionToLock);
    virtual void stopRecording();
    virtual void playRecording();

    virtual void startScene();
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
