#include <Core/GameLoop.h>
#include <Services/SDLRenderService.h>
#include <Services/Singletons/RenderSingleton.h>
#include <Scene/GameObjects/UIObject/Text.h>
#include <Scene/GameObjects/UIObject/Button.h>

int main(int argc, char* argv[])
{
    GameLoop gameLoop {};

    gameLoop.useDefaultServices();

    auto* rs = GolfEngine::Services::Render::getService();


    auto* renderShape  = new RectRenderShape(Rect2(Vector2(95,100), Vector2(100, 60)),
                                                 0,
                                                 Vector2(50,70),
                                                 Color(255,255,255,255));
    auto* renderText = new TextRenderShape(Vector2(50, 50), 0, "Click me!",
                                                                                  20 , Color(), R"(..\..\..\validation\US04_RenderFPS\files\roman.ttf)");

    auto* renderButton = new ButtonRenderShape(renderShape, renderText);

    auto btn = new Button(renderButton);

    rs->addDrawable(btn);

    gameLoop.start();

    return 0;
}
