//
// Created by conner on 11/2/2022.
//

#ifndef SPC_PROJECT_SDLRENDERSERVICE_H
#define SPC_PROJECT_SDLRENDERSERVICE_H

#include "Abstracts/RenderService.h"
#include <SDL.h>
#include <map>
#include <vector>
#include <string>

class SDLRenderService : public RenderService {
public:
    SDLRenderService();
    void addDrawable(const Drawable& drawable) override;
    void removeDrawable(const Drawable& drawable) override;
    void render() override;
    void setScreenSize(int width, int height) override;
private:
    int _screenSizeWidth;
    int _screenSizeHeight;
    SDL_Window* _window;
    SDL_Renderer* _renderer;
    std::vector<Drawable*> _drawables;
    std::map<const std::string&, SDL_Texture*> _cachedTextures;
};


#endif //SPC_PROJECT_SDLRENDERSERVICE_H
