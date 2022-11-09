//
// Created by conner on 11/7/2022.
//

#include "Services/SDLRenderService.h"
#include <memory>
#include "RectDrawable.h"
#include "LineDrawable.h"
#include "Services/Singletons/RenderSingleton.h"

bool running;
bool fullscreen;
RectDrawable* rect;

void input();

int main(int argc, char* argv[]){
    GolfEngine::Services::Render::setService(new SDLRenderService());
    RenderService* rs = GolfEngine::Services::Render::getService();
    fullscreen = false;
    running = true;
    rect = new RectDrawable(Rect2(Vector2(0,0), Vector2(50,50)), Transform(Vector2(200,100), 0, Vector2(1,1)), Color(255,0,0));
    auto* line = new LineDrawable(Vector2(10, 100), Vector2(110,125), Color(0,255,0));
    rs->addDrawable(rect);
    rs->addDrawable(line);
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
                GolfEngine::Services::Render::getService()->setFullScreen(fullscreen);
            }
            else if(e.key.keysym.sym == SDLK_LEFT)
                rect->rotate(-0.1f);
            else if(e.key.keysym.sym == SDLK_RIGHT)
                rect->rotate(0.1f);
        }
    }
}