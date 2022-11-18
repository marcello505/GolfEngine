#include <SDL.h>
#include <memory>
#include <iostream>
#include "Services/SDLInputService.h"
#include "Services/Singletons/RenderSingleton.h"
#include "Services/SDLRenderService.h"
#include "Core/GameLoop.h"
#include "RectDrawable.h"
#include "TextDrawable.h"

bool fullscreen;

bool running = true;
void input();
TextDrawable* text;
TextDrawable* text2;
RenderService* rs;

int main(int argc, char* argv[])
{

    GameLoop gl = GameLoop();
    gl.setRenderService(new GolfEngine::Services::Render::SDLRenderService());
    rs  = GolfEngine::Services::Render::getService();
    auto *rect = new RectDrawable(Rect2(Vector2(0, 0), Vector2(100, 100)),
                                          Transform(Vector2(200, 200), 0, Vector2(1, 1)),
                                          Vector2(50, 75),
                                          Color(255, 0, 0));


    text = new TextDrawable(Vector2(0,0),
                                 Transform(Vector2(0,0), 45,Vector2(1,1)  ), "Dit is SDL_rendered text", 20 ,Color(), R"(..\..\..\validation\US04_RenderFPS\files\roman.ttf)" );


    text2= new TextDrawable(Vector2(50,50),
                                 Transform(Vector2(0,0), 45,Vector2(1,1)  ), "Dit is SDL_rendered text", 50 ,Color(), R"(..\..\..\validation\US04_RenderFPS\files\roman.ttf)" );

//    rs->addDrawable(rect);
    rs->addDrawable(text);
    rs->addDrawable(text2);


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
                text->rotate(-10.0f);
            }
            else if(e.key.keysym.sym == SDLK_RIGHT){
                text->rotate(10.0f);

            }
            else if(e.key.keysym.sym == SDLK_UP){
                text->move(0, -10);

            }
            else if(e.key.keysym.sym == SDLK_DOWN){
                text->move(0, 10);
            }
            else if(e.key.keysym.sym == SDLK_t){
        rs->removeDrawable(text);


                text = new TextDrawable(Vector2(100,100),
                                       Transform(Vector2(0,0), 0,Vector2(1,1)  ), "Dit is nieuwe tekst", 20 ,Color(), R"(..\..\..\validation\US04_RenderFPS\files\roman.ttf)" );

                rs->addDrawable(text);
            }
            else if(e.key.keysym.sym == SDLK_y){
                rs->removeDrawable(text);

                text = new TextDrawable(Vector2(100,100),
                                        Transform(Vector2(0,0), 0,Vector2(1,1)  ), "Dit is SDL_rendered text", 20 ,Color(), R"(..\..\..\validation\US04_RenderFPS\files\roman.ttf)" );
                rs->addDrawable(text);

            }

        }
    }
}
