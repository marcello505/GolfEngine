//
// Created by Lucas on 2-11-2022.
//

#ifndef GOLFENGINE_RECORDING_H
#define GOLFENGINE_RECORDING_H

#include <vector>
#include <map>
#include "../Input/Action.h"

class Recording {
private:
    std::vector<std::byte> _startingSnapshot;
    std::map<int, std::vector<Action>> _inputs

};


#endif //GOLFENGINE_RECORDING_H
