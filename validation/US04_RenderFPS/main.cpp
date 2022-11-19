#include <Core/GameLoop.h>
#include <Services/Box2DPhysicsService.h>
#include <Services/SDLRenderService.h>
#include "Services/SDLInputService.h"
#include "Services/Singletons/RenderSingleton.h"
#include "TextDrawable.h"
#include "RectDrawable.h"





int main(int argc, char* argv[]){
    GameLoop gameLoop {};

    gameLoop.useDefaultServices();
    gameLoop.setPhysicsService(nullptr);
    gameLoop.setAudioService(nullptr);




   auto rs = GolfEngine::Services::Render::getService();


    std::string fps =   std::to_string(gameLoop.time->getRenderFps());

    auto* text = new TextDrawable(Vector2(100,50),
                                 Transform(Vector2(0,0), 0,Vector2(1,1)  ), fps, 16 ,Color(), R"(..\..\..\validation\US04_RenderFPS\files\roman.ttf)", gameLoop );
    rs->addDrawable(text);


    gameLoop.start();


}
