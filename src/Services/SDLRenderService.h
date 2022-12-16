//
// Created by conner on 11/2/2022.
//

#ifndef SPC_PROJECT_SDLRENDERSERVICE_H
#define SPC_PROJECT_SDLRENDERSERVICE_H

#include "Abstracts/RenderService.h"
#include <map>
#include <vector>
#include <memory>
#include <string>
#include "../Scene/RenderShape/RectRenderShape.h"
#include "../Scene/RenderShape/LineRenderShape.h"
#include "../Scene/RenderShape/SpriteRenderShape.h"
#include "../Scene/RenderShape/CircleRenderShape.h"
#include "../Scene/RenderShape/ButtonRenderShape.h"
#include "../Scene/RenderShape/TextRenderShape.h"
#include "../Scene/RenderShape/TileMapRenderShape.h"
#include "Scene/GameObjects/Camera.h"


namespace GolfEngine::Services::Render {
// Forward declaration
class Window_Wrapper;
class Renderer_Wrapper;
class Font_Wrapper;
class Texture_Wrapper;

class SDLRenderService : public RenderService {
public:
    SDLRenderService();

    // RAII
    SDLRenderService(SDLRenderService &sdlRenderService) = delete;
    SDLRenderService &operator=(SDLRenderService *other) = delete;
    SDLRenderService(SDLRenderService &&other) = default;
    SDLRenderService &operator=(SDLRenderService &&other) = default;

    /// Sets the title of the window
    /// \param title new title
    void setWindowTitle(const std::string& title) override;

    /// Adds a drawable to the list of registered drawables
    /// \param drawable to be added
    void addDrawable(Drawable& drawable) override;

    /// Removes a drawable from the list of registered drawables
    /// \param drawable to be removed
    void removeDrawable(Drawable& drawable) override;

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

    // Getters, setters
    [[nodiscard]] int screenSizeWidth() const;
    [[nodiscard]] int screenSizeHeight() const;
    [[nodiscard]] bool fullScreen() const;
    [[nodiscard]] std::optional<std::reference_wrapper<Camera>> getMainCamera() const override;
    void setMainCamera(Camera& camera) override;
    [[nodiscard]] int getScreenSizeWidth() const override;
    [[nodiscard]] int getScreenSizeHeight() const override;
    [[nodiscard]] Vector2 getCameraOffset() const override;
private:
    void renderRect(RectRenderShape &renderShape);
    void renderLine(LineRenderShape &renderShape);
    void renderText(TextRenderShape &renderShape);
    void renderCircle(CircleRenderShape &renderShape);
    void renderButton(ButtonRenderShape &renderShape);
    void renderTileMap(TileMapRenderShape &renderShape);

    Texture_Wrapper& loadSprite(const std::string& path);
    void renderSprite(SpriteRenderShape &renderShape);
    Font_Wrapper& loadFont(const std::string &path, size_t fontSize);

    int _screenSizeWidth;
    int _screenSizeHeight;
    bool _fullScreen;
    std::unique_ptr<Window_Wrapper, void(*)(Window_Wrapper*)> _window;
    std::unique_ptr<Renderer_Wrapper, void(*)(Renderer_Wrapper*)> _renderer;
    std::vector<std::reference_wrapper<Drawable>> _drawables;
    std::map<std::string, std::unique_ptr<Texture_Wrapper, void(*)(Texture_Wrapper*)>> _cachedTextures;
    std::map<std::string, std::pair<size_t , std::unique_ptr<Font_Wrapper, void(*)(Font_Wrapper*)>>> _cachedFonts;
    std::optional<std::reference_wrapper<Camera>> _mainCamera;
    Vector2 camOffset;
};

}

#endif //SPC_PROJECT_SDLRENDERSERVICE_H
