//
// Created by Lucas on 2-11-2022.
//

#ifndef GOLFENGINE_REPLAY_H
#define GOLFENGINE_REPLAY_H

#include <vector>
#include <map>

#include "IPersistable.h"
#include "../Input/Action.h"

struct Replay {
    std::vector<std::unique_ptr<ISnapshot>> startingState {};
    std::vector<std::vector<std::pair<bool, bool>>> inputs {};
    std::vector<std::string> lockedActions {};
    std::optional<std::vector<std::pair<int, int>>> mousePositions {};
};


#endif //GOLFENGINE_REPLAY_H
