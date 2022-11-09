//
// Created by conner on 11/9/2022.
//

#include "Texture.h"
#include <SDL.h>

namespace GolfEngine::Services::Render {

    Texture::Texture() : _width{0}, _height{0}, _texture{nullptr}{
    }

    Texture::~Texture() {
        SDL_DestroyTexture(_texture);
    }

    bool Texture::loadFromFile(const std::string& path, SDL_Renderer& renderer) {
        // Load surface
        SDL_Surface* surface = IMG_Load(path.c_str());
        if(surface == nullptr){
            printf("Unable to load image %s, Error: %s\n", path.c_str(), IMG_GetError());
            return false;
        }

        _width = surface->w;
        _height = surface->h;

        // Create texture from surface
        _texture = SDL_CreateTextureFromSurface(&renderer, surface);
        // Free surface memory
        SDL_FreeSurface(surface);
        if(_texture == nullptr){
            printf("Unable to create texture from %s, Error: %s\n", path.c_str(), SDL_GetError());
            return false;
        }

        return true;
    }

    void Texture::free() {
        SDL_DestroyTexture(_texture);
    }

    int Texture::width() const {
        return _width;
    }

    int Texture::height() const {
        return _height;
    }

    SDL_Texture *Texture::texture() const {
        return _texture;
    }

}
