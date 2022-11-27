#include <Core/GameLoop.h>
#include <Services/SDLRenderService.h>
#include <Services/Singletons/RenderSingleton.h>
#include <Scene/GameObjects/UIObject/Text.h>
#include <Scene/GameObjects/UIObject/Button.h>
#include <Scene/GameObjects/UIObject/Alignment.h>

int main(int argc, char* argv[])
{
    GameLoop gameLoop {};

    gameLoop.useDefaultServices();

    auto* rs = GolfEngine::Services::Render::getService();

    auto text = new Text(Vector2(0,0), 0, "Click me!",
                         20, Color(),
                         R"(..\..\..\validation\US08_RenderUIObject\resources\Rubik-VariableFont_wght.ttf)",
                         Alignment::Center );

    auto btn = new Button(100,  60, Vector2(50,30), true, text);


    auto scoreText = new Text(Vector2(480,10), 0, "score: 237",
                         30, Color(),
                         R"(..\..\..\validation\US08_RenderUIObject\resources\Rubik-VariableFont_wght.ttf)",
                         Alignment::Center );

    rs->addDrawable(btn);
    rs->addDrawable(scoreText);

    gameLoop.start();

    return 0;
}
