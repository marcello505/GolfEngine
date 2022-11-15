#include <SDL.h>
#include <memory>
#include <iostream>
#include "Services/SDLInputService.h"
#include "Services/Singletons/RenderSingleton.h"
#include "Services/SDLRenderService.h"
#include "Core/GameLoop.h"
#include "RectDrawable.h"

bool fullscreen;

bool running;

int main(int argc, char* argv[])
{

    GameLoop gl = GameLoop();
    gl.setRenderService(new GolfEngine::Services::Render::SDLRenderService());
    RenderService* rs = GolfEngine::Services::Render::getService();
    auto *rect = new RectDrawable(Rect2(Vector2(0, 0), Vector2(100, 100)),
                                          Transform(Vector2(200, 200), 0, Vector2(1, 1)),
                                          Vector2(50, 75),
                                          Color(255, 0, 0));
    rs->addDrawable(rect);
    rs->a


    gl.start();
    gl.time->getRenderFps()

    



    return 0;
}