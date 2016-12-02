#pragma once

#include "Entity.h"

class Enemy : public Entity {
public:
    static enum Action {Left, Right, Up, Down, Shoot};
    vector<Action> actions;

    Enemy(ResourceManager<sf::Texture, std::string>* resourceManager, EntityManager* entityManager, int initial_x, int initial_y);

    void update(int frame_time);
};
