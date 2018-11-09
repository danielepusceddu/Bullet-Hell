#include "AudioManager.hpp"

AudioManager::AudioManager(){
    //Ship explosion sound
    shipExplosionSoundBuf.loadFromFile("../assets/audio/explosion1.wav");
    shipExplosionSound.setBuffer(shipExplosionSoundBuf);
    shipExplosionSound.setVolume(20);
}

AudioManager::~AudioManager(){}

void AudioManager::notify(Message msg){
    switch(msg.getType()){
        case Message::Type::SHIP_DEATH:
        shipExplosionSound.play();
        break;

        default:
        break;
    }
}