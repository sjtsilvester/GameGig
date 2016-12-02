#pragma once

#include "Entity.h"

class Enemy : public Entity {
public:
    enum Action {ACTION_LEFT, ACTION_RIGHT, ACTION_UP, ACTION_DOWN, ACTION_SHOOT};

    Enemy(ResourceManager<sf::Texture, std::string>* resourceManager, EntityManager* entityManager, sfld::Vector2f initial_pos, std::vector<Action> actions);

    virtual void update(int frame_time);
    virtual void onBeat();
    virtual void shoot();

protected:
	void baseUpdate(int frame_time); //call this every frame
	virtual void prepareShoot();

	std::vector<Action> actions;
	int beat_count;
};
