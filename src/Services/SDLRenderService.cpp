//
// Created by conner on 11/2/2022.
//

#include "SDLRenderService.h"
#include <cmath>
#include <iostream>
#include <algorithm>

namespace GolfEngine::Services::Render {

    SDLRenderService::SDLRenderService()
            : _screenSizeHeight{480}, _screenSizeWidth{640}, _window{nullptr}, _renderer{nullptr}, _fullScreen{false} {
        // Init SDL
        if (SDL_Init(SDL_INIT_VIDEO) < 0) {
            std::cerr << "Error: " << SDL_GetError() << std::endl;
        }

        //Initialize PNG AND JPG loading
        if(IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG) < 0)
        {
            printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
        }

        // Create window and renderer
        if (SDL_CreateWindowAndRenderer(_screenSizeWidth, _screenSizeHeight, 0, &_window, &_renderer) < 0) {
            std::cerr << "Error: " << SDL_GetError() << std::endl;
        }

        // Set some basic window properties
        SDL_SetWindowTitle(_window, "Hello World");
        SDL_ShowCursor(1); // 0 is disable cursor, 1 is enable
        SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY,
                    "2"); // Increases quality with the scaling of textures, 0 nothing, 1 linear filtering, 2 anisotropic filtering

        //Makes alpha blending possible(used for opacity)
        SDL_SetRenderDrawBlendMode(_renderer, SDL_BLENDMODE_BLEND);

    }

    SDLRenderService::~SDLRenderService() {
        clearTextureCache();

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

    SDLRenderService &SDLRenderService::operator=(SDLRenderService &&other) noexcept {
        if (this != &other) {
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

    void SDLRenderService::addDrawable(Drawable *drawable) {
        // Check for valid drawable
        if (drawable == nullptr)
            return;

        _drawables.push_back(drawable);
    }

    void SDLRenderService::removeDrawable(Drawable *drawable) {
        // Check for valid drawable
        if (drawable == nullptr)
            return;

        // Find the iterator with the given drawable
        auto foundIterator = std::find(_drawables.begin(), _drawables.end(), drawable);
        // If drawable is present in the list, remove it from the list
        if (foundIterator != _drawables.end()) {
            _drawables.erase(foundIterator);
        }
    }

    void SDLRenderService::render() {
        // Clear screen
        SDL_RenderClear(_renderer);

        // Loop through all registered drawables
        for (auto drawable: _drawables) {
            auto *renderShape = drawable->getRenderShape();
            switch (renderShape->getType()) {
                case RenderShapeType::RectShape:
                    renderRect(reinterpret_cast<RectRenderShape &>(*renderShape));
                    break;
                case RenderShapeType::LineShape:
                    renderLine(reinterpret_cast<LineRenderShape &>(*renderShape));
                    break;
                case RenderShapeType::SpriteShape:
                    renderSprite(reinterpret_cast<SpriteRenderShape &>(*renderShape));
                    break;
                case RenderShapeType::CircleShape:
                    renderCircle(reinterpret_cast<CircleRenderShape &>(*renderShape));
                    break;
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
        if (_fullScreen != fullScreen)
            SDL_SetWindowFullscreen(_window, fullScreen ? SDL_WINDOW_FULLSCREEN_DESKTOP : 0);
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

    void SDLRenderService::renderRect(RectRenderShape &renderShape) {
        // Set color
        SDL_SetRenderDrawColor(_renderer, renderShape.color().r8, renderShape.color().g8, renderShape.color().b8, renderShape.color().a);

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

        // Translate rect back to original position and set center point to pivot point
        for (auto &point: points) {
            point.first += xOrigin - xPivot;
            point.second += yOrigin - yPivot;
        }

        // Draw the lines to make the rectangle
        //First to second
        SDL_RenderDrawLine(_renderer, (int) points.at(0).first, (int) points.at(0).second, (int) points.at(1).first,
                           (int) points.at(1).second);
        //First to third
        SDL_RenderDrawLine(_renderer, (int) points.at(0).first, (int) points.at(0).second, (int) points.at(2).first,
                           (int) points.at(2).second);
        //Second to Last
        SDL_RenderDrawLine(_renderer, (int) points.at(1).first, (int) points.at(1).second, (int) points.at(3).first,
                           (int) points.at(3).second);
        //Third to Last
        SDL_RenderDrawLine(_renderer, (int) points.at(2).first, (int) points.at(2).second, (int) points.at(3).first,
                           (int) points.at(3).second);
    }

    void SDLRenderService::renderLine(LineRenderShape &renderShape) {
        // Set color
        SDL_SetRenderDrawColor(_renderer, renderShape.color().r8, renderShape.color().g8, renderShape.color().b8, renderShape.color().a);

        // Draw Line
        SDL_RenderDrawLineF(_renderer,
                            renderShape.positionA().x, renderShape.positionA().y,
                            renderShape.positionB().x, renderShape.positionB().y);
    }

    void SDLRenderService::renderCircle(CircleRenderShape &renderShape) {
        // Set color
        SDL_SetRenderDrawColor(_renderer, renderShape.color().r8, renderShape.color().g8, renderShape.color().b8, renderShape.color().a);

        const int32_t diameter = (abs(renderShape.radius()) * 2);

        int32_t x = (abs(renderShape.radius()) - 1);
        int32_t y = 0;
        int32_t tx = 1;
        int32_t ty = 1;
        int32_t error = (tx - diameter);



        while (x >= y)
        {
            //  Each of the following renders an octant of the circle
            SDL_RenderDrawPoint(_renderer, renderShape.position().x + x, renderShape.position().y + y);
            SDL_RenderDrawPoint(_renderer, renderShape.position().x + x, renderShape.position().y - y);
            SDL_RenderDrawPoint(_renderer, renderShape.position().x - x, renderShape.position().y - y);
            SDL_RenderDrawPoint(_renderer, renderShape.position().x - x, renderShape.position().y + y);
            SDL_RenderDrawPoint(_renderer, renderShape.position().x + y, renderShape.position().y - x);
            SDL_RenderDrawPoint(_renderer, renderShape.position().x + y, renderShape.position().y + x);
            SDL_RenderDrawPoint(_renderer, renderShape.position().x - y, renderShape.position().y - x);
            SDL_RenderDrawPoint(_renderer, renderShape.position().x - y, renderShape.position().y + x);

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
        // Load sprite
        auto* texture {loadSprite(renderShape.path())};
        if(texture == nullptr) {return;}

        // Set color and blend mode
        texture->setColor(renderShape.color());
        texture->setAlphaMod(renderShape.color().a);

        // Calculate desired width and height of sprite
        float dstWidth {(texture->width() * abs(renderShape.pixelScale().x))};
        float dstHeight {(texture->height() * abs(renderShape.pixelScale().y))};

        // Determine pivot point
        SDL_Point pivotPoint;
        // Set pivot point to center if no pivot point has been set
        if(renderShape.pivotPoint().x == 0 && renderShape.pivotPoint().y == 0)
            pivotPoint = {(int)(dstWidth / 2), (int)(dstHeight / 2)};
        else{
            // Mirror the x and y of the pivot point if scale is negative
            float pivotX;
            float pivotY;
            if(renderShape.pixelScale().x < 0)
                pivotX = (1 - (renderShape.pivotPoint().x / texture->width())) * texture->width();
            else
                pivotX = renderShape.pivotPoint().x;

            if(renderShape.pixelScale().y < 0)
                pivotY = (1 - (renderShape.pivotPoint().y / texture->height())) * texture->height();
            else
                pivotY= renderShape.pivotPoint().y;

            // Set pivot point
            pivotPoint = {(int)(pivotX * abs(renderShape.pixelScale().x)),
                          (int)(pivotY * abs(renderShape.pixelScale().y))};
        }

        // Creating destination rect
        SDL_Rect dstRect;
        dstRect.x = renderShape.position().x - pivotPoint.x;
        dstRect.y = renderShape.position().y - pivotPoint.y;
        dstRect.w = dstWidth;
        dstRect.h = dstHeight;

        // Convert Rect2 to SDL_Rect only if there is a given size, else just use the full size by giving a nullptr
        SDL_Rect srcRect;
        bool useFullSize {true};
        auto imageSource {renderShape.imageSource()};
        if(imageSource.size.x != 0 && imageSource.size.y != 0){
            useFullSize = false;
            srcRect.x = imageSource.position.x;
            srcRect.y = imageSource.position.y;
            srcRect.w = imageSource.size.x;
            srcRect.h = imageSource.size.y;
        }

        // Flip sprite if scale is a negative value
        SDL_RendererFlip flip = SDL_FLIP_NONE;
        if(renderShape.pixelScale().x < 0)
            flip = (SDL_RendererFlip)(flip | (SDL_FLIP_HORIZONTAL));
        if(renderShape.pixelScale().y < 0)
            flip = (SDL_RendererFlip)(flip | (SDL_FLIP_VERTICAL));


        // Render sprite
        SDL_RenderCopyEx(_renderer, texture->texture(), useFullSize? nullptr : &srcRect, &dstRect,
                         renderShape.rotation(), &pivotPoint, flip);
    }

    Texture* SDLRenderService::loadSprite(const std::string& path) {
        auto cachedTexture = _cachedTextures.find(path);
        if(cachedTexture != _cachedTextures.end()){
            // Use existing texture
            return cachedTexture->second;
        }
        else{
            // Load new texture
            auto* newTexture = new Texture();
            if(newTexture->loadFromFile(path, *_renderer)){
                _cachedTextures.insert({path, newTexture});
                return newTexture;
            }
            return nullptr;
        }
    }

    void SDLRenderService::clearTextureCache() {
        // Free all texture memory
        for(auto& texture : _cachedTextures){
            texture.second->free();
            delete texture.second;
        }
    }
}
