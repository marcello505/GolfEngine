//
// Created by conner on 11/9/2022.
//

#ifndef GOLFENGINE_TEXTURE_H
#define GOLFENGINE_TEXTURE_H

#include <SDL_image.h>
#include <string>
#include "../../Scene/Color.h"

using namespace GolfEngine::Scene;

namespace GolfEngine::Services::Render {

class Texture {
public:
    Texture();
    ~Texture();
    Texture(Texture& other) = delete;
    Texture& operator=(Texture& other) = delete;
    Texture(Texture&& other) noexcept;
    Texture& operator-(Texture&& other);

    bool loadFromFileSprite(const std::string& path, SDL_Renderer& renderer);

    void free();
    void setColor(Color color);
    void setBlendMode( SDL_BlendMode blending );
    void setAlphaMod( Uint8 alpha );

    [[nodiscard]] int width() const;
    [[nodiscard]] int height() const;
    [[nodiscard]] size_t fontSize() const;
    [[nodiscard]] SDL_Texture* texture() const;


    private:
    SDL_Texture* _texture;
    int _width;
    int _height;

    };

}


#endif //GOLFENGINE_TEXTURE_H
