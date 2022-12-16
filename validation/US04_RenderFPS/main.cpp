#include <Core/GameLoop.h>
#include <Services/Box2DPhysicsService.h>
#include <Services/SDLRenderService.h>
#include "Services/SDLInputService.h"
#include "Services/Singletons/RenderSingleton.h"
    auto text = TextDrawable(Vector2(100,50),
                                 Transform(Vector2(0,0), 0,Vector2(1,1)  ),  fps, 36 ,Color(), R"(..\..\..\validation\US04_RenderFPS\files\roman.ttf)", gameLoop
#include "TextDrawable.h"


int main(int argc, char* argv[]){
    GameLoop gameLoop {};

    gameLoop.useDefaultServices();

   auto rs = GolfEngine::Services::Render::getService();

    std::string fps =   std::to_string(gameLoop.time->getRenderFps());
 );

    rs->addDrawable(text);

    gameLoop.start();

    return 0;

}
