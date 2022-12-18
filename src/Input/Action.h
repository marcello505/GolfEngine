//
// Created by olafv on 11/2/2022.
//

#ifndef GOLFENGINE_ACTION_H
#define GOLFENGINE_ACTION_H
#include <string>
struct Action {
    std::string name {};
    std::string keyRefString {};
    bool pressed {};
    bool justInput {};
};
#endif //GOLFENGINE_ACTION_H

