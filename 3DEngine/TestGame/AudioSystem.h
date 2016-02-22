#ifndef AUDIOSYSTEM_H
#define AUDIOSYSTEM_H
#include "../Dependencies/include/irrKlang/irrKlang.h"
#include <iostream>
class AudioSystem
{
public:
	AudioSystem(irrklang::ISoundEngine* engine);
	~AudioSystem();

	void audioPlay();
	void audioPause();
	void includeAudio(std::string filepath);
	void setPosition(irrklang::vec3df pos);


private:
	irrklang::ISoundEngine* soundEngine;
	irrklang::ISoundSource* soundSource;
	irrklang::ISound* sound;
	irrklang::vec3df position;
};


#endif // !AUDIOSYSTEM_H
