//
// Created by conner on 11/7/2022.
//

#include "Services/SDLRenderService.h"
#include <memory>
#include "RectDrawable.h"
#include "LineDrawable.h"
#include "SpriteDrawable.h"
#include "Services/Singletons/RenderSingleton.h"
#include "CircleDrawable.h"

bool running;
bool fullscreen;
RectDrawable* rect;
CircleDrawable* circle;
SpriteDrawable* sprite;

void input();

int main(int argc, char* argv[]){
    GolfEngine::Services::Render::setService(new GolfEngine::Services::Render::SDLRenderService());
    RenderService* rs = GolfEngine::Services::Render::getService();
    fullscreen = false;
    running = true;
    rect = new RectDrawable(Rect2(Vector2(0,0), Vector2(100,100)),
                            Transform(Vector2(200,200), 0, Vector2(1,1)),
                            Vector2(50,75),
                            Color(255,0,0,255));
    auto* rect2 = new RectDrawable(Rect2(Vector2(0,0), Vector2(100,100)),
                            Transform(Vector2(200,200), 0, Vector2(1,1)),
                            Vector2(),
                            Color(255,0,0));
    sprite = new SpriteDrawable(R"(..\..\..\validation\US00_Rendering\res\player.png)",
                                Vector2(2,2),
                                Rect2(),
                                Transform(Vector2(200,200), 0, Vector2(1,1)),
                                Vector2(120,218),
                                Color(255,255,255,100));

    circle = new CircleDrawable(Vector2(100,0),
                                50,
                                Color(255,0,0, 50),
                                Transform(Vector2(200,200), 0, Vector2(1,1)));

    rs->addDrawable(circle);
    rs->addDrawable(rect);
    //rs->addDrawable(rect2);
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
                circle->move(-10,0);
            }
            else if(e.key.keysym.sym == SDLK_RIGHT){
                rect->rotate(10.0f);
                sprite->rotate(10.0f);
                circle->move(10,0);

            }
            else if(e.key.keysym.sym == SDLK_UP){
                rect->scale(0.1f);
                sprite->scale(0.1f);
                circle->scale(0.1f);
            }
            else if(e.key.keysym.sym == SDLK_DOWN){
                rect->scale(-0.1f);
                sprite->scale(-0.1f);
                circle->scale(-0.1f);
            }
        }
    }
}