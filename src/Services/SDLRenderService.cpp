//
// Created by conner on 11/2/2022.
//

#include "SDLRenderService.h"
#include <iostream>
#include <algorithm>

SDLRenderService::SDLRenderService()
    : _screenSizeHeight{480}, _screenSizeWidth{640}, _window{nullptr}, _renderer{nullptr}
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

    SDL_SetRenderDrawColor(_renderer, 50, 50, 50, 255);

    // Displays all the updates made in the back buffer
    SDL_RenderPresent(_renderer);
}

void SDLRenderService::setScreenSize(int width, int height) {
    SDL_SetWindowSize(_window, width, height);
}

void SDLRenderService::setFullScreen(bool fullScreen) {
    // Set window flags fullscreen or 0 for no fullscreen
    SDL_SetWindowFullscreen(_window, fullScreen? SDL_WINDOW_FULLSCREEN_DESKTOP : 0);
}
