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
	audio->setIsPaused(true);
}

void AudioSystem::includeAudio(std::string filepath)
{
	soundSource = soundEngine->addSoundSourceFromFile(filepath.c_str());
}

void AudioSystem::setPosition(irrklang::vec3df pos)
{
	position = pos;
}
