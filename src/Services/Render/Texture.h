////
//// Created by conner on 11/9/2022.
////
//
//#ifndef GOLFENGINE_TEXTURE_H
//#define GOLFENGINE_TEXTURE_H
//
////#include <SDL_image.h>
//#include "Services/SDLRenderService.h"
//#include <string>
//#include "../../Scene/Color.h"
//
//
//namespace GolfEngine::Services::Render {
//// Forward declaration
//class SDL_Renderer_Wrapper;
//class SDL_Texture_Wrapper;
//enum class BlendMode;
//
//class Texture {
//public:
//    Texture();
//    ~Texture();
//    Texture(Texture& other) = delete;
//    Texture& operator=(Texture& other) = delete;
//    Texture(Texture&& other) noexcept;
//    Texture& operator-(Texture&& other);
//
//    bool loadFromFileSprite(const std::string& path, SDL_Renderer_Wrapper& renderer);
//
//    void free();
//    void setColor(Color color);
//    void setBlendMode( BlendMode blending );
//    void setAlphaMod( std::uint8_t alpha );
//
//    [[nodiscard]] int width() const;
//    [[nodiscard]] int height() const;
//    [[nodiscard]] size_t fontSize() const;
//    [[nodiscard]] SDL_Texture_Wrapper* texture() const;
//
//
//    private:
//    SDL_Texture_Wrapper* _texture;
//    int _width;
//    int _height;
//
//    };
//
//}
//
//
//#endif //GOLFENGINE_TEXTURE_H
