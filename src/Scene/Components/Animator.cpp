//
// Created by conner on 02/11/2022.
//

#include <cmath>

#include "Animator.h"

Animator::Animator(std::string spriteSheetPath, int spriteSheetRows, int spriteSheetCols, Vector2 spriteSheetCellSize)
    : _spriteSheetPath{std::move(spriteSheetPath)}, _rows{spriteSheetRows}, _cols{spriteSheetCols}, _cellSize{spriteSheetCellSize}, _fps{60},
    _looping{false}, _countedFrames{0}, _currentCell{0} {

}

void Animator::addAnimation(const std::string& name, int beginCell, int endCell, float playSpeed) {
    Animation newAnimation {name, playSpeed, beginCell, endCell};
    _animations.insert({name, newAnimation});
    _currentAnimation = newAnimation;
}

void Animator::onStart() {
    // Check if gameObject has a SpriteComponent, if not, create one ourselves
    if(_gameObject->get().hasComponent<SpriteComponent>())
        _spriteComponent = _gameObject->get().getComponent<SpriteComponent>();
    else
        _spriteComponent = _gameObject->get().addComponent<SpriteComponent>(_spriteSheetPath, Vector2(1,1), Rect2(Vector2(0,0), _cellSize));
}

void Animator::onUpdate() {
    if(_currentAnimation != std::nullopt){
        _countedFrames++;
        if(_countedFrames > _fps / _currentAnimation->get().playSpeed){
            _countedFrames = 0;
            _currentCell++;
            if(_currentCell > _currentAnimation->get().endCell)
                finishAnimation();
            _spriteComponent->get().setImageSource(Rect2(Vector2{(_currentCell % _cols) * _cellSize.x,
                                                                 (int)floorf((float)_currentCell / (float)_cols) * _cellSize.y},
                                                                    _cellSize));
        }
    }
}

void Animator::onRemove() {

}

bool Animator::getActive() {
    return _active;
}

void Animator::setActive(bool active) {
    _active = active;
}

void Animator::setParentGameObject(GameObject& gameObject) {
    _gameObject = gameObject;
}

void Animator::play(const std::string& animation, bool looping) {
    if(animation == _currentAnimation->get().name) {return;}

    auto anim = _animations.find(animation);
    if(anim != _animations.end()){
        _currentAnimation = anim->second;
        _looping = looping;
        _currentCell = _currentAnimation->get().beginCell;
    }
}

void Animator::stop() {
    _currentAnimation = std::nullopt;
}

void Animator::finishAnimation() {
    if(_looping)
        _currentCell = _currentAnimation->get().beginCell;
    else{
        auto returnAnim = _returnTransitions.find(_currentAnimation->get().name);
        if(returnAnim != _returnTransitions.end()){
            play(returnAnim->second, true);
        }
        else{
            _currentCell--;
            stop();
        }
    }
}

void Animator::addReturnTransition(const std::string& from, const std::string& to) {
    _returnTransitions.insert({from, to});
}
