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
#include "../Scene/RenderShape/RectRenderShape.h"
#include "../Scene/RenderShape/LineRenderShape.h"

class SDLRenderService : public RenderService {
public:
    SDLRenderService();
    ~SDLRenderService();
    SDLRenderService(SDLRenderService& sdlRenderService) = delete;
    SDLRenderService& operator=(SDLRenderService* other) = delete;
    SDLRenderService(SDLRenderService&& other) noexcept;
    SDLRenderService& operator=(SDLRenderService&& other) noexcept;
    void addDrawable(Drawable* drawable) override;
    void removeDrawable(Drawable* drawable) override;
    void render() override;
    void setScreenSize(int width, int height) override;
    void setFullScreen(bool fullScreen) override;

    // Getters
    [[nodiscard]] int screenSizeWidth() const;
    [[nodiscard]] int screenSizeHeight() const;
    [[nodiscard]] bool fullScreen() const;
private:
    void renderRect(RectRenderShape& renderShape);
    void renderLine(LineRenderShape& renderShape);
private:
    int _screenSizeWidth;
    int _screenSizeHeight;
    bool _fullScreen;
    SDL_Window* _window;
    SDL_Renderer* _renderer;
    std::vector<Drawable*> _drawables;
    std::map<std::string, SDL_Texture*> _cachedTextures;
};


#endif //SPC_PROJECT_SDLRENDERSERVICE_H
