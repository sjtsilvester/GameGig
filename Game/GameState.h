#pragma once

#include "BaseState.h"
#include "ResourceManager.h"

class EntityManager;
class ParticleEngine;

class GameState : public BaseState {
public:
	GameState();
	~GameState();
	void sfmlEvent(sf::Event evt);
	void start();
	void pause();
	void resume();
	void exit();

	void update(int frame_time);
	void render(sf::RenderTarget* target);

private:
	ResourceManager<sf::Texture, std::string> resourceManager_;
	std::unique_ptr<EntityManager> entityManager_;
	std::unique_ptr<ParticleEngine> particleEngine_;
};