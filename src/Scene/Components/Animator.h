//
// Created by conner on 02/11/2022.
//

#ifndef GOLFENGINE_ANIMATOR_H
#define GOLFENGINE_ANIMATOR_H


#include <string>
#include <map>
#include "Animation.h"
#include "SpriteComponent.h"

class Animator : public Component {
public:
    /// Animator component manages a SpriteComponent by changing its sprite to simulate animations
    /// \param spriteSheetPath Path to the sprite sheet containing the various animations
    /// \param spriteSheetRows Amount of rows of cells in the sprite sheet
    /// \param spriteSheetCols Amount of columns of cells in the sprite sheet
    /// \param spriteSheetCellSize The size of a cell in the sprite sheet (rectangle containing a single sprite)
    Animator(std::string spriteSheetPath, int spriteSheetRows, int spriteSheetCols, Vector2 spriteSheetCellSize, Vector2 pixelScale =Vector2(1,1));

    /// Adds an animation to the list of animations
    /// \param name The name of the animation to address later for playing
    /// \param beginCell The cell at which the animation starts
    /// \param endCell The cell at which the animation ends
    /// \param playSpeed A multiplier at which the animation is played (1 frame per second * playSpeed)
    void addAnimation(const std::string& name, int beginCell, int endCell, float playSpeed = 1.0f);

    /// Adds an animation to return to after finishing playing a specific animation
    /// \param from Animation at which to return from
    /// \param to Animation to which to after the from animation has finished
    void addReturnTransition(const std::string& from, const std::string& to);

    /// Plays an animation
    /// \param animation Name of the animation to play
    /// \param looping Loop the animation
    void play(const std::string& animation, bool looping = false);

    /// Will stop current animation
    void stop();

    // Component overrides
    void onStart() override;
    void onUpdate() override;
    void onRemove() override;
    bool getActive() override;
    void setActive(bool active) override;
    void setParentGameObject(GameObject& gameObject) override;

    // IPersistable overrides
    std::unique_ptr<ISnapshot> saveSnapshot() override;
    void loadSnapshot(const ISnapshot& rawSnapshot) override;
private:
    void finishAnimation();

private:
    const std::string _spriteSheetPath;
    const int _rows;
    const int _cols;
    const Vector2 _cellSize;

    std::map<std::string, Animation> _animations;
    std::map<std::string, std::string> _returnTransitions;
    std::optional<std::reference_wrapper<SpriteComponent>> _spriteComponent;
    std::optional<std::reference_wrapper<Animation>> _currentAnimation;
    const int _fps;

    bool _looping;
    int _countedFrames;
    int _currentCell;
    Vector2 _pixelScale;

    struct Snapshot : public ISnapshot{
        bool looping {};
        int countedFrames {};
        int currentCell {};
        std::optional<std::reference_wrapper<Animation>> currentAnimation;
    };
};


#endif //GOLFENGINE_ANIMATOR_H
