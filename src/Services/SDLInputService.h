//
// Created by conner on 11/2/2022.
//

#ifndef SPC_PROJECT_SDLINPUTSERVICE_H
#define SPC_PROJECT_SDLINPUTSERVICE_H

#include "Abstracts/InputService.h"

class SDLInputService : public InputService {
public:
    SDLInputService();
    void handleInputs() override;
};


#endif //SPC_PROJECT_SDLINPUTSERVICE_H
