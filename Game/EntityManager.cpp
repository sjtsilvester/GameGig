#include "stdafx.h"
#include "EntityManager.h"
#include "SFLD.h"
#include "ResourceManager.h"
#include "Entity.h"
#include "ParticleEngine.h"
#include "Enemy.h"

EntityManager::EntityManager(ResourceManager<sf::Texture, std::string>* resourceManager, ParticleEngine* particleEngine) 
	:resourceManager_(resourceManager) , particleEngine_(particleEngine){
}

EntityManager::~EntityManager() = default;

void EntityManager::addEntity(Entity* entity) {
	push_queue_.push_back(std::unique_ptr<Entity>(entity));
}

void EntityManager::addEnemy(Enemy* enemy) {
	enemies_.push_back(enemy);
	addEntity((Entity*)enemy);
}

ParticleEngine* EntityManager::getParticleEngine() {
	return particleEngine_;
}

EntityList* EntityManager::getEntities() {
	return &entities_;
}

void EntityManager::update(int frameTime) {
	for (auto& it : entities_) {
		it->update(frameTime);
	}
	for (auto& it = entities_.begin(); it != entities_.end();) {
		if ((*it)->isDestroyed()) {
			it = entities_.erase(it);
		}
		else {
			it++;
		}
	}

	for (auto& it : push_queue_) {
		entities_.push_back(std::move(it));
	}
	push_queue_.clear();
}

void EntityManager::beat() {
	for (auto& it : enemies_) {
		it->onBeat();
	}
}

void EntityManager::render(sf::RenderTarget* target) {
	particleEngine_->renderStatics(target);
	for (auto& it : entities_) {
		it->render(target);
	}
}

void EntityManager::sfmlEvent(sf::Event evt) {
	for (auto& it : entities_) {
		it->sfmlEvent(evt);
	}
}