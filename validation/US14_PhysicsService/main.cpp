#include <Core/GameLoop.h>
#include <Services/Box2DPhysicsService.h>
#include <Services/SDLRenderService.h>
#include "Services/SDLInputService.h"

int main(int argc, char* argv[]){
    GameLoop gameLoop {};
    gameLoop.useDefaultServices();
    gameLoop.setAudioService(nullptr); // Don't need audio for this test


    gameLoop.start();
}