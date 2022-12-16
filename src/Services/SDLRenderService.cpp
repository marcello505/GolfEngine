//
// Created by conner on 11/2/2022.
//

#include "SDLRenderService.h"
#include <cmath>
#include <iostream>
#include <algorithm>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <optional>

namespace GolfEngine::Services::Render {

    class Window_Wrapper{
    public:
        explicit Window_Wrapper(SDL_Window* w) : window{w}{}
        SDL_Window* window;
    };

    void SDL_DestroyWindowWrapper(Window_Wrapper* window){
        SDL_DestroyWindow(window->window);
        delete window;
    }

    class Renderer_Wrapper{
    public:
        explicit Renderer_Wrapper(SDL_Renderer* r) : renderer{r}{}
        SDL_Renderer* renderer;
    };

    void SDL_DestroyRendererWrapper(Renderer_Wrapper* renderer){
        SDL_DestroyRenderer(renderer->renderer);
        delete renderer;
    }

    class Font_Wrapper{
    public:
        explicit Font_Wrapper(TTF_Font* f) : font{f}{}
        TTF_Font* font;
    };

    void TTF_CloseFontWrapper(Font_Wrapper* font){
        TTF_CloseFont(font->font);
        delete font;
    }

    class Texture_Wrapper{
    public:
        explicit Texture_Wrapper(SDL_Texture* t, int w, int h) : texture{t}, width{w}, height{h}{}
        SDL_Texture* texture;
        int width, height;
    };

    void SDL_DestroyTextureWrapper(Texture_Wrapper* texture){
        SDL_DestroyTexture(texture->texture);
        delete texture;
    }

    SDLRenderService::SDLRenderService()
            : _screenSizeHeight{480}, _screenSizeWidth{640}, _window{nullptr, nullptr}, _renderer{nullptr, nullptr}, _fullScreen{false} {
        // Init SDL
        if (SDL_Init(SDL_INIT_VIDEO) < 0) {
            std::cerr << "Error: " << SDL_GetError() << std::endl;
        }

        //Initialize PNG AND JPG loading
        if(IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG) < 0) {
            printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
        }

        //initialize TTF support
        if(TTF_Init() == -1){
            printf( "SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError() );
        }

        SDL_Window* window;
        SDL_Renderer* renderer;

        // Create window and renderer
        if (SDL_CreateWindowAndRenderer(_screenSizeWidth, _screenSizeHeight, 0, &window, &renderer) < 0) {
            std::cerr << "Error: " << SDL_GetError() << std::endl;
        }

        // Wrap window and renderer in a unique pointer
        std::unique_ptr<Window_Wrapper, void(*)(Window_Wrapper*)> window_wrapper (new Window_Wrapper{window}, SDL_DestroyWindowWrapper);
        _window = std::move(window_wrapper);
        std::unique_ptr<Renderer_Wrapper, void(*)(Renderer_Wrapper*)> renderer_wrapper (new Renderer_Wrapper{renderer}, SDL_DestroyRendererWrapper);
        _renderer = std::move(renderer_wrapper);

        // Set some basic window properties
        SDL_SetWindowTitle(_window->window, "Hello World");
        SDL_ShowCursor(1); // 0 is disable cursor, 1 is enable
        SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY,
                    "0"); // Increases quality with the scaling of textures, 0 nothing, 1 linear filtering, 2 anisotropic filtering

        //Makes alpha blending possible(used for opacity)
        SDL_SetRenderDrawBlendMode(_renderer->renderer, SDL_BLENDMODE_BLEND);
    }

    void SDLRenderService::addDrawable(Drawable& drawable) {
        _drawables.emplace_back(std::ref(drawable));
    }

    void SDLRenderService::removeDrawable(Drawable& drawable) {
        _drawables.erase(std::find_if(_drawables.begin(), _drawables.end(), [&](const std::reference_wrapper<Drawable> &d) {
            return &d.get() == &drawable;
        }));
    }

    void SDLRenderService::render() {
        // Clear screen
        SDL_RenderClear(_renderer->renderer);

        if(_mainCamera){
            camOffset.x = _mainCamera->get().getWorldTransform().position.x - (int)(_screenSizeWidth/2);
            camOffset.y = _mainCamera->get().getWorldTransform().position.y - (int)(_screenSizeHeight/2);
        }
        else {
            camOffset.x = camOffset.y = 0;
        }

        // Loop through all registered drawables
        for (auto drawable: _drawables) {

            auto& renderShape = drawable.get().getRenderShape();
            switch (renderShape.getType()) {
                case RenderShapeType::RectShape:
                    renderRect(dynamic_cast<RectRenderShape&>(renderShape));
                    break;
                case RenderShapeType::LineShape:
                    renderLine(dynamic_cast<LineRenderShape&>(renderShape));
                    break;
                case RenderShapeType::SpriteShape:
                    renderSprite(dynamic_cast<SpriteRenderShape&>(renderShape));
                    break;
                case RenderShapeType::CircleShape:
                    renderCircle(dynamic_cast<CircleRenderShape&>(renderShape));
                    break;
                case RenderShapeType::TextRenderShape:
                    renderText(dynamic_cast<TextRenderShape&>(renderShape));
                    break;
                case RenderShapeType::ParticleSystemShape:
                    break;
                case RenderShapeType::ButtonRenderShape:
                    renderButton(dynamic_cast<ButtonRenderShape&>(renderShape));
                    break;
                case RenderShapeType::TileMapRenderShape:
                    renderTileMap(dynamic_cast<TileMapRenderShape&>(renderShape));
                    break;
            }
        }

        // Set the background color
        if(_mainCamera){
            Color bgColor {_mainCamera->get().backgroundColor()};
            SDL_SetRenderDrawColor(_renderer->renderer, bgColor.r8, bgColor.g8, bgColor.b8, bgColor.a);
        }
        else
            SDL_SetRenderDrawColor(_renderer->renderer, 50, 50, 50, 255);

        // Displays all the updates made in the back buffer
        SDL_RenderPresent(_renderer->renderer);
    }

    void SDLRenderService::setScreenSize(int width, int height) {
        _screenSizeWidth = width;
        _screenSizeHeight = height;
        SDL_SetWindowSize(_window->window, width, height);
        _screenSizeHeight = height;
        _screenSizeWidth = width;
    }

    void SDLRenderService::setFullScreen(bool fullScreen) {
        // Set window flags fullscreen or 0 for no fullscreen
        if (_fullScreen != fullScreen)
            SDL_SetWindowFullscreen(_window->window, fullScreen ? SDL_WINDOW_FULLSCREEN_DESKTOP : 0);
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


    void SDLRenderService::renderButton(ButtonRenderShape &renderShape) {
        renderRect(*renderShape._rectRenderShape);

        std::optional<std::reference_wrapper<Font_Wrapper>> f;

        try{
            f = loadFont(renderShape._textRenderShape->filePath(), renderShape._textRenderShape->fontSize());
        } catch(std::exception& e){
            std::cout << "Error: " << e.what() << std::endl;
            return;
        }

        // Get direct reference to texture for easy access
        auto& font {*f->get().font};

        SDL_Surface* surface = TTF_RenderText_Solid(&font, renderShape._textRenderShape->text().c_str(),
                                                    {renderShape._textRenderShape->color().r8,
                                                     renderShape._textRenderShape->color().g8,
                                                     renderShape._textRenderShape->color().b8});

        if(surface == nullptr){
            printf("Unable to load image %s, Error: %s\n",
                   renderShape._textRenderShape->filePath().c_str(), IMG_GetError());
            return;
        }

        SDL_Rect dstRect;
        // center text to button container
        if(renderShape._textAlign == Alignment::Left){
            dstRect.x = renderShape._rectRenderShape->rect().position.x  - (surface->w);
        } else if(renderShape._textAlign == Alignment::Center){
            dstRect.x = renderShape._rectRenderShape->rect().position.x  - (surface->w / 2.0);
        } else{
            dstRect.x = renderShape._rectRenderShape->rect().position.x  - (surface->w / 4.0);
        }


        dstRect.y = renderShape._rectRenderShape->rect().position.y - (surface->h / 2.0);

        dstRect.w = surface->w;
        dstRect.h = surface->h;

        // Create texture from surface
        auto texture = SDL_CreateTextureFromSurface(_renderer->renderer, surface);
        // Free surface memory
        SDL_FreeSurface(surface);
        if(texture == nullptr){
            printf("Unable to create texture from %s, Error: %s\n",
                   renderShape._textRenderShape->filePath().c_str(), SDL_GetError());
            return;
        }

        SDL_RenderCopyEx(_renderer->renderer, texture, nullptr, &dstRect,
                         renderShape._textRenderShape->rotation(), nullptr, SDL_FLIP_NONE);

        SDL_DestroyTexture(texture);

    }

    void SDLRenderService::renderRect(RectRenderShape& renderShape) {
        // Set color
        SDL_SetRenderDrawColor(_renderer->renderer, renderShape.color().r8, renderShape.color().g8, renderShape.color().b8, renderShape.color().a);

        float xPivot;
        float yPivot;

        // Set Rect center to the origin (0,0), with center of rect as pivot point
        if(renderShape.pivotPoint().x == 0 && renderShape.pivotPoint().y == 0){
            xPivot = renderShape.rect().size.x / 2;
            yPivot = renderShape.rect().size.y / 2;
        }
        // Set Rect center to the origin (0,0), with custom pivot point
        else{
            xPivot = renderShape.pivotPoint().x;
            yPivot = renderShape.pivotPoint().y;
        }

        float xOrigin = renderShape.rect().position.x + xPivot;
        float yOrigin = renderShape.rect().position.y + yPivot;
        std::vector<std::pair<float, float>> points;
        points.emplace_back(renderShape.rect().position.x - xOrigin,
                            renderShape.rect().position.y - yOrigin);
        points.emplace_back(renderShape.rect().position.x + renderShape.rect().size.x - xOrigin,
                            renderShape.rect().position.y - yOrigin);
        points.emplace_back(renderShape.rect().position.x - xOrigin,
                            renderShape.rect().position.y + renderShape.rect().size.y - yOrigin);
        points.emplace_back(renderShape.rect().position.x + renderShape.rect().size.x - xOrigin,
                            renderShape.rect().position.y + renderShape.rect().size.y - yOrigin);

        //Convert degrees to rads
        float radians {(float) (renderShape.rotation() * (M_PI / 180.0f))};

        // Calculate new points with the use of a rotation matrix
        for (auto &point: points) {
            float tempX = point.first, tempY = point.second;
            point.first = tempX * std::cos(radians) - tempY * std::sin(radians);
            point.second = tempX * std::sin(radians) + tempY * std::cos(radians);
        }

        // Translate rect back to original position and set center point to pivot point and add cam offset
        for (auto &point: points) {
            point.first += xOrigin - xPivot;
            point.second += yOrigin - yPivot;
            point.first -= camOffset.x;
            point.second -= camOffset.y;
        }

        // Draw the lines to make the rectangle
        //First to second
        SDL_RenderDrawLine(_renderer->renderer, (int) points.at(0).first, (int) points.at(0).second, (int) points.at(1).first,
                           (int) points.at(1).second);
        //First to third
        SDL_RenderDrawLine(_renderer->renderer, (int) points.at(0).first, (int) points.at(0).second, (int) points.at(2).first,
                           (int) points.at(2).second);
        //Second to Last
        SDL_RenderDrawLine(_renderer->renderer, (int) points.at(1).first, (int) points.at(1).second, (int) points.at(3).first,
                           (int) points.at(3).second);
        //Third to Last
        SDL_RenderDrawLine(_renderer->renderer, (int) points.at(2).first, (int) points.at(2).second, (int) points.at(3).first,
                           (int) points.at(3).second);


    }

    void SDLRenderService::renderLine(LineRenderShape& renderShape) {
        // Set color
        SDL_SetRenderDrawColor(_renderer->renderer, renderShape.color().r8, renderShape.color().g8, renderShape.color().b8, renderShape.color().a);

        // Draw Line
        SDL_RenderDrawLineF(_renderer->renderer,
                            renderShape.positionA().x - camOffset.x, renderShape.positionA().y - camOffset.y,
                            renderShape.positionB().x - camOffset.x, renderShape.positionB().y - camOffset.y);
    }

    void SDLRenderService::renderCircle(CircleRenderShape& renderShape) {
        // Set color
        SDL_SetRenderDrawColor(_renderer->renderer, renderShape.color().r8, renderShape.color().g8, renderShape.color().b8, renderShape.color().a);

        const int32_t diameter = (abs(renderShape.radius()) * 2);

        int32_t x = (abs(renderShape.radius()) - 1);
        int32_t y = 0;
        int32_t tx = 1;
        int32_t ty = 1;
        int32_t error = (tx - diameter);

        while (x >= y)
        {
            //  Each of the following renders an octant of the circle
            SDL_RenderDrawPoint(_renderer->renderer, renderShape.position().x + x - camOffset.x, renderShape.position().y + y - camOffset.y);
            SDL_RenderDrawPoint(_renderer->renderer, renderShape.position().x + x - camOffset.x, renderShape.position().y - y - camOffset.y);
            SDL_RenderDrawPoint(_renderer->renderer, renderShape.position().x - x - camOffset.x, renderShape.position().y - y - camOffset.y);
            SDL_RenderDrawPoint(_renderer->renderer, renderShape.position().x - x - camOffset.x, renderShape.position().y + y - camOffset.y);
            SDL_RenderDrawPoint(_renderer->renderer, renderShape.position().x + y - camOffset.x, renderShape.position().y - x - camOffset.y);
            SDL_RenderDrawPoint(_renderer->renderer, renderShape.position().x + y - camOffset.x, renderShape.position().y + x - camOffset.y);
            SDL_RenderDrawPoint(_renderer->renderer, renderShape.position().x - y - camOffset.x, renderShape.position().y - x - camOffset.y);
            SDL_RenderDrawPoint(_renderer->renderer, renderShape.position().x - y - camOffset.x, renderShape.position().y + x - camOffset.y);
            if (error <= 0)
            {
                ++y;
                error += ty;
                ty += 2;
            }

            if (error > 0)
            {
                --x;
                tx += 2;
                error += (tx - diameter);
            }
        }
    }

    void SDLRenderService::renderSprite(SpriteRenderShape& renderShape) {
        // Try to load sprite with given path
        std::optional<std::reference_wrapper<Texture_Wrapper>> t;
        try {
            t = loadSprite(renderShape.path());
        }
        catch(std::exception& e){
            std::cout << "Error: " << e.what() << std::endl;
            return;
        }

        // Get direct reference to texture for easy access
        auto& texture {t->get()};

        // Set color and alpha mod
        Color color = renderShape.color();
        SDL_SetTextureColorMod(texture.texture, color.r8, color.g8, color.b8);
        SDL_SetTextureAlphaMod(texture.texture, color.a);

        // Calculate desired width and height of sprite
        float dstWidth, dstHeight;
        auto imageSource{renderShape.imageSource()};
        if (imageSource.size.x == 0 && imageSource.size.y == 0) {
            dstWidth = (texture.width * abs(renderShape.pixelScale().x));
            dstHeight = (texture.height * abs(renderShape.pixelScale().y));
        }
        else{
            dstWidth = (imageSource.size.x * abs(renderShape.pixelScale().x));
            dstHeight = (imageSource.size.y * abs(renderShape.pixelScale().y));
        }

        // Determine pivot point
        SDL_Point pivotPoint;
        // Set pivot point to center if no pivot point has been set
        if (renderShape.pivotPoint().x == 0 && renderShape.pivotPoint().y == 0)
            pivotPoint = {(int) (dstWidth / 2), (int) (dstHeight / 2)};
        else {
            // Mirror the x and y of the pivot point if scale is negative
            float pivotX;
            float pivotY;
            if (renderShape.pixelScale().x < 0)
                pivotX = (1 - (renderShape.pivotPoint().x / texture.width)) * texture.width;
            else
                pivotX = renderShape.pivotPoint().x;

            if (renderShape.pixelScale().y < 0)
                pivotY = (1 - (renderShape.pivotPoint().y / texture.height)) * texture.height;
            else
                pivotY = renderShape.pivotPoint().y;

            // Set pivot point
            pivotPoint = {(int) (pivotX * abs(renderShape.pixelScale().x)),
                          (int) (pivotY * abs(renderShape.pixelScale().y))};
        }

        // Creating destination rect
        SDL_Rect dstRect;
        dstRect.x = renderShape.position().x - pivotPoint.x - camOffset.x;
        dstRect.y = renderShape.position().y - pivotPoint.y - camOffset.y;
        dstRect.w = dstWidth;
        dstRect.h = dstHeight;

        // Convert Rect2 to SDL_Rect only if there is a given size, else just use the full size by giving a nullptr
        SDL_Rect srcRect;
        bool useFullSize{true};
        if (imageSource.size.x != 0 && imageSource.size.y != 0) {
            useFullSize = false;
            srcRect.x = imageSource.position.x;
            srcRect.y = imageSource.position.y;
            srcRect.w = imageSource.size.x;
            srcRect.h = imageSource.size.y;
        }

        // Flip sprite if scale is a negative value
        SDL_RendererFlip flip = SDL_FLIP_NONE;
        if (renderShape.pixelScale().x < 0)
            flip = (SDL_RendererFlip) (flip | (SDL_FLIP_HORIZONTAL));
        if (renderShape.pixelScale().y < 0)
            flip = (SDL_RendererFlip) (flip | (SDL_FLIP_VERTICAL));


        // Render sprite
        SDL_RenderCopyEx(_renderer->renderer, texture.texture, useFullSize ? nullptr : &srcRect, &dstRect,
                         renderShape.rotation(), &pivotPoint, flip);

    }

    Texture_Wrapper& SDLRenderService::loadSprite(const std::string& path) {
        auto cachedTexture = _cachedTextures.find(path);
        if(cachedTexture != _cachedTextures.end()){
            // Use existing texture
            return *cachedTexture->second;
        }
        else{
            // Load surface
            SDL_Surface* surface = IMG_Load(path.c_str());
            if(surface == nullptr){
                throw std::runtime_error("Unable to load image " + path + " Error: " + IMG_GetError());
            }

            auto width = surface->w;
            auto height = surface->h;

            // Create texture from surface
            auto newTexture = SDL_CreateTextureFromSurface(_renderer->renderer, surface);
            // Free surface memory
            SDL_FreeSurface(surface);
            if(newTexture == nullptr){
                throw std::runtime_error("Unable to create texture from " + path + "Error: " + SDL_GetError());
            }

            std::unique_ptr<Texture_Wrapper, void(*)(Texture_Wrapper*)> newTexture_wrapper {new Texture_Wrapper{newTexture, width, height}, SDL_DestroyTextureWrapper};
            auto ref = _cachedTextures.insert({path, std::move(newTexture_wrapper)});
            return *ref.first->second;
        }
    }

    void SDLRenderService::renderText(TextRenderShape& renderShape) {
        std::optional<std::reference_wrapper<Font_Wrapper>> f;
        try{
            f = loadFont(renderShape.filePath(), renderShape.fontSize());
        } catch(std::exception& e){
            std::cout << "Error: " << e.what() << std::endl;
            return;
        }

        // Get direct reference to font for easy access
        auto& font {*f->get().font};


        SDL_Surface* surface = TTF_RenderText_Solid(&font, renderShape.text().c_str(), {renderShape.color().r8,renderShape.color().g8,renderShape.color().b8});
        if(surface == nullptr){
            printf("Unable to load image %s, Error: %s\n", renderShape.filePath().c_str(), IMG_GetError());
            return;
        }

        SDL_Rect dstRect;
        dstRect.x = renderShape.position().x;
        dstRect.y = renderShape.position().y;

        dstRect.w = surface->w;
        dstRect.h = surface->h;

        // Create texture from surface
        auto texture = SDL_CreateTextureFromSurface(_renderer->renderer, surface);
        // Free surface memory
        SDL_FreeSurface(surface);
        if(texture == nullptr){
            printf("Unable to create texture from %s, Error: %s\n", renderShape.filePath().c_str(), SDL_GetError());
            return;
        }

        SDL_RenderCopyEx(_renderer->renderer, texture, nullptr, &dstRect, renderShape.rotation(), nullptr, SDL_FLIP_NONE);
        SDL_DestroyTexture(texture);
    }
    
    Font_Wrapper& SDLRenderService::loadFont(const std::string& path, size_t fontSize) {
        auto cachedFont = _cachedFonts.find(path);
        if(cachedFont != _cachedFonts.end() && cachedFont->second.first == fontSize){
            // Use existing texture
            return *cachedFont->second.second;
        }
        else{
            // Load new font
            auto newFont = TTF_OpenFont(path.c_str(), fontSize);
            if(newFont){
                std::unique_ptr<Font_Wrapper, void(*)(Font_Wrapper*)> font_wrapper {new Font_Wrapper{newFont}, TTF_CloseFontWrapper};
                auto ref = _cachedFonts.insert({path, std::pair<size_t, std::unique_ptr<Font_Wrapper, void(*)(Font_Wrapper*)>>(fontSize, std::move(font_wrapper))});
                return *ref.first->second.second;
            }
        }
        throw std::runtime_error("Could not find/load font with path: " + path);
    }

    void SDLRenderService::renderTileMap(TileMapRenderShape& renderShape) {
        // Try to load tile set with given path
        std::optional<std::reference_wrapper<Texture_Wrapper>> t;
        try {
            t = loadSprite(renderShape.imagePath());
        }
        catch(std::exception& e){
            std::cout << "Error: " << e.what() << std::endl;
            return;
        }

        // Get direct reference to texture for easy access
        auto& texture {t->get()};

        SDL_Rect srcRect, dstRect;
        srcRect.w = renderShape.tileSet().tileWidth;
        srcRect.h = renderShape.tileSet().tileHeight;
        dstRect.w = renderShape.map().tileWidth * renderShape.scale().x;
        dstRect.h = renderShape.map().tileHeight * renderShape.scale().y;

        uint8_t rowIndex = 0;
        auto& map = renderShape.map().map;
        int tileSetColumns = renderShape.tileSet().columns;
        int mapColumns = renderShape.map().columns;
        for(auto& row : map){
            uint8_t column = 0;
            for(auto& tile : row){
                if(tile == 0) {column++; continue;}
                srcRect.x = ((tile-1) % tileSetColumns) * srcRect.w;
                srcRect.y = ((tile-1) / tileSetColumns) * srcRect.h;
                dstRect.x = ((column % mapColumns) * dstRect.w) + renderShape.position().x - camOffset.x;
                dstRect.y = (rowIndex * dstRect.h) + renderShape.position().y - camOffset.y;
                SDL_RenderCopy(_renderer->renderer, texture.texture, &srcRect, &dstRect);
                column++;
            }
            rowIndex++;
        }
    }
    std::optional<std::reference_wrapper<Camera>> SDLRenderService::getMainCamera() const {
        if(_mainCamera)
            return _mainCamera;
        else
            return std::nullopt;
    }

    void SDLRenderService::setMainCamera(Camera &camera) {
        _mainCamera = camera;
    }

    bool SDLRenderService::isRegistered(Drawable& drawable) {
        auto result = std::find_if(_drawables.begin(), _drawables.end(), [&](const std::reference_wrapper<Drawable> &d) {
            return &d.get() == &drawable;
        });
        if(result != _drawables.end())
            return true;
        return false;
    }

    int SDLRenderService::getScreenSizeWidth() const {
        return _screenSizeWidth;
    }

    int SDLRenderService::getScreenSizeHeight() const {
        return _screenSizeHeight;
    }

    Vector2 SDLRenderService::getCameraOffset() const {
        if(_mainCamera)
            return camOffset;

        throw std::runtime_error("Camera offset requested without an active camera in the scene.");
    }

    void SDLRenderService::setWindowTitle(const std::string& title) {
        SDL_SetWindowTitle(_window->window, title.c_str());
    }
}
