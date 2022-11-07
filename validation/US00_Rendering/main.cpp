//
// Created by conner on 11/7/2022.
//

#include "Services/SDLRenderService.h"
#include <memory>

bool running;
bool fullscreen;
std::unique_ptr<SDLRenderService> rs;

void input();

int main(int argc, char* argv[]){
    rs = std::make_unique<SDLRenderService>();
    fullscreen = false;
    running = true;
    while(running){
        input();

        rs->render();
    }
    return 0;
}

void input(){
    // simple close input check
    SDL_Event e;
    while(SDL_PollEvent(&e)) {
        if(e.type == SDL_QUIT) {
            running = false;
        }
        else if(e.type == SDL_KEYDOWN){
            if(e.key.keysym.sym == SDLK_ESCAPE)
                running = false;
            else if(e.key.keysym.sym == SDLK_RETURN){
                fullscreen = !fullscreen;
                rs->setFullScreen(fullscreen);
            }
        }
    }
}