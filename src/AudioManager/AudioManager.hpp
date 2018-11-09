#pragma once
#include <SFML/Audio.hpp>
#include "../Bus/BusNode.hpp"

class AudioManager : public BusNode{
    public:
    AudioManager();
    ~AudioManager();
    void notify(Message msg) override;

    private:
    sf::SoundBuffer shipExplosionSoundBuf;
    sf::Sound shipExplosionSound;
};