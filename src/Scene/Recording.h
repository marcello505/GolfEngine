//
// Created by Lucas on 2-11-2022.
//

#ifndef GOLFENGINE_RECORDING_H
#define GOLFENGINE_RECORDING_H

#include <vector>
#include <map>
#include "../Input/Action.h"

struct Recording {
    std::vector<std::byte> startingSnapshot;
    std::map<int, std::vector<Action>> inputs;
};


#endif //GOLFENGINE_RECORDING_H
