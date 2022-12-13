#include <Core/GameLoop.h>
#include <Services/Box2DPhysicsService.h>
#include <Services/SDLRenderService.h>
#include "Services/SDLInputService.h"
#include "Services/Singletons/RenderSingleton.h"
#include "TextDrawable.h"


int main(int argc, char* argv[]){
    GameLoop gameLoop {};

    gameLoop.useDefaultServices();

   auto rs = GolfEngine::Services::Render::getService();

    std::string fps =   std::to_string(gameLoop.time->getRenderFps());


    auto text = TextDrawable(Vector2(100,150),
                                 Transform(Vector2(0,0), 0,Vector2(1,1)  ),  fps, 36 ,Color(), R"(..\..\..\validation\US04_RenderFPS\files\roman.ttf)", gameLoop );


    auto text2 = TextDrawable(Vector2(50,50),
                                 Transform(Vector2(0,0), 0,Vector2(1,1)  ),  fps, 12 ,Color(), R"(..\..\..\validation\US04_RenderFPS\files\roman.ttf)", gameLoop );

    rs->addDrawable(text);
    rs->addDrawable(text2);

    gameLoop.start();

    return 0;

}
