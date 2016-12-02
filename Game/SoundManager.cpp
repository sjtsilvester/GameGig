#include "stdafx.h"
#include "SoundManager.h"

std::map<std::string, sf::SoundBuffer> SoundManager::soundbuffers;
std::vector<sf::Sound*> SoundManager::sounds;
std::map<std::string, sf::Sound*> SoundManager::uniqueSounds;
std::map<std::string, sf::Music*> SoundManager::music;
bool SoundManager::nulled = false;
sf::Music* SoundManager::playing = false;
sf::Music* SoundManager::fadeout = false;
sf::Music* SoundManager::toplay = false;
bool SoundManager::fading = false;
bool SoundManager::musicin = false;
int SoundManager::musicVolume = 80;
int SoundManager::fxVolume = 50;

SoundManager::~SoundManager() {
}

void SoundManager::playUnique(const std::string& name, bool loop, int volume) {
	if (!nulled) {
		std::map<std::string, sf::SoundBuffer>::iterator results = soundbuffers.find(name);
		if (results == soundbuffers.end()) {
			std::cout << "ERROR: Sound " << name << " cannot be found (to play) in the internal buffer." << std::endl;
		}
		else {
			sf::Sound* sound = new sf::Sound(results->second);
			sound->setVolume((float)fxVolume);
			sound->play();
			sound->setLoop(loop);
			uniqueSounds[name] = sound;
		}
	}
}

void SoundManager::addMusic(const std::string& name, const std::string& filename) {
	sf::Music* m = new sf::Music();

	if (!m->openFromFile(filename)) {
		std::cout << "ERROR: Music " << filename << "not found/could not be loaded." << std::endl;
	}
	m->setVolume((float)musicVolume);
	m->setLoop(true);
	music[name] = m;
}

void SoundManager::setMusicVolume(int volume) {
	musicVolume = volume;
	if (volume > 100)
		musicVolume = 100;
	else if (volume < 0) {
		musicVolume = 0;
	}

	if (playing) {
		playing->setVolume((float)volume);
	}
}

void SoundManager::setFxVolume(int volume) {
	fxVolume = volume;
	if (volume > 100)
		fxVolume = 100;
	else if (volume < 0) {
		fxVolume = 0;
	}
}

int SoundManager::getMusicVolume() {
	return musicVolume;
}

int SoundManager::getFxVolume() {
	return fxVolume;
}

sf::Music* SoundManager::getMusic(const std::string& name) {
	std::map<std::string, sf::Music*>::iterator results = music.find(name);
	if (results != music.end()) {
		return results->second;
	}
	return NULL;
}

void SoundManager::stop(const std::string& name) {
	std::map<std::string, sf::Sound*>::iterator results = uniqueSounds.find(name);
	if (results != uniqueSounds.end()) {
		results->second->stop();
	}
}

void SoundManager::playMusic(const std::string& name) {
	if (playing) {
		fadeout = playing;
		fading = true;
		toplay = music[name];
	}
	else {
		musicin = true;
		toplay = music[name];
		toplay->play();
	}
}

void SoundManager::update(double frameTime) {
	clearStopped();
	if (fading) {
		int v = (int)fadeout->getVolume();
		if (v <= frameTime) {
			fadeout->setVolume(0);
		}
		else {
			fadeout->setVolume((playing->getVolume() - (float)frameTime) / 10.f);
		}
		if (fadeout->getVolume() <= 0) {
			playing->pause();
			fading = false;
			musicin = true;
			fadeout = false;
			toplay->setVolume(0);
			toplay->play();
		}
	}
	if (musicin) {
		float getVolume = toplay->getVolume();
		float newv = getVolume + (((float)frameTime) / 10.f);
		toplay->setVolume(newv);
		if (toplay->getVolume() >= musicVolume) {
			musicin = false;
			playing = toplay;
			toplay = false;
		}
	}
}

void SoundManager::add(const std::string& name, const std::string& filename) {
	sf::SoundBuffer buffer;
	if (!buffer.loadFromFile(filename)) {
		std::cout << "ERROR: Sound " << filename << " not found/could not be loaded." << std::endl;
	}
	soundbuffers[name] = buffer;
}

void SoundManager::clearStopped() {
	std::vector<sf::Sound*>::iterator it;
	for (it = sounds.begin(); it != sounds.end();) {
		if ((*it)->getStatus() == sf::Sound::Stopped) {
			delete (*it);
			it = sounds.erase(it);
		}
		else {
			it++;
		}
	}

	std::map<std::string, sf::Sound*>::iterator u;
	for (u = uniqueSounds.begin(); u != uniqueSounds.end();) {
		if (u->second->getStatus() == sf::Sound::Stopped) {
			delete u->second;
			u = uniqueSounds.erase(u);
		}
		else {
			u++;
		}
	}
}

void SoundManager::play(const std::string& name, bool loop, int volume) {
	if (!nulled) {
		std::map<std::string, sf::SoundBuffer>::iterator results = soundbuffers.find(name);
		if (results == soundbuffers.end()) {
			std::cout << "ERROR: Sound " << name << " cannot be found (to play) in the internal buffer." << std::endl;
		}
		else {
			sf::Sound* sound = new sf::Sound(results->second);
			sound->setVolume((float)fxVolume);
			sound->play();
			sound->setLoop(loop);
			sounds.push_back(sound);
		}
	}
}

void SoundManager::stopAll() {
	std::vector<sf::Sound*>::iterator it;
	for (it = sounds.begin(); it != sounds.end(); it++) {
		(*it)->stop();
	}

	std::map<std::string, sf::Sound*>::iterator u;
	for (u = uniqueSounds.begin(); u != uniqueSounds.end(); u++) {
		u->second->stop();
	}
}

void SoundManager::nullSound() {
	nulled = true;
}

void SoundManager::reactivateSound() {
	nulled = false;
}