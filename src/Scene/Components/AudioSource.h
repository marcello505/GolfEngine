//
// Created by jaaps on 02/11/2022.
//

#ifndef GOLFENGINE_AUDIOSOURCE_H
#define GOLFENGINE_AUDIOSOURCE_H

#include <optional>
#include <string>

#include "Component.h"

namespace GolfEngine::Scene::Components{
    class AudioSource : public Component{
    public:
        AudioSource(const std::string& audioPath, bool isMusic, bool playOnAwake = false, bool loopOnAwake = false) :
        _isMusic{isMusic},
        _playOnAwake{playOnAwake},
        _loopOnAwake{loopOnAwake},
        _audioPath{audioPath} {}

        //=======
        //Methods
        /// play() will call the corresponding play call for the group this AudioSource belongs to.
        void play(bool looping = false);
        /// stop() will eiter stop the sound effect or the music depending on which group the AudioSource belongs to.
        void stop();
        void onStart() override;
        void onUpdate() override;
        void onRemove() override;
        bool getActive() override;
        void setActive(bool active) override;
        void setParentGameObject(GameObject& gameObject) override;

        //======
        //Fields
        float volume {1.0f};

    private:
        std::optional<std::reference_wrapper<GameObject>> _parent {};
        bool _active {true};
        std::string _audioPath {};
        bool _isMusic {};
        bool _playOnAwake {};
        bool _loopOnAwake {};
    };

}



#endif //GOLFENGINE_AUDIOSOURCE_H
