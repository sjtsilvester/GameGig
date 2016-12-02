#pragma once

#include "Entity.h"

class Enemy : public Entity {
public:
    static enum Action {Left, Right, Up, Down, Shoot};
    vector<Action> actions;
    int beat_count;

    Enemy(ResourceManager<sf::Texture, std::string>* resourceManager, EntityManager* entityManager, int initial_x, int initial_y, vector<Action> actions);

    void update(int frame_time);
    void onBeat();
    void shoot();
};
