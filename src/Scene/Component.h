//
// Created by jaaps on 02/11/2022.
//

#ifndef GOLFENGINE_COMPONENT_H
#define GOLFENGINE_COMPONENT_H


class Component {
private:
    bool _active;
public:
    void onStart();
    void onUpdate();
    void onRemove();
    bool getActive();
    void setActive(bool active);
};


#endif //GOLFENGINE_COMPONENT_H
