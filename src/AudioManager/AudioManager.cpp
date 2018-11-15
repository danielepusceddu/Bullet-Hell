#include "AudioManager.hpp"
#include <iostream>

AudioManager::AudioManager(Bus& bus):
BusListener{bus}
{
    std::cout << "Loading sounds..." << std::endl;

    //Ship explosion sound
    shipExplosionSoundBuf.loadFromFile("../assets/audio/explosion1.wav");
    shipExplosionSound.setBuffer(shipExplosionSoundBuf);
    shipExplosionSound.setVolume(20);

    //Player laser shot sound
    blueShotSoundBuf.loadFromFile("../assets/audio/laser_shot1.wav");
    blueShotSound.setBuffer(blueShotSoundBuf);
    blueShotSound.setVolume(10);

    //Enemy laser shot sound
    redShotSoundBuf.loadFromFile("../assets/audio/laser_shot2.wav");
    redShotSound.setBuffer(redShotSoundBuf);
    redShotSound.setVolume(15);

    //Music
    music.openFromFile("../assets/audio/8-Bit-Mayhem.ogg");
    music.setVolume(50);
    music.setLoop(true);
}

void AudioManager::startMusic(){
    music.play();
}

void AudioManager::notify(Message msg){
    switch(msg.getType()){
        case Message::Type::SHIP_DEATH:
        shipExplosionSound.play();
        break;

        case Message::Type::BLUE_SHIP_SHOT:
        blueShotSound.play();
        break;

        case Message::Type::RED_SHIP_SHOT:
        redShotSound.play();
        break;

        default:
        break;
    }
}