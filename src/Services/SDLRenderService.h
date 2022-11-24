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
#include <SDL_ttf.h>
#include "../Scene/RenderShape/RectRenderShape.h"
#include "../Scene/RenderShape/LineRenderShape.h"
#include "../Scene/RenderShape/SpriteRenderShape.h"
#include "../Scene/RenderShape/CircleRenderShape.h"
#include "../Scene/RenderShape/ButtonRenderShape.h"
#include "Render/Texture.h"
#include "../Scene/RenderShape/TextRenderShape.h"

namespace GolfEngine::Services::Render {

class SDLRenderService : public RenderService {
public:
    SDLRenderService();
    ~SDLRenderService();

    // RAII
    SDLRenderService(SDLRenderService &sdlRenderService) = delete;
    SDLRenderService &operator=(SDLRenderService *other) = delete;
    SDLRenderService(SDLRenderService &&other) noexcept;
    SDLRenderService &operator=(SDLRenderService &&other) noexcept;

    /// Adds a drawable to the list of registered drawables
    /// \param drawable to be added
    void addDrawable(Drawable *drawable) override;

    /// Removes a drawable from the list of registered drawables
    /// \param drawable to be removed
    void removeDrawable(Drawable *drawable) override;

    /// Renders all drawables in registered drawable list
    void render() override;

    /// Sets the window size to the given sizes
    /// \param width new width of window
    /// \param height new height of window
    void setScreenSize(int width, int height) override;

    /// Sets the window to fullscreen
    /// \param fullScreen true is fullscreen
    void setFullScreen(bool fullScreen) override;

    // Getters
    [[nodiscard]] int screenSizeWidth() const;
    [[nodiscard]] int screenSizeHeight() const;
    [[nodiscard]] bool fullScreen() const;
private:
    void renderRect(RectRenderShape &renderShape);
    void renderLine(LineRenderShape &renderShape);
    void renderText(TextRenderShape &renderShape);
    void renderCircle(CircleRenderShape &renderShape);
    void renderButton(ButtonRenderShape &renderShape);

    Texture* loadSprite(const std::string& path);
    void renderSprite(SpriteRenderShape &renderShape);
    void clearTextureCache();
    void clearFontCache();

    int _screenSizeWidth;
    int _screenSizeHeight;
    bool _fullScreen;
    SDL_Window *_window;
    SDL_Renderer *_renderer;
    std::vector<Drawable *> _drawables;
    std::map<std::string, Texture*> _cachedTextures;
    std::map<std::string, std::pair<size_t , TTF_Font*>> _cachedFonts;

    TTF_Font * loadFont(const std::string &path, size_t fontSize);

};

}

#endif //SPC_PROJECT_SDLRENDERSERVICE_H
