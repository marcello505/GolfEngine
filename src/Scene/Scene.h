//
// Created by marce on 02/11/2022.
//

#ifndef GOLFENGINE_SCENE_H
#define GOLFENGINE_SCENE_H
#include <string>
#include <vector>
#include <memory>
#include "GameObjects/GameObject.h"

// Forward declaration
class GameObject;

class Scene {
private:
    std::unique_ptr<GameObject> _rootGameObject;
public:
   Scene();
   Scene(const Scene& other);
   Scene& operator=(const Scene& other);
   explicit Scene(Scene&& other) = delete;
   Scene& operator=(Scene&& other) = delete;

   void startRecording(const std::string& actionToLock);
   void stopRecording();
   void playRecording();

   void startScene();
   void updateScene();

   void setRootGameObject(GameObject* gameObject);
   GameObject* getRootGameObject();

   /// Creates a new GameObject in the scene
   /// \param gameObject GameObject that should be instantiated in the scene, reference for prefabs and pointer for a new GameObject
   /// \param parent The GameObject that the new GameObject should be created under, nullptr results in root GameObject as parent
   /// \return A pointer reference to the newly created GameObject
   GameObject* createGameObject(GameObject& gameObject, GameObject* parent = nullptr);
   GameObject* createGameObject(GameObject* gameObject, GameObject* parent = nullptr);
};


#endif //GOLFENGINE_SCENE_H
