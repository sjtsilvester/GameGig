#pragma once

#include "stdafx.h"
#include "ResourceManager.h"

#define TILE_SIZE 32

class Entity;
class ParticleEngine;

typedef std::vector<std::unique_ptr<Entity>> EntityList;

class EntityManager {
public:
	EntityManager(ResourceManager<sf::Texture, std::string>* resourceManager, ParticleEngine* particleEngine);
	~EntityManager();

	void addEntity(Entity* entity);
	EntityList* getEntities();

	ParticleEngine* getParticleEngine();

	void update(int frametime);
	void render(sf::RenderTarget* target);

	void sfmlEvent(sf::Event evt);

	void beat();
private:
	ResourceManager<sf::Texture, std::string>* resourceManager_;

	EntityList push_queue_;
	EntityList entities_;

	ParticleEngine* particleEngine_;
};