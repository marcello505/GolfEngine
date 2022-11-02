//
// Created by conner on 11/2/2022.
//

#ifndef SPC_PROJECT_CAMERA_H
#define SPC_PROJECT_CAMERA_H

#include "GameObject.h"
#include "../Color.h"

class Camera : public GameObject {
private:
    Color _backgroundColor;
    float _aspectWidth;
    float _aspectHeight;
};


#endif //SPC_PROJECT_CAMERA_H
