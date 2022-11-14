//
// Created by jaaps on 02/11/2022.
//

#ifndef GOLFENGINE_COMPONENT_H
#define GOLFENGINE_COMPONENT_H


class Component {
protected:
    bool _active;
public:
    virtual void onStart() = 0;
    virtual void onUpdate() = 0;
    virtual void onRemove() = 0;
    virtual bool getActive()  = 0;
    virtual void setActive(bool active) = 0;
};


#endif //GOLFENGINE_COMPONENT_H
