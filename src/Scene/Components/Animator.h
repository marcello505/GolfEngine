//
// Created by conner on 02/11/2022.
//

#ifndef GOLFENGINE_ANIMATOR_H
#define GOLFENGINE_ANIMATOR_H


#include <string>
#include <map>
#include "Animation.h"
#include "Component.h"
#include "SpriteComponent.h"

class Animator : public Component {
public:
    Animator(std::string spriteSheetPath, int spriteSheetRows, int spriteSheetCols, Vector2 spriteSheetCellSize);
    void addAnimation(const std::string& name, int beginCell, int endCell, float playSpeed = 1.0f);
    void addReturnTransition(const std::string& from, const std::string& to);
    void play(const std::string& animation, bool looping = false);
    void stop();

    // Component overrides
    void onStart() override;
    void onUpdate() override;
    void onRemove() override;
    bool getActive() override;
    void setActive(bool active) override;
    void setParentGameObject(GameObject& gameObject) override;
private:
    void finishAnimation();

private:
    std::string _spriteSheetPath;
    int _rows;
    int _cols;
    Vector2 _cellSize;

    std::map<std::string, Animation> _animations;
    std::map<std::string, std::string> _returnTransitions;
    std::optional<std::reference_wrapper<SpriteComponent>> _spriteComponent;
    std::optional<std::reference_wrapper<Animation>> _currentAnimation;
    int _fps;
    bool _looping;

    int _countedFrames;
    int _currentCell;
};


#endif //GOLFENGINE_ANIMATOR_H
