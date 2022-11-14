//
// Created by marce on 02/11/2022.
//

#ifndef GOLFENGINE_SCENE_H
#define GOLFENGINE_SCENE_H
#include <string>
#include <vector>
#include "GameObjects/GameObject.h"

// Forward declaration
class GameObject;

class Scene {
private:
    GameObject* _rootGameObject;
public:
   Scene();
   ~Scene();
   void startRecording(const std::string& actionToLock);
   void stopRecording();
   void playRecording();

   /// Sets rootGameObject
   /// \param gameObject
   void setRootGameObject(GameObject* gameObject);

   /// Returns root GameObject
   /// \return
   GameObject* getRootGameObject();
};


#endif //GOLFENGINE_SCENE_H
