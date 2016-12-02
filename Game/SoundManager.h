#ifndef SOUNDMANAGER_H
#define SOUNDMANAGER_H

#include "stdafx.h"
#include <SFML/Audio.hpp>

//from my game Immortui http://immortui.hogpog.co.uk
//awful I know

class SoundManager {
public:
	~SoundManager();
	static void add(const std::string& name, const std::string& filename);
	static void play(const std::string& name, bool loop = false, int volume = 25);
	static void playUnique(const std::string& name, bool loop = false, int volume = 25);
	static void addMusic(const std::string& name, const std::string& filename);
	static sf::Music* getMusic(const std::string& name);
	static void playMusic(const std::string& name);
	static void stop(const std::string& name);
	static void stopAll();
	static void clearStopped();
	static void nullSound();
	static void reactivateSound();
	static void update(double frameTime);
	static int getMusicVolume();
	static int getFxVolume();
	static void setMusicVolume(int volume);
	static void setFxVolume(int volume);
private:
	static int musicVolume;
	static int fxVolume;
	static sf::Music* toplay;
	static sf::Music* playing;
	static sf::Music* fadeout;
	static bool musicin;
	static bool fading;
	static bool nulled;
	static std::map<std::string, sf::Music*> music;
	static std::map<std::string, sf::SoundBuffer> soundbuffers;
	static std::map<std::string, sf::Sound*> uniqueSounds;
	static std::vector<sf::Sound*> sounds;
	SoundManager() {}
};

#endif