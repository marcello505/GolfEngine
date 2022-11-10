//
// Created by conner on 11/7/2022.
//

#include "Services/SDLRenderService.h"
#include <memory>
#include "RectDrawable.h"
#include "LineDrawable.h"
#include "SpriteDrawable.h"
#include "Services/Singletons/RenderSingleton.h"

bool running;
bool fullscreen;
RectDrawable* rect;
SpriteDrawable* sprite;

void input();

int main(int argc, char* argv[]){
    GolfEngine::Services::Render::setService(new GolfEngine::Services::Render::SDLRenderService());
    RenderService* rs = GolfEngine::Services::Render::getService();
    fullscreen = false;
    running = true;
    rect = new RectDrawable(Rect2(Vector2(0,0), Vector2(100,100)),
                            Transform(Vector2(200,200), 0, Vector2(1,1.5)),
                            Vector2(50,75),
                            Color(255,0,0));
//    auto* line = new LineDrawable(Vector2(10, 100), Vector2(250,400), Color(0,255,0));
    sprite = new SpriteDrawable(R"(D:\Avans\Jaar4\MinorSPC\SPC-Project\validation\US00_Rendering\res\player.png)",
                                Vector2(2,2),
                                Rect2(),
                                Transform(Vector2(200,200), 0, Vector2(1,1)),
                                Vector2(120,218));
    rs->addDrawable(rect);
//    rs->addDrawable(line);
    rs->addDrawable(sprite);
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
            else if(e.key.keysym.sym == SDLK_LEFT){
                rect->rotate(-10.0f);
                sprite->rotate(-10.0f);
            }
            else if(e.key.keysym.sym == SDLK_RIGHT){
                rect->rotate(10.0f);
                sprite->rotate(10.0f);
            }
            else if(e.key.keysym.sym == SDLK_UP){
                rect->scale(0.1f);
                sprite->scale(0.1f);
            }
            else if(e.key.keysym.sym == SDLK_DOWN){
                rect->scale(-0.1f);
                sprite->scale(-0.1f);
            }
        }
    }
}