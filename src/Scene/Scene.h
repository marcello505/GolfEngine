//
// Created by marce on 02/11/2022.
//

#ifndef GOLFENGINE_SCENE_H
#define GOLFENGINE_SCENE_H
#include <string>
#include <vector>
#include "GameObjects/GameObject.h"

class Scene {
private:
    GameObject _rootGameObject;
public:
   void startRecording(const std::string& actionToLock);
   void stopRecording();
   void playRecording();
};


#endif //GOLFENGINE_SCENE_H
