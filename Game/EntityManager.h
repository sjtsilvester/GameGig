#pragma once

#include "stdafx.h"
#include "ResourceManager.h"

#define TILE_SIZE 32

#define SCREEN_WIDTH 12*TILE_SIZE
#define SCREEN_HEIGHT 24*TILE_SIZE

class Entity;
class ParticleEngine;
class Enemy;
class TopLayerObj;
class Player;

typedef std::vector<std::unique_ptr<Entity>> EntityList;
typedef std::vector<std::unique_ptr<TopLayerObj>> TopLayerObjList;
typedef std::vector<Enemy*> EnemyList;

class EntityManager {
public:
	EntityManager(ResourceManager<sf::Texture, std::string>* resourceManager, ParticleEngine* particleEngine);
	~EntityManager();

	void addTopLayer(TopLayerObj* obj);
	void addEntity(Entity* entity);
	void addEnemy(Enemy* enemy);
	EntityList* getEntities();

	ParticleEngine* getParticleEngine();

	void update(int frametime);
	void render(sf::RenderTarget* target);

	void sfmlEvent(sf::Event evt);

	void beat();

	void clearEnemies();

	void setPlayer(Player* player);
	Player* getPlayer();

	void screenShake(float magnitude, int time);
private:
	sf::View view;
	int shake_timer;
	bool in_shake;
	int shake_length;
	float shake_magnitude;

	ResourceManager<sf::Texture, std::string>* resourceManager_;

	EntityList push_queue_;
	EntityList entities_;
	EnemyList enemies_;
	TopLayerObjList top_list_;

	Player* player_;
	

	ParticleEngine* particleEngine_;
};