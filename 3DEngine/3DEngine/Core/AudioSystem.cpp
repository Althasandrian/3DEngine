#include "AudioSystem.h"


AudioSystem::~AudioSystem()
{
	soundEngine->drop();
}

void AudioSystem::audioPlay(irrklang::ISound* sound)
{
	soundEngine->play3D(sound->getSoundSource(), sound->getPosition() = irrklang::vec3df(0,0,0));
}

void AudioSystem::audioPause(irrklang::ISound* sound)
{
	sound->setIsPaused();
}
void AudioSystem::audioStop(irrklang::ISound* sound)
{
	sound->stop();
}
void AudioSystem::setEngine(irrklang::ISoundEngine* engine)
{
	soundEngine = engine;
}
irrklang::ISoundSource* AudioSystem::includeAudio(std::string filePath)
{
	irrklang::ISoundSource* soundSource = soundEngine->addSoundSourceFromFile(filePath.c_str());
	return soundSource;
}

void AudioSystem::setPosition(irrklang::ISound* sound, irrklang::vec3df pos)
{
	sound->setPosition(pos);
}
void AudioSystem::setVolume(irrklang::ISound* sound,int volume)
{
	sound->setVolume(volume);
}

