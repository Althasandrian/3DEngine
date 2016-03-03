#ifndef RESOURCE_H
#define RESOURCE_H
#include <iostream>
#include "../AudioSystem.h"
#include "..\..\Dependencies\include\irrKlang\irrKlang.h"
enum TYPE
{
	Text = 1,
	Audio = 2,
	Image = 3,
	Font = 4,
};
class Resource
{
public:
	Resource() {};
	~Resource(){};

	std::string filepath;
	TYPE type;
	std::string scope;
	int ID;	
	std::vector<int> resourceUsers;


	void setTextData(std::string readFile){ textData = readFile; }
	void setImageData(std::vector<unsigned char> imageFile) { std::cout << "setting image data" << std::endl; imageData = imageFile; }
	void setAudioData(irrklang::ISoundSource* audioFile) { std::cout << "Setting audio data " << std::endl; audioData = audioFile; }
	void setAudioEngine(irrklang::ISoundEngine* engine) {  audio->setEngine(engine); }
	void setAudio(std::string filename){ audio->includeAudio(filename); }
	std::string getTextData(){ return textData; }
	std::vector<unsigned char> getImageData(){ return imageData; }

	AudioSystem* getAudioData() { return audio; }
private:
	std::string textData;
	std::vector<unsigned char> imageData;
	irrklang::ISoundSource* audioData;	
	//irrklang::ISoundEngine* engine;
	AudioSystem* audio = new AudioSystem;
};

#endif