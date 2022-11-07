//
// Created by conner on 11/2/2022.
//

#include "SDLRenderService.h"
#include <iostream>
#include <algorithm>

SDLRenderService::SDLRenderService()
    : _screenSizeHeight{480}, _screenSizeWidth{640}, _window{nullptr}, _renderer{nullptr}, _fullScreen{false}
{
    // Init SDL
    if(SDL_Init(SDL_INIT_EVERYTHING) < 0){
        std::cerr << "Error: " << SDL_GetError() << std::endl;
    }

    // Create window and renderer
    if(SDL_CreateWindowAndRenderer(_screenSizeWidth, _screenSizeHeight, 0, &_window, &_renderer) < 0){
        std::cerr << "Error: " << SDL_GetError() << std::endl;
    }

    // Set some basic window properties
    SDL_SetWindowTitle(_window, "Hello World");
    SDL_ShowCursor(1); // 0 is disable cursor, 1 is enable
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "2"); // Increases quality with the scaling of textures, 0 nothing, 1 linear filtering, 2 anisotropic filtering
}

SDLRenderService::~SDLRenderService() {
    // Close SDL window and renderer
    SDL_DestroyRenderer(_renderer);
    SDL_DestroyWindow(_window);
}

SDLRenderService::SDLRenderService(SDLRenderService &&other) noexcept {
    // Steal properties
    _window = other._window;
    _renderer = other._renderer;
    _drawables = std::move(other._drawables);
    _cachedTextures = std::move(other._cachedTextures);
    _screenSizeWidth = other._screenSizeWidth;
    _screenSizeHeight = other._screenSizeHeight;
    _fullScreen = other._fullScreen;
}

SDLRenderService &SDLRenderService::operator=(SDLRenderService &&other)  noexcept {
    if(this != &other){
        // Clear and destroy existing properties
        _drawables.clear();
        _cachedTextures.clear();
        SDL_DestroyRenderer(_renderer);
        SDL_DestroyWindow(_window);

        // Steal properties
        _window = other._window;
        _renderer = other._renderer;
        _drawables = std::move(other._drawables);
        _cachedTextures = std::move(other._cachedTextures);
        _screenSizeWidth = other._screenSizeWidth;
        _screenSizeHeight = other._screenSizeHeight;
        _fullScreen = other._fullScreen;

        // Reset pointers of other
        other._window = nullptr;
        other._renderer = nullptr;
    }
    return *this;
}

void SDLRenderService::addDrawable(Drawable* drawable) {
    // Check for valid drawable
    if(drawable == nullptr)
        return;

    _drawables.push_back(drawable);
}

void SDLRenderService::removeDrawable(Drawable* drawable) {
    // Check for valid drawable
    if(drawable == nullptr)
        return;

    // Find the iterator with the given drawable
    auto foundIterator = std::find(_drawables.begin(), _drawables.end(), drawable);
    // If drawable is present in the list, remove it from the list
    if(foundIterator != _drawables.end()){
        _drawables.erase(foundIterator);
    }
}

void SDLRenderService::render() {
    // Clear screen
    SDL_RenderClear(_renderer);

    // Loop through all registered drawables
    for(auto drawable : _drawables){
        auto* renderShape = drawable->getRenderShape();
        switch (renderShape->getType()) {
            case RenderShapeType::RectShape:
                renderRect(reinterpret_cast<RectRenderShape&>(*renderShape));
                break;
            case RenderShapeType::LineShape:
                renderLine(reinterpret_cast<LineRenderShape&>(*renderShape));
                break;
            case RenderShapeType::CircleShape:
            case RenderShapeType::SpriteShape:
            case RenderShapeType::ParticleSystemShape:
                break;
        }
    }

    SDL_SetRenderDrawColor(_renderer, 50, 50, 50, 255);

    // Displays all the updates made in the back buffer
    SDL_RenderPresent(_renderer);
}

void SDLRenderService::setScreenSize(int width, int height) {
    SDL_SetWindowSize(_window, width, height);
}

void SDLRenderService::setFullScreen(bool fullScreen) {
    // Set window flags fullscreen or 0 for no fullscreen
    if(_fullScreen != fullScreen)
        SDL_SetWindowFullscreen(_window, fullScreen? SDL_WINDOW_FULLSCREEN_DESKTOP : 0);
    _fullScreen = fullScreen;
}

int SDLRenderService::screenSizeWidth() const {
    return _screenSizeWidth;
}

int SDLRenderService::screenSizeHeight() const {
    return _screenSizeHeight;
}

bool SDLRenderService::fullScreen() const {
    return _fullScreen;
}

void SDLRenderService::renderRect(RectRenderShape& renderShape) {
    // Set color
    SDL_SetRenderDrawColor(_renderer, renderShape.color().r8, renderShape.color().g8, renderShape.color().b8, 255);

    // Set rect
    SDL_Rect rect;
    rect.x = (int)renderShape.rect().position.x;
    rect.y = (int)renderShape.rect().position.y;
    rect.w = (int)renderShape.rect().size.x;
    rect.h = (int)renderShape.rect().size.y;

    // Draw rect
    SDL_RenderDrawRect(_renderer, &rect);
}

void SDLRenderService::renderLine(LineRenderShape& renderShape) {
    // Set color
    SDL_SetRenderDrawColor(_renderer, renderShape.color().r8, renderShape.color().g8, renderShape.color().b8, 255);

    // Draw Line
    SDL_RenderDrawLineF(_renderer, renderShape.positionA().x, renderShape.positionA().y, renderShape.positionB().x, renderShape.positionB().y);
}

