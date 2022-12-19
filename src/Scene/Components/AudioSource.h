//
// Created by jaaps on 02/11/2022.
//

#ifndef GOLFENGINE_AUDIOSOURCE_H
#define GOLFENGINE_AUDIOSOURCE_H

#include <optional>
#include <string>
#include <map>

#include "Component.h"

namespace GolfEngine::Scene::Components{
    class AudioSource : public Component{
    public:
        /// AudioSource component is used for playing music or sound effects
        /// \param isMusic configure this audio source to play music or sound effects
        /// \param playOnAwake play sfx or music on awake
        /// \param loopOnAwake loop sfx or music on awake
        explicit AudioSource(bool isMusic, bool playOnAwake = false, bool loopOnAwake = false) :
        _isMusic{isMusic},
        _playOnAwake{playOnAwake},
        _loopOnAwake{loopOnAwake} {}

        /// Will play the sound effect or music with the corresponding name
        /// \param sound name of sound to be played
        /// \param looping loop the sound
        void play(const std::string& sound, bool looping = false);

        /// Will stop the playing sound effect or music with the corresponding name
        /// \param sound name of the sound to be stopped
        void stop(const std::string& sound);

        /// Will add a sound to this AudioSource component, so it can be played in the future
        /// \param sound name of the sound to be added
        /// \param path path to the sound file
        void addSound(const std::string& sound, const std::string& path);

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

        float volume {1.0f};
    private:
        std::optional<std::reference_wrapper<GameObject>> _parent {};
        bool _active {true};
        const bool _isMusic {};
        const bool _playOnAwake {};
        const bool _loopOnAwake {};

        std::map<std::string, std::string> _sounds {};

        struct Snapshot : ISnapshot{
            float volume {};
        };
    };
}


#endif //GOLFENGINE_AUDIOSOURCE_H
