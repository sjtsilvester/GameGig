#pragma once

#include "Entity.h"

class Enemy : public Entity {
public:
    enum Action {ACTION_LEFT, ACTION_RIGHT, ACTION_UP, ACTION_DOWN, ACTION_SHOOT};

    Enemy(ResourceManager<sf::Texture, std::string>* resourceManager, EntityManager* entityManager, sfld::Vector2f initial_pos, std::vector<Action> actions);

    virtual void update(int frame_time);
    void onBeat();
    virtual void shoot();

protected:
	std::vector<Action> actions;
	int beat_count;
};
