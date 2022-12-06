//
// Created by marcello on 12/6/22.
//

#ifndef GOLFENGINE_IPERSISTABLE_H
#define GOLFENGINE_IPERSISTABLE_H

#include <memory>

class ISnapshot{

};

class IPersistable{
public:
    virtual std::unique_ptr<ISnapshot> saveSnapshot() = 0;
    virtual void loadSnapshot(const ISnapshot& rawSnapshot) = 0;
};

#endif //GOLFENGINE_IPERSISTABLE_H
