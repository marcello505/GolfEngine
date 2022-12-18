//
// Created by conner on 11/2/2022.
//

#ifndef SPC_PROJECT_SDLRENDERSERVICE_H
#define SPC_PROJECT_SDLRENDERSERVICE_H

#include "Abstracts/RenderService.h"
#include <SDL.h>
#include <map>
#include <vector>
#include <memory>
#include <string>
#include <SDL_ttf.h>
#include "../Scene/RenderShape/RectRenderShape.h"
#include "../Scene/RenderShape/LineRenderShape.h"
#include "../Scene/RenderShape/SpriteRenderShape.h"
#include "../Scene/RenderShape/CircleRenderShape.h"
#include "../Scene/RenderShape/ButtonRenderShape.h"
#include "Render/Texture.h"
#include "../Scene/RenderShape/TextRenderShape.h"
#include "../Scene/RenderShape/TileMapRenderShape.h"
#include "Scene/GameObjects/Camera.h"

namespace GolfEngine::Services::Render {

class SDLRenderService : public RenderService {
public:
    SDLRenderService();

    SDLRenderService(SDLRenderService &sdlRenderService) = delete;
    SDLRenderService &operator=(SDLRenderService *other) = delete;

    /// Sets the title of the window
    /// \param title new title
    void setWindowTitle(const std::string& title) override;

    /// Adds a drawable to the list of registered drawables
    /// \param drawable to be added
    void addDrawable(Drawable& drawable) override;

    /// Removes a drawable from the list of registered drawables
    /// \param drawable to be removed
    void removeDrawable(Drawable& drawable) override;

    /// Checks whether a drawable is registered
    /// \param drawable to be checked
    /// \return True if it is registered
    bool isRegistered(Drawable &drawable) override;

    /// Renders all drawables in registered drawable list
    void render() override;

    /// Sets the window size to the given sizes
    /// \param width new width of window
    /// \param height new height of window
    void setScreenSize(int width, int height) override;

    /// Sets the window to fullscreen
    /// \param fullScreen true is fullscreen
    void setFullScreen(bool fullScreen) override;

    /// Registers a camera to be used in the scene
    /// \param camera reference to camera, can be null to clear any camera
    void setMainCamera(const std::optional<std::reference_wrapper<Camera>>& camera) override;

    // Getters
    [[nodiscard]] int screenSizeWidth() const override;
    [[nodiscard]] int screenSizeHeight() const override;
    [[nodiscard]] bool fullScreen() const override;
    [[nodiscard]] Vector2 getCameraOffset() const override;
    [[nodiscard]] std::optional<std::reference_wrapper<Camera>> getMainCamera() const override;
private:
    void renderRect(RectRenderShape &renderShape);
    void renderLine(LineRenderShape &renderShape);
    void renderText(TextRenderShape &renderShape);
    void renderCircle(CircleRenderShape &renderShape);
    void renderButton(ButtonRenderShape &renderShape);
    void renderTileMap(TileMapRenderShape &renderShape);

    Texture& loadSprite(const std::string& path);
    void renderSprite(SpriteRenderShape &renderShape);
    TTF_Font& loadFont(const std::string &path, size_t fontSize);

    int _screenSizeWidth;
    int _screenSizeHeight;
    bool _fullScreen;
    std::unique_ptr<SDL_Window, void(*)(SDL_Window*)> _window;
    std::unique_ptr<SDL_Renderer, void(*)(SDL_Renderer*)> _renderer;
    std::vector<std::reference_wrapper<Drawable>> _drawables;
    std::map<std::string, std::unique_ptr<Texture>> _cachedTextures;
    std::map<std::pair<std::string ,size_t >,  std::unique_ptr<TTF_Font, void(*)(TTF_Font*)>> _cachedFonts;

    std::optional<std::reference_wrapper<Camera>> _mainCamera;
    Vector2 camOffset;
};

}

#endif //SPC_PROJECT_SDLRENDERSERVICE_H
