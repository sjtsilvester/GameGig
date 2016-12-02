#include "stdafx.h"
#include "EntityManager.h"
#include "SFLD.h"
#include "ResourceManager.h"
#include "Entity.h"
#include "ParticleEngine.h"
#include "Enemy.h"
#include "TopLayerObj.h"
#include "GameState.h"
#include "Player.h"

int EntityManager::bpm = 60;

EntityManager::EntityManager(ResourceManager<sf::Texture, std::string>* resourceManager, ParticleEngine* particleEngine) 
	: resourceManager_(resourceManager) , particleEngine_(particleEngine){
	view = SFLD::window_->getDefaultView();
	in_shake = false;
	shake_timer = 0;
	shake_length = 0;
	bg1 = sf::Sprite(resourceManager_->get("background"));
	bg2 = sf::Sprite(resourceManager_->get("background"));
	bgy = 0;
	font.loadFromFile("media/victor-pixel.ttf");
	healthtext.setFont(font);
	scoretext.setFont(font);
	score = 0;

	healthtext.setPosition(0, SCREEN_HEIGHT - 1 * TILE_SIZE);
	scoretext.setPosition(0, SCREEN_HEIGHT - 2 * TILE_SIZE + TILE_SIZE / 2);
}

EntityManager::~EntityManager() = default;

void EntityManager::setGameState(GameState* state) {
	state_ = state;
}

void EntityManager::addTopLayer(TopLayerObj* obj) {
	top_list_.push_back(std::unique_ptr<TopLayerObj>(obj));
}

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

void EntityManager::increaseScore() {
	score++;
}

int EntityManager::getScore() const {
	return score;
}

void EntityManager::update(int frameTime) {
	bg1.setPosition(0, bgy - SCREEN_HEIGHT);
	bg2.setPosition(0, bgy);

	if (bgy > SCREEN_HEIGHT) {
		bgy = 0;
	}
	bgy += 1.0f / 5.f;

	std::string s = "Lives: " + std::to_string(player_->getHealth());
	healthtext.setString(s);

	std::string s2 = "Score: " + std::to_string(score);
	scoretext.setString(s2);

	
	particleEngine_->update(frameTime);
	for (auto& it : entities_) {
		it->update(frameTime);
	}
	for (auto& it = enemies_.begin(); it != enemies_.end();) {
		if ((*it)->isDestroyed()) {
			it = enemies_.erase(it);
		}
		else {
			it++;
		}
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

	for (auto& it : top_list_) {
		it->update(frameTime);
	}

	for (auto& it = top_list_.begin(); it != top_list_.end();) {
		if ((*it)->toRemove()) {
			it = top_list_.erase(it);
		}
		else {
			it++;
		}
	}

	if (in_shake) {
		float xdisp = (rand() % 21 - 10) / 10.0f;
		float ydisp = (rand() % 21 - 10) / 10.0f;
		view.setCenter(SFLD::window_->getDefaultView().getCenter() + sfld::Vector2f(xdisp*shake_magnitude, ydisp*shake_magnitude));
		SFLD::window_->setView(view);
		shake_timer += frameTime;
		if (shake_timer >= shake_length) {
			shake_timer = 0;
			view = SFLD::window_->getDefaultView();
			SFLD::window_->setView(view);
			in_shake = false;
		}
	}

	push_queue_.clear();
}

void EntityManager::beat() {
	for (auto& it : enemies_) {
		it->onBeat();
	}
}

void EntityManager::setPlayer(Player* player) {
	player_ = player;
}

void EntityManager::clearEnemies() {
	for (auto& it : enemies_) {
		it->destroy();
	}
	state_->gotoNext();
}

Player* EntityManager::getPlayer() {
	return player_;
}

void EntityManager::screenShake(float magnitude, int time) {
	in_shake = true;
	shake_magnitude = magnitude;
	shake_length = time;
	shake_timer = 0;
}

void EntityManager::render(sf::RenderTarget* target) {
	target->draw(bg1);
	target->draw(bg2);
	particleEngine_->renderStatics(target);
	for (auto& it : entities_) {
		it->render(target);
	}
	for (auto& it : top_list_) {
		it->render(target);
	}
	particleEngine_->renderParticles(target);
	target->draw(healthtext);
	target->draw(scoretext);
}

void EntityManager::sfmlEvent(sf::Event evt) {
	for (auto& it : entities_) {
		it->sfmlEvent(evt);
	}
}