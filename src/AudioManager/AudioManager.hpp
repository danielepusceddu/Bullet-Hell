#pragma once
#include <SFML/Audio.hpp>
#include "../Bus/BusNode.hpp"

class AudioManager : public BusNode{
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