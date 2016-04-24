#ifndef AUDIOSYSTEM_H
#define AUDIOSYSTEM_H
#include "../../Dependencies/include/irrKlang/irrKlang.h"
#include <iostream>
#include "ResourceManager.h"
class AudioSystem
{
public:
	AudioSystem() {}
	~AudioSystem();

	void audioPlay(	irrklang::ISound* sound);
	void audioPause(irrklang::ISound* sound);
	void audioStop(irrklang::ISound* sound);
	irrklang::ISoundSource* includeAudio(std::string filepath);
	void setPosition(irrklang::ISound* sound, irrklang::vec3df pos);
	void setVolume(irrklang::ISound* sound, int volume);
	void AudioSystem::setEngine(irrklang::ISoundEngine* engine);

private:
	irrklang::ISoundEngine* soundEngine;
};

#endif // !AUDIOSYSTEM_H