#pragma once
#include <SFML/Audio.hpp>
#include "../Bus/BusListener.hpp"

class AudioManager : public BusListener{
    public:
    AudioManager(Bus& bus);
    void notify(Message msg) override;
    void startMusic();

    private:
    sf::Music music;

    sf::SoundBuffer shipExplosionSoundBuf;
    sf::Sound shipExplosionSound;

    sf::SoundBuffer blueShotSoundBuf;
    sf::Sound blueShotSound;

    sf::SoundBuffer redShotSoundBuf;
    sf::Sound redShotSound;
};