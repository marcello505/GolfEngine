////
//// Created by conner on 11/9/2022.
////
//
//#include "Texture.h"
//#include <SDL.h>
//#include <SDL_image.h>
//#include <SDL_ttf.h>
//#include <iostream>
//#include <SDL_blendmode.h>
//
//namespace GolfEngine::Services::Render {
//    class SDL_Texture_Wrapper{
//
//    };
//
//    enum class BlendMode{
//        BLENDMODE_NONE = 0x00000000,
//        BLENDMODE_BLEND = 0x00000001,
//        BLENDMODE_ADD = 0x00000002,
//        BLENDMODE_MOD = 0x00000004,
//        BLENDMODE_MUL = 0x00000008,
//        BLENDMODE_INVALID = 0x7FFFFFFF
//    };
//
//    Texture::Texture() : _width{0}, _height{0}, _texture{nullptr}{
//    }
//
//    Texture::~Texture() {
//        SDL_DestroyTexture(_texture);
//    }
//
//    Texture::Texture(Texture&& other) noexcept{
//        _texture = other._texture;
//        other._texture = nullptr;
//
//        _width = other._width;
//        _height = other._height;
//    }
//
//    Texture& Texture::operator-(Texture&& other){
//        if(this != &other){
//            SDL_DestroyTexture(_texture);
//
//            _texture = other._texture;
//            _width = other._width;
//            _height = other._height;
//
//            other._texture = nullptr;
//        }
//        return *this;
//    }
//
//    bool Texture::loadFromFileSprite(const std::string& path, SDL_Renderer_Wrapper& renderer) {
//        // Load surface
//        SDL_Surface* surface = IMG_Load(path.c_str());
//        if(surface == nullptr){
//            printf("Unable to load image %s, Error: %s\n", path.c_str(), IMG_GetError());
//            return false;
//        }
//
//        _width = surface->w;
//        _height = surface->h;
//
//        // Create texture from surface
//        _texture = SDL_CreateTextureFromSurface(renderer.renderer, surface);
//        // Free surface memory
//        SDL_FreeSurface(surface);
//        if(_texture == nullptr){
//            printf("Unable to create texture from %s, Error: %s\n", path.c_str(), SDL_GetError());
//            return false;
//        }
//
//        return true;
//    }
//
//    void Texture::free() {
//        SDL_DestroyTexture(_texture);
//    }
//
//    int Texture::width() const {
//        return _width;
//    }
//
//    int Texture::height() const {
//        return _height;
//    }
//
//    SDL_Texture *Texture::texture() const {
//        return _texture;
//    }
//
//    void Texture::setColor(Color color) {
//        SDL_SetTextureColorMod(_texture, color.r8, color.g8, color.b8);
//    }
//
//    void Texture::setBlendMode(BlendMode blending) {
//        SDL_SetTextureBlendMode(_texture, static_cast<SDL_BlendMode>(blending));
//    }
//
//    void Texture::setAlphaMod(std::uint8_t alpha) {
//        Uint8 a {alpha};
//        SDL_SetTextureAlphaMod(_texture, a);
//    }
//
//}
