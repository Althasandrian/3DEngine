#ifndef AUDIO_HPP
#define AUDIO_HPP

#include <Core/Managers/EntityManager.hpp>
#include <Core/AudioSystem.h>

namespace Engine
{
	class Audio : public Component
	{
	public:
		Audio() : as(new AudioSystem()){};
		virtual ~Audio() {};
		virtual void Init() override;
		virtual void Cleanup() override;

		virtual void Update(DeltaTime deltaTime) override;
		irrklang::ik_u32 getPlayPosition();
		//play
		void Play();
		void Pause();
		void Stop();
		irrklang::ISound* getAudio();
		irrklang::vec3df getPosition();
		void setVolume(irrklang::ik_f32 volume);
		void setAudio(std::string filepath);
		void setPosition(irrklang::vec3df position);
	protected:
	private:
		irrklang::ISoundEngine* soundEngine;
		irrklang::ISoundSource* soundSource;
		irrklang::ISound* sound;
		irrklang::vec3df position;
		int volume;
		bool isPlaying;
		AudioSystem* as;

	};

	void Audio::Init() {};
	void Audio::Cleanup(){};
	void Audio::setAudio(std::string filepath){
		soundSource = as->includeAudio(filepath);
	};

	void Audio::Update(DeltaTime deltaTime) {};
	irrklang::ik_u32 Audio::getPlayPosition(){ return sound->getPlayPosition(); };
	void Audio::Play(){ as->audioPlay(sound); };
	void Audio::Pause(){ as->audioPause(sound); };
	void Audio::Stop(){ as->audioStop(sound); };
	irrklang::ISound* Audio::getAudio(){ return sound; };
	irrklang::vec3df Audio::getPosition(){ return position; };
	void Audio::setVolume(irrklang::ik_f32 volume){ as->setVolume(sound, volume); };
	void Audio::setPosition(irrklang::vec3df position){ as->setPosition(sound, position); };

}
#endif
