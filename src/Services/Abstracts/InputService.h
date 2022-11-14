//
// Created by conner on 11/2/2022.
//

#ifndef SPC_PROJECT_INPUTSERVICE_H
#define SPC_PROJECT_INPUTSERVICE_H

class InputService {
public:
    virtual void handleInputs() = 0;
    bool hasRecievedQuitSignal();
};


#endif //SPC_PROJECT_INPUTSERVICE_H
