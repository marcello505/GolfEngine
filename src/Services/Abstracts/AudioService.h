//
// Created by conner on 11/2/2022.
//

#ifndef SPC_PROJECT_AUDIOSERVICE_H
#define SPC_PROJECT_AUDIOSERVICE_H

#include <string>

class AudioService{
public:
    // LifeCycles
    /// Initializes the audio device, automatically called by GameLoop
    virtual void init() = 0;
    /// Closes the audio device and clears cache, automatically called by GameLoop
    virtual void free() = 0;

    // Audio Controls Methods
    /// Plays a sound effect
    /// \param path Path of the sound effect to be played
    /// \param volume Volume of the sound effect to be played
    /// \param loop Loop the sound effect after finish playing
    virtual void playSfx(const std::string& path, float volume, bool loop) = 0;

    /// Plays a music track
    /// \param path Path of the music to be played
    /// \param volume Volume of the music to be played
    /// \param loop Loop the music after finish playing
    virtual void playMusic(const std::string& path, float volume, bool loop) = 0;

    /// Pause the music currently playing
    virtual void pauseMusic() = 0;

    /// Resume the music that is currently paused
    virtual void resumeMusic() = 0;

    /// Pauses or resumes the music based on its current state
    virtual void toggleMusic() = 0;

    /// Stop the music from playing (Not able to resume after)
    virtual void stopMusic() = 0;

    /// Stops all the sound effects from playing
    virtual void stopSfx() = 0;

    /// Stop a specific sound effect from playing
    /// \param path Path to the sound effect that is playing
    virtual void stopSfx(const std::string& path) = 0;

    // Volume Methods
    /// Returns the master volume
    /// \return current master volume value
    virtual float getMasterVolume() = 0;
    /// Returns the music volume
    /// \return current music volume value
    virtual float getMusicVolume() = 0;
    /// Returns the sfx volume
    /// \return current sfx volume value
    virtual float getSfxVolume() = 0;
    /// Sets the _masterVolume field and updates the current volume of all audio.
    /// \param volume a value between 0.0 and 1.0, used as a factor to calculate volume.
    virtual void setMasterVolume(float volume) = 0;
    /// Sets the _musicVolume field and updates the current volume of Music.
    /// \param volume a value between 0.0 and 1.0, used as a factor to calculate volume.
    virtual void setMusicVolume(float volume) = 0;
    /// Sets the _sfxVolume field and updates the current volume of Sound effects.
    /// \param volume a value between 0.0 and 1.0, used as a factor to calculate volume.
    virtual void setSfxVolume(float volume) = 0;

    // Cache Methods
    /// Loads a sfx file into the cache of the Audio Service
    /// \param path Path to the sfx file to be cached
    virtual void preloadSfx(const std::string& path) = 0;
    /// Loads a music file into the cache of the Audio Service
    /// \param path Path to the music file to be cached
    virtual void preloadMusic(const std::string& path) = 0;
    /// Clears the entire cache of the Audio Service
    virtual void clearCache() = 0;

    // Getters and boolean Methods
    /// Checks whether there is currently music playing
    /// \return true if music is playing
    virtual bool isMusicPlaying() = 0;
    /// Checks whether there is currently a paused music track
    /// \return true if current music is paused
    virtual bool isMusicPaused() = 0;

    // Virtual Destructors
    virtual ~AudioService() = default;
};


#endif //SPC_PROJECT_AUDIOSERVICE_H
