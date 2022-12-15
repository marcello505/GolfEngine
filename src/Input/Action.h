//
// Created by olafv on 11/2/2022.
//

#ifndef GOLFENGINE_ACTION_H
#define GOLFENGINE_ACTION_H
#include <string>
class Action {
public:
    std::string name {};
    std::string keyRefString;
    bool pressed {};
    bool justInput {};
/*    bool operator==(const Action& other) const
    {
        return (name == other.name);
    }*/
};
#endif //GOLFENGINE_ACTION_H

