#include "AudioSystem.h"

AudioSystem::AudioSystem(irrklang::ISoundEngine* engine)
{
	soundEngine = engine;
}

AudioSystem::~AudioSystem()
{
	soundEngine->drop();
}

void AudioSystem::audioPlay()
{
	soundEngine->play3D(soundSource, position);
}

void AudioSystem::audioPause()
{
	sound->setIsPaused(true);
}

void AudioSystem::includeAudio(std::string filePath)
{
	
	soundSource = soundEngine->addSoundSourceFromFile(filePath.c_str());
}

void AudioSystem::setPosition(irrklang::vec3df pos)
{
	position = pos;
}
void AudioSystem::setVolume()
{
	sound->setVolume(volume);
}

