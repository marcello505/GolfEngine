//
// Created by conner on 11/9/2022.
//

#ifndef GOLFENGINE_TEXTURE_H
#define GOLFENGINE_TEXTURE_H

#include <SDL_image.h>
#include <string>

namespace GolfEngine::Services::Render {

class Texture {
public:
    Texture();
    ~Texture();

    bool loadFromFile(const std::string& path, SDL_Renderer& renderer);

    void free();
//    void setColor( Uint8 red, Uint8 green, Uint8 blue );
//    void setBlendMode( SDL_BlendMode blending );
//    void setAlpha( Uint8 alpha );
// void render( int x, int y, SDL_Rect* clip = NULL, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE );

    [[nodiscard]] int width() const;
    [[nodiscard]] int height() const;
    [[nodiscard]] SDL_Texture *texture() const;

private:
    SDL_Texture *_texture;
    int _width;
    int _height;
};

}


#endif //GOLFENGINE_TEXTURE_H
